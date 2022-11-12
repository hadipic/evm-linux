TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

INCLUDEPATH += $$PWD/../../../engines/pikascript

include($$PWD/../pris/common.pri)
include($$PWD/../pris/pikascript.pri)

SOURCES += \
        $$PWD/../../../engines/pikascript/evm.c

SOURCES += \
        main.c
