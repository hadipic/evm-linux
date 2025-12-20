/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include "evm_module.h"
#ifdef EVM_USE_MODULE_CFFI

inline void evm_cffi_exec_param(evm_t *e, evm_cffi_val_t *cffi_vals, const char *signature, int argc, evm_val_t *v) {
    for (int i = 0; i < argc; i++) {
        switch (signature[i]) {
            case 'b': cffi_vals[i].i32 = evm_2_boolean(e, v[i]);break;
            case 'i': cffi_vals[i].i32 = evm_2_double(e, v[i]);break;
            case 'u': cffi_vals[i].i32 = (uint32_t)evm_2_double(e, v[i]);break;
            case 'l': cffi_vals[i].i64 = evm_2_double(e, v[i]);break;
            case 'd': cffi_vals[i].f64 = evm_2_double(e, v[i]);break;
            case 'f': cffi_vals[i].f32 = evm_2_double(e, v[i]);break;
            case 's': cffi_vals[i].s = evm_2_string(e, v[i]);break;
            case 'p': cffi_vals[i].p = evm_2_invoke(e, v[i]);break;
            default: 
                evm_throw(e, evm_mk_string(e, "Unsupported cffi type"));
        }
    }
}

inline evm_val_t evm_cffi_exec_ret(evm_t *e, evm_cffi_val_t* cffi_vals, const char *signature, int argc) {
    evm_val_t res;
    switch (signature[0]) {
        case 'b': res = evm_mk_boolean(e, cffi_vals[0].i32);break;
        case 'i': res = evm_mk_number(e, cffi_vals[0].i32);break;
        case 'u': res = evm_mk_number(e, cffi_vals[0].i32);break;
        case 'l': res = evm_mk_number(e, cffi_vals[0].i64);break;
        case 'd': res = evm_mk_number(e, cffi_vals[0].f64);break;
        case 'f': res = evm_mk_number(e, cffi_vals[0].f32);break;
        case 's': res = evm_mk_string(e, cffi_vals[0].s);break;
        case 'v': res = EVM_UNDEFINED;break;
        case 'p': res = evm_mk_invoke(e, cffi_vals[0].p);break;
        default:
            evm_throw(e, evm_mk_string(e, "Unsupported cffi type"));
    }

    for (int i = 1; i < argc; i++) {
        switch (signature[i]) {
            case 's': evm_string_free(e, cffi_vals[i].s);break;
        }
    }

    return res;
}
#endif
