#include "evm_module.h"
#ifdef EVM_USE_MODULE_CFFI

inline void evm_cffi_exec_param(evm_t *e, evm_cffi_val_t *cffi_vals, const char *signature, int argc, evm_val_t *v) {
    for (int i = 0; i < argc; i++) {
        switch (signature[i]) {
            case 'b': cffi_vals[i].i32 = evm_2_boolean(e, v[i]);break;
            case 'i': cffi_vals[i].i32 = evm_2_integer(e, v[i]);break;
            case 'l': cffi_vals[i].i64 = evm_2_integer(e, v[i]);break;
            case 'd': cffi_vals[i].f64 = evm_2_double(e, v[i]);break;
            case 'f': cffi_vals[i].f32 = evm_2_double(e, v[i]);break;
            case 's': cffi_vals[i].s = evm_2_string(e, v[i]);break;
            case 'p': cffi_vals[i].p = evm_2_invoke(e, v[i]);break;
            default: 
                evm_throw(e, evm_mk_string(e, "Unsupported cffi type"));
        }
    }
}

inline evm_val_t evm_cffi_exec_ret(evm_t *e, evm_cffi_val_t *cffi_vals, int argc, const char *signature) {
    evm_val_t ret = EVM_UNDEFINED;
    switch (signature[0]) {
        case 'b': ret = evm_mk_boolean(e, cffi_vals[0].i32);break;
        case 'i': ret = evm_mk_number(e, cffi_vals[0].i32);break;
        case 'l': ret = evm_mk_number(e, cffi_vals[0].i64);break;
        case 'd': ret = evm_mk_number(e, cffi_vals[0].f64);break;
        case 'f': ret = evm_mk_number(e, cffi_vals[0].f32);break;
        case 's': ret = evm_mk_string(e, cffi_vals[0].s);
        case 'v': ret = EVM_UNDEFINED;break;
        case 'p': ret = evm_mk_invoke(e, cffi_vals[0].p);break;
        default: 
            evm_throw(e, evm_mk_string(e, "Unsupported cffi type"));
    }

    for (int i = 1; i < argc; i++) {
        switch (signature[i]) {
            case 's':
                evm_string_free(e, cffi_vals[i].s); break;
        }
    }
    return ret;
}
#endif
