/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/

#ifndef EVM_TYPE_H
#define EVM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "jsi.h"
#include "jsvalue.h"

typedef js_State evm_t;
typedef js_Value evm_val_t;

typedef evm_val_t (*evm_native_t)(evm_t *e, evm_val_t pthis, int argc, evm_val_t *v);

#define EVM_UNDEFINED   (evm_val_t){ .type = JS_TUNDEFINED }

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
