/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

int uv_nonblock_ioctl(int fd, int set) {
  int r;
  do
    r = ioctl(fd, FIONBIO, &set);
  while (r == -1 && errno == EINTR);

  if (r)
    return -errno;
  return 0;
}

int uv__cloexec_ioctl(int fd, int set) {
  int r;

  do
    r = ioctl(fd, set ? FIOCLEX : FIONCLEX);
  while (r == -1 && errno == EINTR);

  if (r)
    return -errno;

  return 0;
}

int uv__close_nocheckstdio(int fd) {
  int saved_errno;
  int rc;

  EVM_ASSERT(fd > -1);

  saved_errno = errno;
  rc = close(fd);
  if (rc == -1) {
    rc = -errno;
    if (rc == -EINTR || rc == -EINPROGRESS)
      rc = 0;
    errno = saved_errno;
  }

  return rc;
}

int uv__close(int fd) {
  EVM_ASSERT(fd > STDERR_FILENO);
  return uv__close_nocheckstdio(fd);
}

int uv_socket(int domain, int type, int protocol) {
  int sockfd;
  int err;


  sockfd = socket(domain, type, protocol);
  if (sockfd == -1)
    return -errno;

  err = uv_nonblock(sockfd, 1);
  if (err == 0)
    err = uv__cloexec(sockfd, 1);

  if (err) {
    uv__close(sockfd);
    return err;
  }

  return sockfd;
}

int uv__getiovmax(void) {
#if defined(IOV_MAX)
  return IOV_MAX;
#elif defined(_SC_IOV_MAX)
  static int iovmax = -1;
  if (iovmax == -1) {
    iovmax = sysconf(_SC_IOV_MAX);
    /* On some embedded devices (arm-linux-uclibc based ip camera),
     * sysconf(_SC_IOV_MAX) can not get the correct value. The return
     * value is -1 and the errno is EINPROGRESS. Degrade the value to 1.
     */
    if (iovmax == -1) iovmax = 1;
  }
  return iovmax;
#else
  return 1024;
#endif
}
