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

DEFINES += EVM_USE_MODULE_LVGL=1
DEFINES += EVM_USE_MODULE_LVGL_IMAGE


INCLUDEPATH += $$PWD/../../../components/zmalloc

include($$PWD/../../../qmake/common.pri)
include($$PWD/../../../qmake/lvgl.pri)
include($$PWD/../../../qmake/lv_png.pri)
include($$PWD/../../../qmake/lv_drivers.pri)

unix{
include($$PWD/../../../qmake/tuv.pri)
#include($$PWD/../../../qmake/iotjs.pri)
}

#include($$PWD/../../../qmake/jerryscript.pri)
include($$PWD/../../../qmake/quickjs.pri)
#include($$PWD/../../../qmake/mujs.pri)


win32{
    INCLUDEPATH +=  $$PWD/../
    LIBS += -L$$PWD/../SDL2 -lSDL2 -lm -lws2_32
}


unix {
    # ... بقیه includeها ...
    # اضافه کردن SDL2 برای Linux
    INCLUDEPATH += /usr/include/SDL2  # یا مسیر نصب SDL2 (معمولاً /usr/include/SDL2)
    LIBS += -lSDL2
}


SOURCES += \
        main.c
