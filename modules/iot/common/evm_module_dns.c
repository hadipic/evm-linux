#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_DNS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//dns.lookup(hostname[, options], callback)
static evm_val_t evm_module_dns_lookup(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    if( argc < 1 || !evm_is_string(e, v[0]) ) {
        return evm_mk_undefined(e);
    }
    struct hostent *hostinfo;
    const char *hostname = evm_2_string(e, v[0]);
    hostinfo = gethostbyname (hostname);

    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[4];
        args[0] = *(v + 1);
        args[1] = evm_mk_number(e, errno);
        args[2] = evm_string_create(e, inet_ntoa(*((struct in_addr*)hostinfo->h_addr_list[0])));
        args[3] = evm_mk_number(e, hostinfo->h_addrtype);
        evm_module_next_tick(e, 4, args);
    }
    return evm_mk_undefined(e);
}

evm_err_t evm_module_dns(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "lookup", evm_mk_native(e, evm_module_dns_lookup, "lookup", 3));
    evm_module_add(e, "dns", obj);
    return ec_ok;
}

#endif
