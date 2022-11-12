TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

include($$PWD/../pris/common.pri)
include($$PWD/../pris/quickjs.pri)

SOURCES += \
        main.c
