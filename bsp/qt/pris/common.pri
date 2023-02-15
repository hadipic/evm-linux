# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/iot/common

DEFINES += CONFIG_EVM_MODULE_FS
DEFINES += CONFIG_EVM_MODULE_TIMERS
DEFINES += CONFIG_EVM_MODULE_BUFFER
DEFINES += CONFIG_EVM_MODULE_ASSERT
DEFINES += CONFIG_EVM_MODULE_CFFI
DEFINES += CONFIG_EVM_MODULE_LIBC
DEFINES += CONFIG_EVM_MODULE_ADC
DEFINES += CONFIG_EVM_MODULE_GPIO
DEFINES += CONFIG_EVM_MODULE_I2C
DEFINES += CONFIG_EVM_MODULE_UART
#DEFINES += CONFIG_EVM_MODULE_REPL
DEFINES += CONFIG_EVM_MODULE_SOCKET


SOURCES += \
    ../../../modules/iot/common/evm_module_process.c \
    ../../../modules/iot/common/evm_module.c \
    ../../../modules/iot/common/evm_module_cffi.c \
    ../../../modules/iot/common/evm_module_adc.c \
    ../../../modules/iot/common/evm_module_timers.c \
    ../../../modules/iot/common/evm_module_uart.c \
    ../../../modules/iot/common/evm_module_repl.c \
    ../../../modules/iot/common/iot_adc.c \
    ../../../modules/iot/common/iot_system.c \
    ../../../modules/iot/common/iot_uv.c



SOURCES += \
    ../../../modules/iot/linux/evm_main.c
