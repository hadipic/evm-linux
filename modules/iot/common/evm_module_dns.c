/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifdef EVM_USE_MODULE_DNS

#include "linux_uv.h"

#define AI_ADDRCONFIG    0x0400
#define AI_V4MAPPED      0x0800

char* getaddrinfo_error_str(int status) {
  switch (status) {
    case UV__EAI_ADDRFAMILY:
      return "EAI_ADDRFAMILY, address family for hostname not supported";
    case UV__EAI_AGAIN:
      return "EAI_AGAIN, temporary failure in name resolution";
    case UV__EAI_BADFLAGS:
      return "EAI_BADFLAGS, bad flags";
    case UV__EAI_FAIL:
      return "EAI_FAIL, Non-recoverable failure in name resolution";
    case UV__EAI_FAMILY:
      return "EAI_FAMILY, family not supported";
    case UV__EAI_CANCELED:
      return "EAI_CANCELED, request canceled";
    case UV__EAI_MEMORY:
      return "EAI_MEMORY, memory allocation failure";
    case UV__EAI_NODATA:
      return "EAI_NODATA, no address association with hostname";
    case UV__EAI_NONAME:
      return "EAI_NONAME, name or service not known";
    case UV__EAI_OVERFLOW:
      return "EAI_OVERFLOW, argument buffer overflow";
    case UV__EAI_SERVICE:
      return "EAI_SERVICE, service not supported";
    case UV__EAI_SOCKTYPE:
      return "EAI_SOCKTYPE, socktype not supported";
    case UV__EAI_PROTOCOL:
      return "EAI_PROTOCOL, unknown error";
    default:
      return "unknown error";
  }
}

static void after_get_addr_info(uv_getaddrinfo_t* req, int status,
                                struct addrinfo* res) {
  evm_t *e = evm_runtime();
  size_t argc = 0;
  evm_val_t args[3] = { 0 };

  if (status == 0 && res != NULL) {
    char ip[INET6_ADDRSTRLEN];
    int family;
    const char* addr;
    struct addrinfo* info;

    /* search for the first AF_INET entry */
    for (info = res; info != NULL; info = info->ai_next) {
      if (info->ai_family == AF_INET) {
        break;
      }
    }

    if (info == NULL) {
      /* Did not find an AF_INET addr, using the first one */
      info = res;
    }

    EVM_ASSERT(info != NULL);

    if (info->ai_family == AF_INET) {
      struct sockaddr_in* sockaddr = (struct sockaddr_in*)(info->ai_addr);
      addr = (char*)(&(sockaddr->sin_addr));
      family = 4;
    } else {
      struct sockaddr_in6* sockaddr = (struct sockaddr_in6*)(info->ai_addr);
      addr = (char*)(&(sockaddr->sin6_addr));
      family = 6;
    }

    int err = uv_inet_ntop(info->ai_family, addr, ip, INET6_ADDRSTRLEN);
    if (err) {
      ip[0] = 0;
      args[argc++] = evm_throw(e, evm_mk_string(e, "EAFNOSUPPORT, DNS could not resolve hostname"));
    } else {
      args[argc++] = evm_mk_null(e);
    }

    args[argc++] = evm_mk_string(e, ip);
    args[argc++] = evm_mk_number(e, family);
  } else {
    args[argc++] = evm_throw(e, evm_mk_string(e, getaddrinfo_error_str(status)));
  }

  uv_freeaddrinfo(res);

  // Make the callback into JavaScript
  evm_val_t jcallback = *IOT_UV_REQUEST_CALLBACK(req);
  evm_call_free(e, jcallback, EVM_UNDEFINED, argc, args);
  for (size_t i = 0; i < argc; i++) {
    evm_val_free(e, args[i]);
  }

  iot_uv_request_destroy((uv_req_t*)req);
}

EVM_FUNCTION(get_address_info) {
  EVM_EPCV;
  char *hostname = evm_2_string(e, v[0]);
  int option = 0;
  if(argc > 1)
      option = evm_2_integer(e, v[1]);
  int flags = 0;
  if(argc > 2)
      flags = evm_2_integer(e, v[2]);
  int error = 0;
  evm_val_t jcallback = EVM_UNDEFINED;
  if(argc > 3)
      jcallback = evm_val_duplicate(e, v[3]);

  int family;
  if (option == 0) {
#if defined(__NUTTX__) || defined(__TIZENRT__)
    family = AF_INET;
#else
    family = AF_UNSPEC;
#endif
  } else if (option == 4) {
    family = AF_INET;
  } else if (option == 6) {
    family = AF_INET6;
  } else {
    evm_string_free(e, hostname);
    return evm_throw(e, evm_mk_string(e, "bad address family"));
  }

#if defined(__NUTTX__)
  char ip[INET6_ADDRSTRLEN] = "";
  const char* hostname_data = iotjs_string_data(&hostname);

  if (strcmp(hostname_data, "localhost") == 0) {
    strncpy(ip, "127.0.0.1", strlen("127.0.0.1") + 1);
  } else {
    struct sockaddr_in addr;

    if (inet_pton(family, hostname_data, &(addr.sin_addr)) == 1) {
      inet_ntop(family, &(addr.sin_addr), ip, INET6_ADDRSTRLEN);
    } else {
      error = EAFNOSUPPORT;
    }
  }

  size_t argc = 0;
  jerry_value_t args[3] = { 0 };

  if (error) {
    args[argc++] = iotjs_jval_create_error_without_error_flag(
        "EAFNOSUPPORT, could not resolve hostname");
  } else {
    args[argc++] = jerry_create_null();
  }

  args[argc++] = jerry_create_string_from_utf8((const jerry_char_t*)ip);
  args[argc++] = jerry_create_number(option);

  iotjs_invoke_callback(jcallback, jerry_create_undefined(), args, argc);
  for (size_t i = 0; i < argc; i++) {
    jerry_release_value(args[i]);
  }
  IOTJS_UNUSED(flags);
#else
  uv_req_t* req_addr =
      iot_uv_request_create(sizeof(uv_getaddrinfo_t), jcallback, 0);

  static const struct addrinfo empty_hints;
  struct addrinfo hints = empty_hints;
  hints.ai_family = family;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = flags;

  error = uv_getaddrinfo(uv_default_loop(),
                         (uv_getaddrinfo_t*)req_addr, after_get_addr_info,
                         hostname, NULL, &hints);

  if (error) {
    iot_uv_request_destroy(req_addr);
  }
#endif


  evm_string_free(e, hostname);

  return evm_mk_number(e, error);
}


void evm_module_dns(evm_t *e) {
  evm_val_t dns = evm_object_create(e);
  evm_prop_set(e, dns, IOT_MAGIC_STRING_GETADDRINFO, evm_mk_native(e, get_address_info, IOT_MAGIC_STRING_GETADDRINFO, EVM_VARARGS));
  evm_prop_set(e, dns, "AI_ADDRCONFIG", evm_mk_number(e, AI_ADDRCONFIG));
  evm_prop_set(e, dns, "AI_ADDRCONFIG", evm_mk_number(e, AI_V4MAPPED));
  evm_module_add(e, "@native.dns", dns);
}
#endif
