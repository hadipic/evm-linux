/****************************************************************************
**
** Copyright (C) 2022 @武汉市凡迈科技有限公司
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  Version	: 1.0
**  Email	: scriptiot@aliyun.com
**  Website	: https://gitee.com/scriptiot
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_NETWORK_H
#define EVM_MODULE_NETWORK_H

#include "evm.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <unistd.h>

void net_gethostbyname(char * hostName, uint32_t* out_ip_addr);
int net_createsocket(int socketType, uint32_t host, int16_t port, evm_val_t options);

#ifdef __cplusplus
}
#endif

#endif
