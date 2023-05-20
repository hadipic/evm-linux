
#include "evm_module.h"
#include "evm_port_uart.h"

static void uart_setup(evm_t *e, evm_port_uart_t *info, evm_val_t obj) {
    evm_val_t val = evm_prop_get(e, obj, "port");
    char *port = evm_2_string(e, val);
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "port");
    info->baudrate = evm_2_integer(e, val);
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "databits");
    info->databits = evm_2_integer(e, val);
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "stopbits");
    info->stopbits = evm_2_integer(e, val);
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "parity");
    info->parity = evm_2_integer(e, val);
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "callback");
    info->callback = val;

    evm_port_uart_setup(info, port);
    evm_string_free(e, port);
}

EVM_FUNCTION(write){
    evm_port_uart_t *info = evm_object_get_user_data(e, v[0]);
    if( argc > 0 && info ) {
        char *buf;
        int len;
        if( evm_is_buffer(e, v[0]) ) {
            buf = evm_buffer_addr(e, v[0]);
            len = evm_buffer_len(e, v[0]);
            evm_port_uart_write(info, buf, len);
        } else if( evm_is_string(e, v[0]) ) {
            buf = evm_2_string(e, v[0]);
            len = evm_string_len(e, v[0]);
            evm_port_uart_write(info, buf, len);
            evm_string_free(e, buf);
        } else {
            return EVM_UNDEFINED;
        }
    }
}

/**
 * @brief create({
 *  port: "/dev/ttyS0",
 *  baudrate: 115200,
 *  databits: 8,
 *  stopbits: 1,
 *  parity: "none",
 *  callback: <function>
 * })
 * @return
 */
EVM_FUNCTION(create){
    EVM_UNUSED(e);
    evm_port_uart_t *info = evm_malloc(sizeof (evm_port_uart_t));
    EVM_ASSERT(info);
    evm_val_t obj = evm_object_create_user_data(e, info);
    uart_setup(e, info, v[0]);
    return obj;
}

void evm_module_uart(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "create", evm_mk_native(e, create, "create", EVM_VARARGS));
    evm_prop_set(e, obj, "write", evm_mk_native(e, write, "write", EVM_VARARGS));
    evm_module_add(e, "@native.uart", obj);
    evm_val_free(e, obj);
}
