TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += EVM_USE_MUJS

DEFINES += CONFIG_EVM_MODULE_FS
DEFINES += CONFIG_EVM_MODULE_PROCESS
DEFINES += CONFIG_EVM_MODULE_EVENT
DEFINES += CONFIG_EVM_MODULE_DNS
DEFINES += CONFIG_EVM_MODULE_TIMERS
DEFINES += CONFIG_EVM_MODULE_BUFFER
DEFINES += CONFIG_EVM_MODULE_ASSERT
DEFINES += CONFIG_EVM_MODULE_CFFI
DEFINES += CONFIG_EVM_MODULE_LIBC
DEFINES += CONFIG_EVM_MODULE_NET
DEFINES += CONFIG_EVM_MODULE_ADC
DEFINES += CONFIG_EVM_MODULE_GPIO
DEFINES += CONFIG_EVM_MODULE_I2C
DEFINES += CONFIG_EVM_MODULE_UART
DEFINES += CONFIG_EVM_MODULE_REPL

LIBS += -lpthread
LIBS += -lrt
INCLUDEPATH += $$PWD/../../../engines/mujs
INCLUDEPATH += $$PWD/../../../modules/iotjs/common

INCLUDEPATH += $$PWD/../../../include

contains(DEFINES, EVM_USE_MUJS){
    INCLUDEPATH += $$PWD/../../../engines/mujs
    INCLUDEPATH += $$PWD/../../../engines/mujs/mujs

    SOURCES += \
        $$PWD/../../../engines/mujs/evm.c

    SOURCES += \
        $$PWD/../../../engines/mujs/mujs/one.c
}

# freertos
INCLUDEPATH += $$PWD/../../../components/freertos/include
INCLUDEPATH += $$PWD/../../../components/freertos/portable/ThirdParty/GCC/Posix
INCLUDEPATH += $$PWD/../../../components/freertos/portable/ThirdParty/GCC/Posix/utils

SOURCES += \
    ../../../components/freertos/croutine.c \
    ../../../components/freertos/event_groups.c \
    ../../../components/freertos/heap_4.c \
    ../../../components/freertos/list.c \
    ../../../components/freertos/queue.c \
    ../../../components/freertos/stream_buffer.c \
    ../../../components/freertos/tasks.c \
    ../../../components/freertos/timers.c \
    ../../../components/freertos/portable/ThirdParty/GCC/Posix/port.c \
    ../../../components/freertos/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c

SOURCES += \
    ../../../modules/iotjs/common/evm_module_process.c \
    ../../../modules/iotjs/common/evm_module.c \
    ../../../modules/iotjs/common/evm_module_events.c \
    ../../../modules/iotjs/common/evm_module_buffer.c \
    ../../../modules/iotjs/common/evm_module_cffi.c \
    ../../../modules/iotjs/common/evm_module_libc.c \
    ../../../modules/iotjs/common/evm_module_assert.c \
    ../../../modules/iotjs/common/evm_module_fs.c \
    ../../../modules/iotjs/common/evm_module_dns.c \
    ../../../modules/iotjs/common/evm_module_adc.c \
    ../../../modules/iotjs/common/evm_module_gpio.c \
    ../../../modules/iotjs/common/evm_module_i2c.c \
    ../../../modules/iotjs/common/evm_module_timers.c \
    ../../../modules/iotjs/common/evm_module_uart.c \
    ../../../modules/iotjs/common/evm_module_repl.c \
    ../../../modules/iotjs/common/evm_module_network.c

SOURCES += \
    ../../../modules/iotjs/linux/linux_module_adc.c \
    ../../../modules/iotjs/linux/linux_module_event.c \
    ../../../modules/iotjs/linux/linux_module_i2c.c \
    ../../../modules/iotjs/linux/linux_module_gpio.c \
    ../../../modules/iotjs/linux/linux_module_timers.c \
    ../../../modules/iotjs/linux/linux_module_uart.c \
    ../../../modules/iotjs/linux/linux_module_repl.c

SOURCES += \
    ../../../modules/iotjs/linux/evm_main.c



SOURCES += \
        main.c
