TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR = $$PWD/../build
DESTDIR = $$PWD/../build

LIBS += -lpthread

DEFINES += EVM_USE_MODULE_EX
DEFINES += EVM_USE_JERRYSCRIPT
DEFINES += JERRY_LINE_INFO=1

INCLUDEPATH += $$PWD/../../../components/zmalloc

include($$PWD/../../../qmake/common.pri)
include($$PWD/../../../qmake/lvgl.pri)
include($$PWD/../../../qmake/lv_png.pri)
include($$PWD/../../../qmake/lv_drivers.pri)
unix{
include($$PWD/../../../qmake/tuv.pri)
include($$PWD/../../../qmake/iotjs.pri)
}

include($$PWD/../../../qmake/jerryscript.pri)

win32{
    INCLUDEPATH +=  $$PWD/../
    LIBS += -L$$PWD/../SDL2 -lSDL2 -lm -lws2_32
}


SOURCES += \
        main.c
