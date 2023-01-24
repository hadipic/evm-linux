/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifdef CONFIG_EVM_MODULE_TCP

#include "linux_uv.h"

static void tcp_object_init(evm_t *e, evm_val_t jtcp) {
  uv_handle_t* handle = iot_uv_handle_create(sizeof(uv_tcp_t), jtcp, 0);
  uv_tcp_init(system_get_uv_loop(), (uv_tcp_t*)handle);
}

static void iotjs_tcp_report_req_result(uv_req_t* req, int status) {
  EVM_ASSERT(req);
  evm_t *e = evm_runtime();
  // Take callback function object.
  evm_val_t jcallback = *IOT_UV_REQUEST_CALLBACK(req);

  // Only parameter is status code.
  evm_val_t jstatus = evm_mk_number(e, status);

  // Make callback.
  evm_call(e, jcallback, EVM_UNDEFINED, 1, &jstatus);

  // Destroy args
  evm_val_free(e, jstatus);

  // Release request.
  iot_uv_request_destroy(req);
}

// Connection request result handler.
static void after_connect(uv_connect_t* req, int status) {
  iotjs_tcp_report_req_result((uv_req_t*)req, status);
}

//connect(address, port, callback)
EVM_FUNCTION(evm_module_tcp_connect) {
    EVM_EPCV;
    uv_tcp_t *tcp_handle = evm_object_get_user_data(e, p);

    const char *address = evm_2_string(e, v[0]);
    int port = evm_2_integer(e, v[1]);
    evm_val_t jcallback = v[2];

    struct sockaddr_in addr;
    int err = uv_ip4_addr(address, port, &addr);

    if (err == 0) {
        // Create connection request and configure request data.
        uv_req_t* req_connect =
            iot_uv_request_create(sizeof(uv_connect_t), jcallback, 0);

        // Create connection request.
        err = uv_tcp_connect((uv_connect_t*)req_connect, tcp_handle,
                             (struct sockaddr*)(&addr), after_connect);

        if (err) {
          iot_uv_request_destroy(req_connect);
        }
    }
    EVM_RETURN(evm_mk_number(e, err));
}

void after_close(uv_handle_t* handle) {
    evm_t *e = evm_runtime();
    evm_val_t jtcp = IOT_UV_HANDLE_DATA(handle)->jobject;

    // callback function.
    evm_val_t jcallback = evm_prop_get(e, jtcp, "onclose");
    if (evm_is_callable(e, jcallback)) {
        evm_call_free(e, jcallback, EVM_UNDEFINED, 0, NULL);
    }
    evm_val_free(e, jcallback);
}

EVM_FUNCTION(evm_module_tcp_close) {
    EVM_EPCV;
    uv_handle_t *uv_handle = evm_object_get_user_data(e, p);
    iot_uv_handle_close(uv_handle, after_close);
    EVM_RETURN(EVM_UNDEFINED);
}

// Socket binding, this function would be called from server socket before
// start listening.
// [0] address
// [1] port
EVM_FUNCTION(evm_module_tcp_bind) {
    EVM_EPCV;
    uv_tcp_t *tcp_handle = evm_object_get_user_data(e, p);

    const char * address = evm_2_string(e, v[0]);
    int port = evm_2_integer(e, v[1]);

    struct sockaddr_in addr;
    int err = uv_ip4_addr(address, port, &addr);

    if (err == 0) {
        err = uv_tcp_bind(tcp_handle, (struct sockaddr*)(&addr), 0);
    }

    EVM_RETURN(evm_mk_number(e, err));
}

// A client socket wants to connect to this server.
// Parameters:
//   * uv_stream_t* handle - server handle
//   * int status - status code
static void on_connection(uv_stream_t* handle, int status) {
    evm_t *e = evm_runtime();
    evm_val_t jtcp = IOT_UV_HANDLE_DATA(handle)->jobject;

    // `onconnection` callback.
    evm_val_t jonconnection = evm_prop_get(e, jtcp, "onconnection");
    EVM_ASSERT(evm_is_callable(e, jonconnection));

    // The callback takes two parameter
    // [0] status
    // [1] client tcp object
    int argc = 1;
    evm_val_t args[2] = { evm_mk_number(e, status), EVM_UNDEFINED };

    if (status == 0) {
        // Create client socket handle wrapper.
        evm_val_t jcreate_tcp = evm_prop_get(e, jtcp, "createTCP");
        EVM_ASSERT(evm_is_callable(e, jcreate_tcp));

        evm_val_t jclient_tcp = evm_call(e, jcreate_tcp, EVM_UNDEFINED, 0, NULL);
        EVM_ASSERT(evm_is_object(e, jclient_tcp));

        void* client_handle = evm_object_get_user_data(e, jclient_tcp);


        if (!client_handle || uv_accept(handle, (uv_stream_t*)client_handle)) {
          return;
        }
        args[argc++] = jclient_tcp;
        evm_val_free(e, jcreate_tcp);
    }
    evm_call_free(e, jonconnection, jtcp, argc, args);
    evm_val_free(e, jonconnection);
    for (size_t i = 0; i < argc; i++) {
        evm_val_free(e, args[i]);
    }
}

EVM_FUNCTION(evm_module_tcp_listen) {
    EVM_EPCV;
    uv_tcp_t *tcp_handle = evm_object_get_user_data(e, p);
    int backlog = evm_2_integer(e, v[0]);
    int err = uv_listen((uv_stream_t*)tcp_handle, backlog, on_connection);

    EVM_RETURN(evm_mk_number(e, err));
}

void AfterWrite(uv_write_t* req, int status) {
    iotjs_tcp_report_req_result((uv_req_t*)req, status);
}

EVM_FUNCTION(evm_module_tcp_write) {
    EVM_EPCV;
    uv_stream_t *tcp_handle = evm_object_get_user_data(e, p);
    evm_val_t jbuffer = v[0];

    uv_buf_t buf;
    buf.base = (char*)evm_buffer_addr(e, jbuffer);
    buf.len = (size_t)evm_buffer_len(e, jbuffer);

    evm_val_t arg1 = v[1];
    uv_req_t* req_write = iot_uv_request_create(sizeof(uv_write_t), arg1, 0);

    int err = uv_write((uv_write_t*)req_write, tcp_handle, &buf, 1, AfterWrite);

    if (err) {
        iot_uv_request_destroy((uv_req_t*)req_write);
    }

    EVM_RETURN(evm_mk_number(e, err));
}

static void on_alloc(uv_handle_t* handle, size_t suggested_size,
                     uv_buf_t* buf) {
  if (suggested_size > EVM_MAX_READ_BUFFER_SIZE) {
    suggested_size = EVM_MAX_READ_BUFFER_SIZE;
  }

  buf->base = evm_malloc(suggested_size);
  buf->len = suggested_size;
}

static void on_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
    evm_t *e = evm_runtime();
    evm_val_t jtcp = IOT_UV_HANDLE_DATA(handle)->jobject;

    // socket object
    evm_val_t jsocket = evm_prop_get(e, jtcp, "owner");
    EVM_ASSERT(evm_is_object(e, jsocket));

    // onread callback
    evm_val_t jonread = evm_prop_get(e, jtcp, "onread");
    EVM_ASSERT(evm_is_callable(e, jonread));

    int argc = 3;
    evm_val_t jargs[4] = { jsocket, evm_mk_number(e, nread),
                             evm_mk_boolean(e, false), EVM_UNDEFINED };

    if (nread <= 0) {
        evm_free(buf->base);

        if (nread < 0) {
          if (nread == UV__EOF) {
            jargs[2] = evm_mk_boolean(e, true);
          }

          evm_call_free(e, jonread, EVM_UNDEFINED, argc, jargs);
        }
    } else {
        evm_val_t jbuffer = evm_buffer_create(e, buf->base, (size_t)nread);
        jargs[argc++] = jbuffer;
        evm_call_free(e, jonread, EVM_UNDEFINED, argc, jargs);

        evm_free(buf->base);
    }

    for (uint8_t i = 0; i < argc; i++) {
        evm_val_free(e, jargs[i]);
    }
    evm_val_free(e, jonread);
}

EVM_FUNCTION(evm_module_tcp_read_start) {
    EVM_EPCV;
    uv_stream_t *tcp_handle = evm_object_get_user_data(e, p);

    int err = uv_read_start(tcp_handle, on_alloc, on_read);

    EVM_RETURN(evm_mk_number(e, err));
}

static void AfterShutdown(uv_shutdown_t* req, int status) {
  iotjs_tcp_report_req_result((uv_req_t*)req, status);
}

EVM_FUNCTION(evm_module_tcp_shutdown) {
    EVM_EPCV;
    uv_stream_t *tcp_handle = evm_object_get_user_data(e, p);

    evm_val_t arg0 = v[0];
    uv_shutdown_t* req_shutdown =
      (uv_shutdown_t*)iot_uv_request_create(sizeof(uv_shutdown_t), arg0, 0);

    int err = uv_shutdown(req_shutdown, tcp_handle, AfterShutdown);

    if (err) {
        iot_uv_request_destroy((uv_req_t*)req_shutdown);
    }

    EVM_RETURN(evm_mk_number(e, err));
}

EVM_FUNCTION(evm_module_tcp_set_keep_alive) {
    EVM_EPCV;
    uv_tcp_t *tcp_handle = evm_object_get_user_data(e, p);

    int enable = evm_2_integer(e, v[0]);
    unsigned delay = evm_2_integer(e, v[1]);

    int err = uv_tcp_keepalive(tcp_handle, enable, delay);

    EVM_RETURN(evm_mk_number(e, err));
}

EVM_FUNCTION(evm_module_tcp_err_name) {
    EVM_EPCV;
    int errorcode = evm_2_integer(e, v[0]);
    EVM_RETURN(evm_string_create(e, (const char*)uv_err_name(errorcode)));
}

void address_to_js(evm_val_t obj, struct sockaddr* addr) {
    evm_t *e = evm_runtime();
    char ip[INET6_ADDRSTRLEN];
    struct sockaddr_in* a4;
    struct sockaddr_in6* a6;
    int port;

    switch (addr->sa_family) {
    case AF_INET6: {
        a6 = (struct sockaddr_in6*)(addr);
        uv_inet_ntop(AF_INET6, &a6->sin6_addr, ip, sizeof ip);
        port = ntohs(a6->sin6_port);
        evm_prop_set(e, obj, "address", evm_mk_string(e, ip));
        evm_prop_set(e, obj, "family", evm_mk_string(e, "IPv6"));
        evm_prop_set(e, obj, "port", evm_mk_number(e, port));
        break;
    }

    case AF_INET: {
      a4 = (struct sockaddr_in*)(addr);
      uv_inet_ntop(AF_INET, &a4->sin_addr, ip, sizeof ip);
      port = ntohs(a4->sin_port);
      evm_prop_set(e, obj, "address", evm_mk_string(e, ip));
      evm_prop_set(e, obj, "family", evm_mk_string(e, "IPv4"));
      evm_prop_set(e, obj, "port", evm_mk_number(e, port));
      break;
    }

    default: {
      evm_prop_set(e, obj, "address", evm_mk_string(e, ""));
      break;
    }
    }
}

EVM_FUNCTION(evm_module_tcp_get_socket_name) {
    EVM_EPCV;
    uv_tcp_t *tcp_handle = evm_object_get_user_data(e, p);
    struct sockaddr_storage storage;
    int addrlen = sizeof(storage);
    struct sockaddr* const addr = (struct sockaddr*)(&storage);
    int err = uv_tcp_getsockname(tcp_handle, addr, &addrlen);
    if (err == 0)
    address_to_js(v[0], addr);
    EVM_RETURN(evm_mk_number(e, err));
}

EVM_FUNCTION(evm_module_tcp_create) {
    EVM_EPCV;
    evm_val_t obj = evm_object_create(e);
    tcp_object_init(e, obj);
    evm_prop_set(e, obj, "errname", evm_mk_native(e, evm_module_tcp_err_name, "errname", 0));
    evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_tcp_close, "close", EVM_VARARGS));
    evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_tcp_connect, "connect", EVM_VARARGS));
    evm_prop_set(e, obj, "bind", evm_mk_native(e, evm_module_tcp_bind, "bind", EVM_VARARGS));
    evm_prop_set(e, obj, "listen", evm_mk_native(e, evm_module_tcp_listen, "listen", EVM_VARARGS));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_tcp_write, "write", EVM_VARARGS));
    evm_prop_set(e, obj, "readStart", evm_mk_native(e, evm_module_tcp_read_start, "readStart", EVM_VARARGS));
    evm_prop_set(e, obj, "shutdown", evm_mk_native(e, evm_module_tcp_shutdown, "shutdown", EVM_VARARGS));
    evm_prop_set(e, obj, "setKeepAlive", evm_mk_native(e, evm_module_tcp_set_keep_alive, "setKeepAlive", 0));
    evm_prop_set(e, obj, "getsockname", evm_mk_native(e, evm_module_tcp_get_socket_name, "getsockname", 0));
    EVM_RETURN(obj);
}

void evm_module_tcp(evm_t *e) {
  evm_val_t obj = evm_object_create(e);
  evm_prop_set(e, obj, "create", evm_mk_native(e, evm_module_tcp_create, "create", 0));
  evm_module_add(e, "tcp", obj);
}
#endif
