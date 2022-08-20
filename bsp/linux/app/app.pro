TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += EVM_USE_MUJS

DEFINES += CONFIG_EVM_MODULE_FS
DEFINES += CONFIG_EVM_MODULE_PROCESS
DEFINES += CONFIG_EVM_MODULE_EVENTS
DEFINES += CONFIG_EVM_MODULE_DNS
DEFINES += CONFIG_EVM_MODULE_TIMERS
DEFINES += CONFIG_EVM_MODULE_BUFFER
DEFINES += CONFIG_EVM_MODULE_ASSERT
DEFINES += CONFIG_EVM_MODULE_CFFI
DEFINES += CONFIG_EVM_MODULE_LIBC
DEFINES += CONFIG_EVM_MODULE_NET

LIBS += -lpthread
LIBS += -lrt
INCLUDEPATH += $$PWD/../../../engines/mujs
INCLUDEPATH += $$PWD/../../../modules/iotjs/common
INCLUDEPATH += $$PWD/../../../components/webclient/inc
INCLUDEPATH += $$PWD/../../../include

contains(DEFINES, EVM_USE_MUJS){
    INCLUDEPATH += $$PWD/../../../engines/mujs
    INCLUDEPATH += $$PWD/../../../engines/mujs/mujs

    SOURCES += \
        $$PWD/../../../engines/mujs/evm.c

    SOURCES += \
        $$PWD/../../../engines/mujs/mujs/one.c
}

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
    ../../../modules/iotjs/common/evm_module_network.c

SOURCES += \
    ../../../modules/iotjs/linux/evm_main.c \
    ../../../modules/iotjs/linux/evm_module_timers.c



SOURCES += \
        main.c
