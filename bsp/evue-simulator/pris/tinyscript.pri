INCLUDEPATH += $$PWD/../../../engines/tinyscript
INCLUDEPATH += $$PWD/../../../../tinyscript/tinyscript

HEADERS += \
    $$PWD/../../../../tinyscript/tinyscript/ts_parser.h \
    $$PWD/../../../../tinyscript/tinyscript/tinyscript_p.h \
    $$PWD/../../../../tinyscript/tinyscript/tinyscript.h

SOURCES += \
    $$PWD/../../../../tinyscript/tinyscript/tinyscript.c \
    $$PWD/../../../../tinyscript/tinyscript/ts_compile.c

HEADERS += \
    $$PWD/../../../engines/tinyscript/evm_type.h

SOURCES += \
    $$PWD/../../../engines/tinyscript/bget.c \
    $$PWD/../../../engines/tinyscript/evm.c



