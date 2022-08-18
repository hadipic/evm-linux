TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += EVM_USE_MUJS
DEFINES += CONFIG_EVM_MODULE_CFFI

INCLUDEPATH += $$PWD/../../include

SOURCES += \
    $$PWD/../../modules/iotjs/common/evm_module.c \
    $$PWD/../../modules/iotjs/common/evm_module_cffi.c

contains(DEFINES, EVM_USE_MUJS){
    INCLUDEPATH += $$PWD/../../engines/mujs
    INCLUDEPATH += $$PWD/../../engines/mujs/mujs

    SOURCES += \
        $$PWD/../../engines/mujs/evm.c

    SOURCES += \
        $$PWD/../../engines/mujs/mujs/one.c
}

contains(DEFINES, EVM_USE_QUICKJS){
    DEFINES += CONFIG_VERSION=\\\"2021-03-27\\\"
    INCLUDEPATH += $$PWD/../../engines/quickjs
    INCLUDEPATH += $$PWD/../../engines/quickjs/quickjs

    SOURCES += \
        $$PWD/../../engines/quickjs/evm.c

    SOURCES += \
        $$PWD/../../engines/quickjs/quickjs/libregexp.c \
        $$PWD/../../engines/quickjs/quickjs/libunicode.c \
        $$PWD/../../engines/quickjs/quickjs/quickjs.c \
        $$PWD/../../engines/quickjs/quickjs/cutils.c
}

SOURCES += \
        main.c


