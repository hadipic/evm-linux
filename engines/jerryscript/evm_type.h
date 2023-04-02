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

#include <stdarg.h>
#include "jerryscript.h"

typedef jerry_context_t evm_t;
typedef jerry_value_t evm_val_t;

typedef jerry_external_handler_t evm_native_t;

#define EVM_UNDEFINED jerry_undefined()

#define EVM_FUNCTION(name)                           \
  static jerry_value_t name(const jerry_call_info_t *call_info_p,   \
                            const jerry_value_t v[], \
                            const jerry_length_t argc)

#define EVM_EPCV evm_t *e = NULL; const evm_val_t *p = &call_info_p->this_value;
#define EVM_RETURN(x)   return x;
#define EVM_RETURN_VAL(x)   return x;
#define EVM_VARARGS 0

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
