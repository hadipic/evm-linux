TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR = $$PWD/../build
DESTDIR = $$PWD/../build

LIBS += -lpthread

DEFINES += EVM_USE_MODULE_EX

INCLUDEPATH += $$PWD/../../../components/zmalloc

include($$PWD/../../../qmake/common.pri)
include($$PWD/../../../qmake/lvgl.pri)
include($$PWD/../../../qmake/lv_png.pri)
include($$PWD/../../../qmake/lv_drivers.pri)
include($$PWD/../../../qmake/freertos.pri)
include($$PWD/../../../qmake/tuv.pri)

win32{
    INCLUDEPATH +=  $$PWD/../
}

contains(DEFINES, EVM_USE_JERRYSCRIPT) {
include($$PWD/../../../qmake/jerryscript.pri)
}

SOURCES += \
        main.c
