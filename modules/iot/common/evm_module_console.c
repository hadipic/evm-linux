#include "evm_module.h"

extern char iot_platform_getchar(void);

EVM_FUNCTION(console_log) {
    EVM_EPCV;
    for (int i; i < argc; i++) {
        char *s = evm_2_string(e, v[i]);
        printf("%s", s);
        evm_string_free(e, s);
    }
    printf("\r\n");
    EVM_RETURN(evm_mk_undefined(e))
}

//write(buf)
EVM_FUNCTION(console_write) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[0]);
    printf("%s", s);
    evm_string_free(e, s);
    EVM_RETURN(evm_mk_undefined(e))
}

//getc()
EVM_FUNCTION(console_getc) {
    EVM_EPCV;
    int c = iot_platform_getchar();
    EVM_RETURN(evm_mk_number(e, c));
}

void evm_module_console(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "log", evm_mk_native(e, console_log, "log", EVM_VARARGS));
    evm_prop_set(e, obj, "getc", evm_mk_native(e, console_getc, "getc", EVM_VARARGS));
    evm_prop_set(e, obj, "write", evm_mk_native(e, console_write, "write", EVM_VARARGS));
    evm_global_set(e, "console", obj);
}

