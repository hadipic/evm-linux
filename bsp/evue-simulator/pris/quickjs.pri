INCLUDEPATH += $$PWD/../../../engines/quickjs
INCLUDEPATH += $$PWD/../../../engines/quickjs/quickjs

DEFINES += CONFIG_VERSION=\\\"2021-03-27\\\"

HEADERS += \
    $$PWD/../../../include/evm.h

SOURCES += \
    $$PWD/../../../engines/quickjs/evm.c

SOURCES += \
    $$PWD/../../../engines/quickjs/quickjs/quickjs.c \
    $$PWD/../../../engines/quickjs/quickjs/cutils.c \
    $$PWD/../../../engines/quickjs/quickjs/libregexp.c \
    $$PWD/../../../engines/quickjs/quickjs/libunicode.c
