/****************************************************************************
**
** Copyright (C) 2022 @武汉市凡迈科技有限公司
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  Version	: 3.2
**  Email	: scriptiot@aliyun.com
**  Website	: https://gitee.com/scriptiot
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
