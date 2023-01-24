/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

#define UV__INET_ADDRSTRLEN         16
#define UV__INET6_ADDRSTRLEN        46

static void uv__write(uv_stream_t* stream);

int uv__tcp_nodelay(int fd, int on) {
  if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)))
    return -errno;
  return 0;
}

int uv__tcp_keepalive(int fd, int on, unsigned int delay) {
  if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on)))
    return -errno;

#ifdef TCP_KEEPIDLE
  if (on && setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &delay, sizeof(delay)))
    return -errno;
#endif

  return 0;
}

void uv__stream_init(uv_loop_t* loop,
                     uv_stream_t* stream,
                     uv_handle_type type) {
  uv_handle_init(loop, (uv_handle_t*)stream, type, NULL);
  stream->read_cb = NULL;
  stream->alloc_cb = NULL;
  stream->close_cb = NULL;
  stream->connection_cb = NULL;
  stream->connect_req = NULL;
  stream->shutdown_req = NULL;
  stream->accepted_fd = -1;
  stream->fd = -1;
  stream->write_queue_size = 0;
  stream->loop = loop;
  QUEUE_INIT(&stream->write_queue);
  QUEUE_INIT(&stream->write_completed_queue);
}

int uv__stream_open(uv_stream_t* stream, int fd, int flags) {
  if (!(stream->fd == -1 || stream->fd == fd) )
    return -EBUSY;

  EVM_ASSERT(fd >= 0);
  stream->flags |= flags;

  if (stream->type == UV_TCP) {
    if ((stream->flags & UV_TCP_NODELAY) && uv__tcp_nodelay(fd, 1))
      return -errno;

    if ((stream->flags & UV_TCP_KEEPALIVE) && uv__tcp_keepalive(fd, 1, 60))
      return -errno;
  }
  stream->fd = fd;
  return 0;
}

static int maybe_new_socket(uv_tcp_t* handle, int domain, int flags) {
  int sockfd;
  int err;

  if (domain == AF_UNSPEC || handle->fd != -1) {
    handle->flags |= flags;
    return 0;
  }

  err = uv_socket(domain, SOCK_STREAM, 0);
  if (err < 0)
    return err;
  sockfd = err;

  err = uv__stream_open((uv_stream_t*)handle, sockfd, flags);
  if (err) {
    uv__close(sockfd);
    return err;
  }

  return 0;
}

int uv_tcp_init_ex(uv_loop_t* loop, uv_tcp_t* tcp, unsigned int flags) {
  int domain;
  domain = flags & 0xFF;
  if (domain != AF_INET && domain != AF_INET6 && domain != AF_UNSPEC)
    return -EINVAL;

  if (flags & ~0xFF)
    return -EINVAL;

  uv__stream_init(loop, (uv_stream_t*)tcp, UV_TCP);

  if (domain != AF_UNSPEC) {
    int err = maybe_new_socket(tcp, domain, 0);
    if (err) {
      QUEUE_REMOVE(&loop->tcp_queue);
      return err;
    }
  }
  return 0;
}


int uv_tcp_init(uv_loop_t* loop, uv_tcp_t* tcp) {
  return uv_tcp_init_ex(loop, tcp, AF_UNSPEC);
}

int uv__tcp_connect(uv_connect_t* req,
                    uv_tcp_t* handle,
                    const struct sockaddr* addr,
                    unsigned int addrlen,
                    uv_connect_cb cb) {
  int err;
  int r;

  EVM_ASSERT(handle->type == UV_TCP);

  if (handle->connect_req != NULL)
    return -EALREADY;  /* FIXME(bnoordhuis) -EINVAL or maybe -EBUSY. */

  err = maybe_new_socket(handle,
                         addr->sa_family,
                         UV_STREAM_READABLE | UV_STREAM_WRITABLE);
  if (err)
    return err;

  handle->delayed_error = 0;

  do {
    errno = 0;
    r = connect(handle->fd, addr, addrlen);
  } while (r == -1 && errno == EINTR);

  /* We not only check the return value, but also check the errno != 0.
   * Because in rare cases connect() will return -1 but the errno
   * is 0 (for example, on Android 4.3, OnePlus phone A0001_12_150227)
   * and actually the tcp three-way handshake is completed.
   */
  if (r == -1 && errno != 0) {
    if (errno == EINPROGRESS)
      ; /* not an error */
    else if (errno == ECONNREFUSED)
    /* If we get a ECONNREFUSED wait until the next tick to report the
     * error. Solaris wants to report immediately--other unixes want to
     * wait.
     */
      handle->delayed_error = -errno;
    else
      return -errno;
  }

  uv_request_init(handle->loop, (uv_req_t*)req, UV_CONNECT, cb);
  req->handle = (uv_stream_t*) handle;
  return uv_request_pending((uv_req_t*)req);
}

int uv_tcp_connect(uv_connect_t* req,
                   uv_tcp_t* handle,
                   const struct sockaddr* addr,
                   uv_connect_cb cb) {
  unsigned int addrlen;

  if (handle->type != UV_TCP)
    return UV_EINVAL;

  if (addr->sa_family == AF_INET)
    addrlen = sizeof(struct sockaddr_in);
  else if (addr->sa_family == AF_INET6)
    addrlen = sizeof(struct sockaddr_in6);
  else
    return UV_EINVAL;

  return uv__tcp_connect(req, handle, addr, addrlen, cb);
}

int uv__tcp_bind(uv_tcp_t* tcp,
                 const struct sockaddr* addr,
                 unsigned int addrlen,
                 unsigned int flags) {
  int err;
  int on;

  /* Cannot set IPv6-only mode on non-IPv6 socket. */
  if ((flags & UV_TCP_IPV6ONLY) && addr->sa_family != AF_INET6)
    return -EINVAL;

  err = maybe_new_socket(tcp,
                         addr->sa_family,
                         UV_STREAM_READABLE | UV_STREAM_WRITABLE);
  if (err)
    return err;

  on = 1;
  if (setsockopt(tcp->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
    return -errno;

#ifdef IPV6_V6ONLY
  if (addr->sa_family == AF_INET6) {
    on = (flags & UV_TCP_IPV6ONLY) != 0;
    if (setsockopt(tcp->fd,
                   IPPROTO_IPV6,
                   IPV6_V6ONLY,
                   &on,
                   sizeof on) == -1) {
      return -errno;
    }
  }
#endif

  errno = 0;
  if (bind(tcp->fd, addr, addrlen) && errno != EADDRINUSE) {
    if (errno == EAFNOSUPPORT)
      /* OSX, other BSDs and SunoS fail with EAFNOSUPPORT when binding a
       * socket created with AF_INET to an AF_INET6 address or vice versa. */
      return -EINVAL;
    return -errno;
  }
  tcp->delayed_error = -errno;

  tcp->flags |= UV_HANDLE_BOUND;
  if (addr->sa_family == AF_INET6)
    tcp->flags |= UV_HANDLE_IPV6;

  return 0;
}


int uv_tcp_bind(uv_tcp_t* handle,
                const struct sockaddr* addr,
                unsigned int flags) {
  unsigned int addrlen;

  if (handle->type != UV_TCP)
    return UV_EINVAL;

  if (addr->sa_family == AF_INET)
    addrlen = sizeof(struct sockaddr_in);
  else if (addr->sa_family == AF_INET6)
    addrlen = sizeof(struct sockaddr_in6);
  else
    return UV_EINVAL;

  return uv__tcp_bind(handle, addr, addrlen, flags);
}

int uv__accept(int sockfd) {
  int peerfd;
  int err;

  EVM_ASSERT(sockfd >= 0);

  while (1) {
    peerfd = accept(sockfd, NULL, NULL);
    if (peerfd == -1) {
      if (errno == EINTR)
        continue;
      return -errno;
    }

    err = uv__cloexec(peerfd, 1);
    if (err == 0)
      err = uv_nonblock(peerfd, 1);

    if (err) {
      uv__close(peerfd);
      return err;
    }

    return peerfd;
  }
}


static void listen_poll(uv_poll_t* work_req, int status, int events) {
    uv_stream_t *stream = work_req->data;
    int err;
    EVM_ASSERT(stream->accepted_fd == -1);
    EVM_ASSERT(!(stream->flags & UV_CLOSING));

    /* connection_cb can close the server socket while we're
     * in the loop so check it on each iteration.
     */
    while (stream->fd != -1) {
      EVM_ASSERT(stream->accepted_fd == -1);

      err = uv__accept(stream->fd);
      if (err < 0) {
        if (err == -EAGAIN || err == -EWOULDBLOCK)
          return;  /* Not an error. */

        if (err == -ECONNABORTED)
          continue;  /* Ignore. Nothing we can do about that. */

        stream->connection_cb(stream, err);
        continue;
      }

      stream->accepted_fd = err;
      stream->connection_cb(stream, 0);

      if (stream->accepted_fd != -1) {
        return;
      }

      if (stream->type == UV_TCP && (stream->flags & UV_TCP_SINGLE_ACCEPT)) {
        /* Give other processes a chance to accept connections. */
        struct timespec timeout = { 0, 1 };
        nanosleep(&timeout, NULL);
      }
    }
}


int uv_tcp_listen(uv_tcp_t* tcp, int backlog, uv_connection_cb cb) {
  static int single_accept = -1;
  int err;

  if (tcp->delayed_error)
    return tcp->delayed_error;

  if (single_accept == -1) {
    const char* val = getenv("UV_TCP_SINGLE_ACCEPT");
    single_accept = (val != NULL && atoi(val) != 0);  /* Off by default. */
  }

  if (single_accept)
    tcp->flags |= UV_TCP_SINGLE_ACCEPT;

  err = maybe_new_socket(tcp, AF_INET, UV_STREAM_READABLE);
  if (err)
    return err;

  if (listen(tcp->fd, backlog))
    return -errno;

  tcp->connection_cb = cb;
  tcp->flags |= UV_HANDLE_BOUND;
  /* Start listening for connections. */

  uv_poll_init(tcp->loop, &tcp->io_watcher, tcp->fd);
  tcp->io_watcher.data = tcp;
  uv_poll_start(&tcp->io_watcher, UV_READABLE, listen_poll);
  return 0;
}

int uv_listen(uv_stream_t* stream, int backlog, uv_connection_cb cb) {
  int err;

  switch (stream->type) {
  case UV_TCP:
    err = uv_tcp_listen((uv_tcp_t*)stream, backlog, cb);
    break;
  default:
    err = -EINVAL;
  }
  return err;
}

int uv_accept(uv_stream_t* server, uv_stream_t* client) {
  int err;

  EVM_ASSERT(server->loop == client->loop);

  if (server->accepted_fd == -1)
    return -EAGAIN;

  switch (client->type) {
    case UV_TCP:
      err = uv__stream_open(client,
                            server->accepted_fd,
                            UV_STREAM_READABLE | UV_STREAM_WRITABLE);
      if (err) {
        uv__close(server->accepted_fd);
        goto done;
      }
      break;
    default:
      return -EINVAL;
  }

  client->flags |= UV_HANDLE_BOUND;

done:
  server->accepted_fd = -1;
  return err;
}

static size_t uv__write_req_size(uv_write_t* req) {
  size_t size;

  EVM_ASSERT(req->bufs != NULL);
  size = uv__count_bufs(req->bufs + req->write_index,
                        req->nbufs - req->write_index);
  EVM_ASSERT(req->handle->write_queue_size >= size);

  return size;
}

static void uv__write_callbacks(uv_stream_t* stream) {
  uv_write_t* req;
  QUEUE* q;

  while (!QUEUE_EMPTY(&stream->write_completed_queue)) {
    /* Pop a req off write_completed_queue. */
    q = QUEUE_HEAD(&stream->write_completed_queue);
    req = QUEUE_DATA(q, uv_write_t, node);
    QUEUE_REMOVE(q);

    if (req->bufs != NULL) {
      stream->write_queue_size -= uv__write_req_size(req);
      if (req->bufs != req->bufsml)
        uv__free(req->bufs);
      req->bufs = NULL;
    }

    /* NOTE: call callback AFTER freeing the request data. */
    if (req->cb)
      req->cb(req, req->error);
  }

  EVM_ASSERT(QUEUE_EMPTY(&stream->write_completed_queue));
}

static void write_worker(uv_work_t* work_req) {
    uv_stream_t* stream = work_req->data;
    EVM_ASSERT(stream->type == UV_TCP ||
             stream->type == UV_NAMED_PIPE ||
             stream->type == UV_TTY);
    EVM_ASSERT(!(stream->flags & UV_CLOSING));

    if (stream->connect_req) {
        return;
    }

    EVM_ASSERT(uv__stream_fd(stream) >= 0);


    uv__write(stream);
    uv__write_callbacks(stream);
}

ssize_t writev(int fd, const struct iovec* iiovec, int count) {
  ssize_t result = 0;
  ssize_t total = 0;
  int idx;

  for (idx = 0; idx < count; ++idx) {
    result = uv_posix_write(fd, iiovec[idx].iov_base, iiovec[idx].iov_len);
    if (result < 0) {
      return result;
    } else {
      total += result;
    }
  }
  return total;
}

static void uv__write_req_finish(uv_write_t* req) {
  uv_stream_t* stream = req->handle;

  /* Pop the req off tcp->write_queue. */
  QUEUE_REMOVE(&req->node);

  /* Only free when there was no error. On error, we touch up write_queue_size
   * right before making the callback. The reason we don't do that right away
   * is that a write_queue_size > 0 is our only way to signal to the user that
   * they should stop writing - which they should if we got an error. Something
   * to revisit in future revisions of the libuv API.
   */
  if (req->error == 0) {
    if (req->bufs != req->bufsml)
      uv__free(req->bufs);
    req->bufs = NULL;
  }

  /* Add it to the write_completed_queue where it will have its
   * callback called in the near future.
   */
  QUEUE_INSERT_TAIL(&stream->write_completed_queue, &req->node);
}

static void uv__write(uv_stream_t* stream) {
  struct iovec* iov;
  QUEUE* q;
  uv_write_t* req;
  int iovmax;
  int iovcnt;
  ssize_t n;

start:

  EVM_ASSERT(stream->fd >= 0);

  if (QUEUE_EMPTY(&stream->write_queue))
    return;

  q = QUEUE_HEAD(&stream->write_queue);
  req = QUEUE_DATA(q, uv_write_t, node);
  EVM_ASSERT(req->handle == stream);

  /*
   * Cast to iovec. We had to have our own uv_buf_t instead of iovec
   * because Windows's WSABUF is not an iovec.
   */
  EVM_ASSERT(sizeof(uv_buf_t) == sizeof(struct iovec));
  iov = (struct iovec*) &(req->bufs[req->write_index]);
  iovcnt = req->nbufs - req->write_index;

  iovmax = uv__getiovmax();

  /* Limit iov count to avoid EINVALs from writev() */
  if (iovcnt > iovmax)
    iovcnt = iovmax;

  do {
    if (iovcnt == 1) {
      n = uv_posix_write(uv__stream_fd(stream), iov[0].iov_base, iov[0].iov_len);
    } else {
      n = writev(uv__stream_fd(stream), iov, iovcnt);
    }
  }

  while (n == -1 && errno == EINTR);

  if (n < 0) {
    if (errno != EAGAIN && errno != EWOULDBLOCK) {
      /* Error */
      req->error = -errno;
      uv__write_req_finish(req);
//      uv__io_stop(stream->loop, &stream->io_watcher, POLLOUT);
//      if (!uv__io_active(&stream->io_watcher, POLLIN))
//        uv__handle_stop(stream);
//      uv__stream_osx_interrupt_select(stream);
      return;
    } else if (stream->flags & UV_STREAM_BLOCKING) {
      /* If this is a blocking stream, try again. */
      goto start;
    }
  } else {
    /* Successful write */

    while (n >= 0) {
      uv_buf_t* buf = &(req->bufs[req->write_index]);
      size_t len = buf->len;

      EVM_ASSERT(req->write_index < req->nbufs);

      if ((size_t)n < len) {
        buf->base += n;
        buf->len -= n;
        stream->write_queue_size -= n;
        n = 0;

        /* There is more to write. */
        if (stream->flags & UV_STREAM_BLOCKING) {
          /*
           * If we're blocking then we should not be enabling the write
           * watcher - instead we need to try again.
           */
          goto start;
        } else {
          /* Break loop and ensure the watcher is pending. */
          break;
        }

      } else {
        /* Finished writing the buf at index req->write_index. */
        req->write_index++;

        EVM_ASSERT((size_t)n >= len);
        n -= len;

        EVM_ASSERT(stream->write_queue_size >= len);
        stream->write_queue_size -= len;

        if (req->write_index == req->nbufs) {
          /* Then we're done! */
          EVM_ASSERT(n == 0);
          uv__write_req_finish(req);
          /* TODO: start trying to write the next request. */
          return;
        }
      }
    }
  }

  /* Either we've counted n down to zero or we've got EAGAIN. */
  EVM_ASSERT(n == 0 || n == -1);

  /* Only non-blocking streams should use the write_watcher. */
  EVM_ASSERT(!(stream->flags & UV_STREAM_BLOCKING));

  uv_queue_work(stream->loop, req, write_worker, NULL);
}

int uv_write2(uv_write_t* req,
              uv_stream_t* stream,
              const uv_buf_t bufs[],
              unsigned int nbufs,
              uv_stream_t* send_handle,
              uv_write_cb cb) {
  int empty_queue;

  EVM_ASSERT(nbufs > 0);
  EVM_ASSERT((stream->type == UV_TCP ||
          stream->type == UV_NAMED_PIPE ||
          stream->type == UV_TTY) &&
         "uv_write (unix) does not yet support other types of streams");

  if (stream->fd < 0)
    return -EBADF;


  /* It's legal for write_queue_size > 0 even when the write_queue is empty;
   * it means there are error-state requests in the write_completed_queue that
   * will touch up write_queue_size later, see also uv__write_req_finish().
   * We could check that write_queue is empty instead but that implies making
   * a write() syscall when we know that the handle is in error mode.
   */
  empty_queue = (stream->write_queue_size == 0);

  /* Initialize the req */
  uv_request_init(stream->loop, req, UV_WRITE, cb);
  req->handle = stream;
  req->send_handle = send_handle;

  req->bufs = req->bufsml;
  if (nbufs > ARRAY_SIZE(req->bufsml))
    req->bufs = uv__malloc(nbufs * sizeof(bufs[0]));

  if (req->bufs == NULL)
    return -ENOMEM;

  memcpy(req->bufs, bufs, nbufs * sizeof(bufs[0]));
  req->nbufs = nbufs;
  req->write_index = 0;
  stream->write_queue_size += uv__count_bufs(bufs, nbufs);

  /* Append the request to write_queue. */
  QUEUE_INSERT_TAIL(&stream->write_queue, &req->node);

  /* If the queue was empty when this function began, we should attempt to
   * do the write immediately. Otherwise start the write_watcher and wait
   * for the fd to become writable.
   */
  if (stream->connect_req) {
    /* Still connecting, do nothing. */
  }
  else if (empty_queue) {
    uv__write(stream);
  }
  else {
    /*
     * blocking streams should never have anything in the queue.
     * if this assert fires then somehow the blocking stream isn't being
     * sufficiently flushed in uv__write.
     */
    EVM_ASSERT(!(stream->flags & UV_STREAM_BLOCKING));
    uv_queue_work(stream->loop, req, write_worker, NULL);
  }

  return 0;
}


/* The buffers to be written must remain valid until the callback is called.
 * This is not required for the uv_buf_t array.
 */
int uv_write(uv_write_t* req,
             uv_stream_t* handle,
             const uv_buf_t bufs[],
             unsigned int nbufs,
             uv_write_cb cb) {
  return uv_write2(req, handle, bufs, nbufs, NULL, cb);
}

int uv_shutdown(uv_shutdown_t* req, uv_stream_t* stream, uv_shutdown_cb cb) {
    EVM_ASSERT((stream->type == UV_TCP || stream->type == UV_NAMED_PIPE));

    if (!(stream->flags & UV_STREAM_WRITABLE) ||
        stream->flags & UV_STREAM_SHUT ||
        stream->flags & UV_STREAM_SHUTTING ||
        uv_is_closing((uv_handle_t*)stream)) {
        return -ENOTCONN;
    }

    EVM_ASSERT(uv__stream_fd(stream) >= 0);

    /* Initialize request */
    uv_request_init(stream->loop, req, UV_SHUTDOWN, cb);
    req->handle = stream;
    stream->shutdown_req = req;
    stream->flags |= UV_STREAM_SHUTTING;

    return uv_request_pending(req);
}

static void read_worker(uv_work_t* work_req) {
    uv_stream_t *stream = work_req->data;
    int count;
    uv_buf_t buf;
    ssize_t nread;
    count = 32;
    while(stream->read_cb && stream->alloc_cb) {
        buf = uv_buf_init(NULL, 0);
        stream->alloc_cb((uv_handle_t*)stream, 64 * 1024, &buf);
        if (buf.base == NULL || buf.len == 0) {
          /* User indicates it can't or won't handle the read. */
          stream->read_cb(stream, UV_ENOBUFS, &buf);
          return;
        }

        EVM_ASSERT(buf.base != NULL);
        EVM_ASSERT(stream->fd >= 0);

        do {
            nread = uv_posix_read(stream->fd, buf.base, buf.len);
        }
        while (nread < 0 && errno == EINTR);

        if (nread < 0) {
            /* Error */
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                stream->read_cb(stream, 0, &buf);
            } else {
                /* Error. User should call uv_close(). */
                stream->read_cb(stream, -errno, &buf);
                if (stream->flags & UV_STREAM_READING) {
                    stream->flags &= ~UV_STREAM_READING;
                    uv_close((uv_handle_t*)stream, stream->close_cb);
                    uv_close((uv_handle_t*)work_req, work_req->close_cb);
                }
            }
            return;
        } else if(nread == 0) {
            stream->flags |= UV_STREAM_READ_EOF;
            stream->read_cb(stream, UV_EOF, &buf);
            stream->flags &= ~UV_STREAM_READING;
            uv_close((uv_handle_t*)stream, stream->close_cb);
            uv_close((uv_handle_t*)work_req, work_req->close_cb);
        } else {
            ssize_t buflen = buf.len;

            stream->read_cb(stream, nread, &buf);
            if (nread < buflen) {
                stream->flags |= UV_STREAM_READ_PARTIAL;
                return;
            }
        }
    }
}

int uv_read_start(uv_stream_t* stream,
                  uv_alloc_cb alloc_cb,
                  uv_read_cb read_cb) {
  EVM_ASSERT(stream->type == UV_TCP);

  if (stream->flags & UV_CLOSING)
    return -EINVAL;

  stream->flags |= UV_STREAM_READING;

  EVM_ASSERT(stream->fd >= 0);
  EVM_ASSERT(alloc_cb);

  stream->read_cb = read_cb;
  stream->alloc_cb = alloc_cb;

  stream->req.data = stream;
  uv_queue_work(stream->loop, &stream->req, read_worker, NULL);

  return 0;
}

int uv_tcp_keepalive(uv_tcp_t* handle, int on, unsigned int delay) {
  int err;

  if (handle->fd != -1) {
    err =uv__tcp_keepalive(handle->fd, on, delay);
    if (err)
      return err;
  }

  if (on)
    handle->flags |= UV_TCP_KEEPALIVE;
  else
    handle->flags &= ~UV_TCP_KEEPALIVE;

  return 0;
}

static int inet_ntop4(const unsigned char *src, char *dst, size_t size) {
  static const char fmt[] = "%u.%u.%u.%u";
  char tmp[UV__INET_ADDRSTRLEN];
  int l;

  l = snprintf(tmp, sizeof(tmp), fmt, src[0], src[1], src[2], src[3]);
  if (l <= 0 || (size_t) l >= size) {
    return UV_ENOSPC;
  }
  strncpy(dst, tmp, size);
  dst[size - 1] = '\0';
  return 0;
}

int uv_inet_ntop(int af, const void* src, char* dst, size_t size) {
  switch (af) {
  case AF_INET:
    return (inet_ntop4(src, dst, size));
  default:
    return UV_EAFNOSUPPORT;
  }
  /* NOTREACHED */
}

int uv_tcp_getsockname(const uv_tcp_t* handle,
                       struct sockaddr* name,
                       int* namelen) {
  socklen_t socklen;

  if (handle->delayed_error)
    return handle->delayed_error;

  if (handle->fd < 0)
    return -EINVAL;  /* FIXME(bnoordhuis) -EBADF */

  /* sizeof(socklen_t) != sizeof(int) on some systems. */
  socklen = (socklen_t) *namelen;

  if (getsockname(handle->fd, name, &socklen))
    return -errno;

  *namelen = (int) socklen;
  return 0;
}

void uv_tcp_close(uv_tcp_t* handle) {
    if (handle->fd != -1) {
        /* Don't close stdio file descriptors.  Nothing good comes from it. */
        if (handle->fd > STDERR_FILENO)
            uv__close(handle->fd);
        handle->fd = -1;
    }

    if (handle->accepted_fd != -1) {
        uv__close(handle->accepted_fd);
        handle->accepted_fd = -1;
    }
}
