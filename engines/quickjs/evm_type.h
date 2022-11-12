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

#include <stdarg.h>
#include "quickjs-opcode.h"
#include "quickjs-atom.h"
#include "quickjs.h"

typedef JSContext evm_t;
typedef JSValue evm_val_t;

#define EVM_UNDEFINED JS_UNDEFINED

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
