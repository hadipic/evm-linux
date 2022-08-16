TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += $$PWD/../../engines/mujs
INCLUDEPATH += $$PWD/../../engines/mujs/mujs

SOURCES += \
    $$PWD/../../engines/mujs/evm.c

SOURCES += \
    $$PWD/../../engines/mujs/mujs/one.c

SOURCES += \
        main.c


