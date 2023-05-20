TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR = $$PWD/../build
DESTDIR = $$PWD/../build

LIBS += -lpthread

DEFINES += QVM_USE_QUICKJS_JS_BC_C_SOURCE
DEFINES += EVM_USE_LUAT

include($$PWD/../pris/common.pri)
include($$PWD/../pris/lvgl.pri)
include($$PWD/../pris/lv_png.pri)
include($$PWD/../pris/lv_drivers.pri)
include($$PWD/../pris/freertos.pri)

win32{
    INCLUDEPATH +=  $$PWD/../
}

include($$PWD/../pris/quickjs.pri)

SOURCES += \
        main.c
