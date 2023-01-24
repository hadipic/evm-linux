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

#include "dataArg.h"
#include "PikaObj.h"

typedef PikaObj evm_t;
typedef Arg* evm_val_t;

extern Arg _evm_pika_undefined;

#define EVM_UNDEFINED   &_evm_pika_undefined

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
