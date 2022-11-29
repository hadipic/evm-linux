//This is auto-generated file
#ifdef CONFIG_EVM_MODULE_SOCKET

#include "sys/socket.h"
#include "unistd.h"
#include "netdb.h"
#include "arpa/inet.h"
#include "evm_module.h"

static evm_val_t evm_module_socket_socket(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "iii", argc, v);
  cffi_args[0].i32 = socket(cffi_args[1].i32, cffi_args[2].i32, cffi_args[3].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "iiii");
}

static evm_val_t evm_module_socket_listen(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ii", argc, v);
  cffi_args[0].i32 = listen(cffi_args[1].i32, cffi_args[2].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "iii");
}

static evm_val_t evm_module_socket_connect(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "isi", argc, v);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(cffi_args[3].i32);
  addr.sin_addr.s_addr = inet_addr(cffi_args[2].s);
  cffi_args[0].i32 = connect(cffi_args[1].i32, &addr, sizeof(struct sockaddr));
  return evm_cffi_exec_ret(e, cffi_args[0], "iisi");
}

static evm_val_t evm_module_socket_send(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "ipii", argc, v);
  cffi_args[0].i64 = send(cffi_args[1].i32, cffi_args[2].p, cffi_args[3].i32, cffi_args[4].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "lipii");
}

static evm_val_t evm_module_socket_recv(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "ipii", argc, v);
  cffi_args[0].i64 = recv(cffi_args[1].i32, cffi_args[2].p, cffi_args[3].i32, cffi_args[4].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "lipii");
}

static evm_val_t evm_module_socket_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "i", argc, v);
  cffi_args[0].i32 = close(cffi_args[1].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "ii");
}


void evm_module_socket(evm_t *e) {
  evm_val_t obj = evm_object_create(e);
  evm_prop_set(e, obj, "socket", evm_mk_native(e, evm_module_socket_socket, "socket", 3));
  evm_prop_set(e, obj, "listen", evm_mk_native(e, evm_module_socket_listen, "listen", 2));
  evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_socket_connect, "connect", 3));
  evm_prop_set(e, obj, "send", evm_mk_native(e, evm_module_socket_send, "send", 4));
  evm_prop_set(e, obj, "recv", evm_mk_native(e, evm_module_socket_recv, "recv", 4));
  evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_socket_close, "close", 1));
  evm_prop_set(e, obj, "AF_INET", evm_mk_number(e, AF_INET));
  evm_prop_set(e, obj, "SOCK_STREAM", evm_mk_number(e, SOCK_STREAM));
  evm_module_add(e, "socket", obj);
}
#endif
