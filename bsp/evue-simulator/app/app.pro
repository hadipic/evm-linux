TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR = $$PWD/../build
DESTDIR = $$PWD/../build

LIBS += -lpthread

include($$PWD/../pris/common.pri)
include($$PWD/../pris/lvgl.pri)
include($$PWD/../pris/lv_png.pri)
include($$PWD/../pris/lv_drivers.pri)

unix{
include($$PWD/../pris/tuv.pri)
}

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

if( contains(DEFINES, EVM_USE_TINYSCRIPT) ) {
    include($$PWD/../pris/tinyscript.pri)
}

if( contains(DEFINES, EVM_USE_DUKTAPE) ) {
    include($$PWD/../pris/duktape.pri)
}

SOURCES += \
        main.c
