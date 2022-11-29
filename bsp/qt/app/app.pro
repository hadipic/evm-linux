TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

#DEFINES += EVM_USE_PIKASCRIPT
#DEFINES += EVM_USE_QUICKJS
DEFINES += EVM_USE_MUJS
#DEFINES += EVM_USE_MICROPY

include($$PWD/../pris/common.pri)

if( contains(DEFINES, EVM_USE_PIKASCRIPT) ) {
    include($$PWD/../pris/pikascript.pri)
}

if( contains(DEFINES, EVM_USE_QUICKJS) ) {
    include($$PWD/../pris/quickjs.pri)
}

if( contains(DEFINES, EVM_USE_MUJS) ) {
    include($$PWD/../pris/mujs.pri)
}

if( contains(DEFINES, EVM_USE_MICROPY) ) {
    include($$PWD/../pris/micropy.pri)
}

SOURCES += \
        main.c
