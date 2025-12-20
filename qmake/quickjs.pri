INCLUDEPATH += $$PWD/../engines/quickjs
INCLUDEPATH += $$PWD/../engines/quickjs/quickjs

DEFINES += CONFIG_VERSION=\\\"2021-03-27\\\"

HEADERS += \
    $$PWD/../engines/quickjs/quickjs/libbf.h \
    $$PWD/../engines/quickjs/quickjs/list.h \
    $$PWD/../engines/quickjs/quickjs/quickjs-libc.h \
    $$PWD/../engines/quickjs/quickjs/quickjs-opcode.h \
    $$PWD/../include/evm.h

HEADERS += \
    $$PWD/../engines/quickjs/evm_type.h

SOURCES += \
    $$PWD/../engines/quickjs/evm.c \
    $$PWD/../engines/quickjs/quickjs/libbf.c

SOURCES += \
    $$PWD/../engines/quickjs/quickjs/quickjs.c \
    $$PWD/../engines/quickjs/quickjs/cutils.c \
    $$PWD/../engines/quickjs/quickjs/libregexp.c \
    $$PWD/../engines/quickjs/quickjs/libunicode.c
