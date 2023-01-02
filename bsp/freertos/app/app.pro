TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR = $$PWD/../build
DESTDIR = $$PWD/../build

include($$PWD/../pris/common.pri)
include($$PWD/../pris/freertos.pri)

unix{
LIBS += -lpthread
}

contains(DEFINES, EVM_USE_TUV){
include($$PWD/../pris/tuv.pri)
}

contains(DEFINES, EVM_USE_EUV){
include($$PWD/../pris/euv.pri)
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

if( contains(DEFINES, EVM_USE_UPY) ) {
    include($$PWD/../pris/micropy.pri)
}

if( contains(DEFINES, EVM_USE_QUICKVM) ) {
    include($$PWD/../pris/quickvm.pri)
}

if( contains(DEFINES, EVM_USE_DUKTAPE) ) {
    include($$PWD/../pris/duktape.pri)
}

HEADERS += \
    FreeRTOSConfig.h

SOURCES += \
        main.c
