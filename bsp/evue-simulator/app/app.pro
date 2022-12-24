TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

#DEFINES += EVM_USE_PIKASCRIPT
#DEFINES += EVM_USE_QUICKJS
#DEFINES += EVM_USE_MUJS
#DEFINES += EVM_USE_UPY
DEFINES += EVM_USE_QUICKVM
#DEFINES += EVM_USE_QUICKVM_DEBUG

include($$PWD/../pris/common.pri)
include($$PWD/../pris/tuv.pri)
include($$PWD/../pris/lvgl.pri)
include($$PWD/../pris/lv_png.pri)
include($$PWD/../pris/lv_drivers.pri)

win32{
    INCLUDEPATH +=  $$PWD/../
}

if( contains(DEFINES, EVM_USE_PIKASCRIPT) ) {
    DEFINES += PIKASCRIPT=1
    DEFINES += PIKA_CONFIG_ENABLE=1
    include($$PWD/../pris/pikascript.pri)
}

if( contains(DEFINES, EVM_USE_QUICKJS) ) {
    include($$PWD/../pris/quickjs.pri)
}

if( contains(DEFINES, EVM_USE_MUJS) ) {
    include($$PWD/../pris/mujs.pri)
}

if( contains(DEFINES, EVM_USE_UPY) ) {
    include($$PWD/../pris/micropy.pri)
}

if( contains(DEFINES, EVM_USE_QUICKVM) ) {
    include($$PWD/../pris/quickvm.pri)
}

SOURCES += \
        main.c
