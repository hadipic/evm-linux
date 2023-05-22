#ifndef __EVM_PORT_WIFI_H__
#define __EVM_PORT_WIFI_H__

#include "evm_module.h"

int evm_port_wifi_connect(const char *ssid, const char *pwd);
int evm_port_wifi_ip(char *ip);
int evm_port_wifi_ssid(char *ssid);

#endif
