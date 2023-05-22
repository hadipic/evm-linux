#include "evm_port_wifi.h"
#include <unistd.h>
#include <sys/fcntl.h>

int evm_port_wifi_connect(const char *ssid, const char *pwd) {
    return 1;
}

int evm_port_wifi_ip(char *ip) {
    return 1;
}

int evm_port_wifi_ssid(char *ssid) {
    return 1;
}
