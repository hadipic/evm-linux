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

#include "quickvm.h"

#define QVM_MEM_SIZE    (10 * 1000 * 1024)
#define QVM_STACK_SIZE  (sizeof(qvm_value_t) * 10000)
#define QVM_REF_SIZE    100

typedef qvm_state_t evm_t;
typedef qvm_value_t evm_val_t;

#define EVM_UNDEFINED qvm_undefined

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
