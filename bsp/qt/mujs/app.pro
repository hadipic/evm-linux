TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

INCLUDEPATH += $$PWD/../../../engines/mujs

include($$PWD/../pris/common.pri)
include($$PWD/../pris/mujs.pri)

SOURCES += \
        main.c