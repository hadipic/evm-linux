TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR = $$PWD/../build
DESTDIR = $$PWD/../build

LIBS += -lpthread

DEFINES += EVM_USE_MODULE_EX
DEFINES += EVM_USE_JERRYSCRIPT

INCLUDEPATH += $$PWD/../../../components/zmalloc

include($$PWD/../../../qmake/common.pri)
include($$PWD/../../../qmake/lvgl.pri)
include($$PWD/../../../qmake/lv_png.pri)
include($$PWD/../../../qmake/lv_drivers.pri)
include($$PWD/../../../qmake/freertos.pri)
include($$PWD/../../../qmake/tuv.pri)
include($$PWD/../../../qmake/iotjs.pri)
include($$PWD/../../../qmake/jerryscript.pri)
win32{
    INCLUDEPATH +=  $$PWD/../
}

SOURCES += \
        main.c
