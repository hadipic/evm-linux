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

contains(DEFINES, EVM_USE_QUICKJS) {
DEFINES += CONFIG_EVM_MODULE_LVGL
SOURCES += \
    ../../../modules/iot/gui/lvgl/evm_module_lvgl.c
}


SOURCES += \
    ../../../modules/iot/common/evm_module_process.c \
    ../../../modules/iot/common/evm_module.c \
    ../../../modules/iot/common/evm_module_events.c \
    ../../../modules/iot/common/evm_module_buffer.c \
    ../../../modules/iot/common/evm_module_cffi.c \
    ../../../modules/iot/common/evm_module_libc.c \
    ../../../modules/iot/common/evm_module_assert.c \
    ../../../modules/iot/common/evm_module_fs.c \
    ../../../modules/iot/common/evm_module_dns.c \
    ../../../modules/iot/common/evm_module_adc.c \
    ../../../modules/iot/common/evm_module_gpio.c \
    ../../../modules/iot/common/evm_module_i2c.c \
    ../../../modules/iot/common/evm_module_timers.c \
    ../../../modules/iot/common/evm_module_uart.c \
    ../../../modules/iot/common/evm_module_repl.c \
    ../../../modules/iot/common/evm_module_network.c

SOURCES += \
    ../../../modules/iot/linux/linux_module_adc.c \
    ../../../modules/iot/linux/linux_module_event.c \
    ../../../modules/iot/linux/linux_module_i2c.c \
    ../../../modules/iot/linux/linux_module_gpio.c \
    ../../../modules/iot/linux/linux_module_timers.c \
    ../../../modules/iot/linux/linux_module_uart.c \
    ../../../modules/iot/linux/linux_module_repl.c

SOURCES += \
    ../../../modules/iot/linux/evm_main.c
