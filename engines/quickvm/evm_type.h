/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_TYPE_H
#define EVM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tinyscript.h"

#define TS_MEM_SIZE (1000 * 1024)
#define TS_STACK_SIZE (1024)

typedef ts_runtime_t evm_t;
typedef ts_value_t evm_val_t;
typedef ts_native_t evm_native_t;

#define EVM_UNDEFINED VAL_UNDEFINED

#define EVM_FUNCTION(name)                                \
  static evm_val_t name(evm_t *e,   \
                            evm_val_t p,   \
                            int argc, \
                            evm_val_t *v)

#define EVM_EPCV
#define EVM_RETURN(x)   return x;
#define EVM_RETURN_VAL(x)   return x;
#define EVM_VARARGS 0

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
