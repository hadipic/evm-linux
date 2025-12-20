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
#ifndef EVM_MODULE_H
#define EVM_MODULE_H

#include "evm.h"
#include "zmalloc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union  {
    void *p; 
    char *s; 
    double f64;
    float f32; 
    int32_t i32; 
    int64_t i64;
} evm_cffi_val_t;
extern void evm_cffi_exec_param(evm_t *e, evm_cffi_val_t *cffi_vals, const char *signature, int argc, evm_val_t *v);
extern evm_val_t evm_cffi_exec_ret(evm_t *e, evm_cffi_val_t *cffi_val, const char *signature, int argc);

EVM_API void evm_module_init(evm_t *env);
EVM_API void evm_module_init_ex(evm_t *env);
EVM_API evm_t *evm_runtime(void);
EVM_API const char *evm_get_app_path(void);
EVM_API void evm_loop();

#ifdef EVM_USE_LOG
#define EVM_LOG(...) printf("[%s][%s][%d]:%s,%d\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define EVM_LOG(...)
#endif

#ifdef __cplusplus
}
#endif


#endif
