#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_CFFI

void evm_cffi_exec_param(evm_t *e, evm_cffi_val_t *cffi_vals, const char *signature, int argc, evm_val_t *v) {
    for (int i = 0; i < argc; i++) {
        switch (signature[i]) {
            case 'b': cffi_vals[i].i32 = evm_2_boolean(e, v[i]);break;
            case 'i': cffi_vals[i].i32 = evm_2_integer(e, v[i]);break;
            case 'l': cffi_vals[i].i64 = evm_2_integer(e, v[i]);break;
            case 'd': cffi_vals[i].f64 = evm_2_double(e, v[i]);break;
            case 'f': cffi_vals[i].f32 = evm_2_double(e, v[i]);break;
            case 's': cffi_vals[i].s = evm_2_string(e, v[i]);break;
            case 'p': cffi_vals[i].p = evm_object_get_user_data(e, v[i]);break;
            default: 
                evm_throw(e, evm_mk_string(e, "Unsupported cffi type"));
        }
    }
}

evm_val_t evm_cffi_exec_ret(evm_t *e, evm_cffi_val_t cffi_val, const char *signature) {
    switch (signature[0]) {
        case 'b': return evm_mk_boolean(e, cffi_val.i32);
        case 'i': return evm_mk_number(e, cffi_val.i32);
        case 'l': return evm_mk_number(e, cffi_val.i64);
        case 'd': return evm_mk_number(e, cffi_val.f64);
        case 'f': return evm_mk_number(e, cffi_val.f32);
        case 's': return evm_mk_string(e, cffi_val.s);
        case 'v': return EVM_UNDEFINED;
        case 'p': return evm_object_create_user_data(e, cffi_val.p);
        default: 
            evm_throw(e, evm_mk_string(e, "Unsupported cffi type"));
    }
}
#endif
