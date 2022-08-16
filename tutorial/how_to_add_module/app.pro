TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += EVM_USE_DUKTAPE

contains(DEFINES, EVM_USE_MUJS){
    INCLUDEPATH += $$PWD/../../engines/mujs
    INCLUDEPATH += $$PWD/../../engines/mujs/mujs

    SOURCES += \
        $$PWD/../../engines/mujs/evm.c

    SOURCES += \
        $$PWD/../../engines/mujs/mujs/one.c
}

contains(DEFINES, EVM_USE_DUKTAPE){
    INCLUDEPATH += $$PWD/../../engines/duktape
    INCLUDEPATH += $$PWD/../../engines/duktape/duktape/src

    SOURCES += \
        $$PWD/../../engines/duktape/evm.c

    SOURCES += \
        $$PWD/../../engines/duktape/duktape/src/duktape.c
}

SOURCES += \
        main.c


