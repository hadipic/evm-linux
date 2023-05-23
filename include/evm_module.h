/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
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

extern void evm_main(char *filename);
extern void evm_module_init(evm_t *env);
extern const char *evm_get_app_path(void);

#ifdef __cplusplus
}
#endif


#endif
