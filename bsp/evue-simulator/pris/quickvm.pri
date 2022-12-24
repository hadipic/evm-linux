INCLUDEPATH += $$PWD/../../../engines/quickvm
INCLUDEPATH += $$PWD/../../../engines/quickvm/inc

SOURCES += \
    $$PWD/../../../engines/quickvm/bget.c \
    $$PWD/../../../engines/quickvm/evm.c

HEADERS += \
    $$PWD/../../../engines/quickvm/evm_type.h


contains(DEFINES, EVM_USE_QUICKVM_DEBUG) {
    INCLUDEPATH += $$PWD/../../../../quickcompiler/private
    INCLUDEPATH += $$PWD/../../../../quickcompiler/inc
    DEFINES += QVM_USE_JS
SOURCES += \
    $$PWD/../../../../quickcompiler/src/quickvm.c \
    $$PWD/../../../../quickcompiler/src/quickvm_compiler.c \
    $$PWD/../../../../quickcompiler/src/quickvm_js_parse.c \
    $$PWD/../../../../quickcompiler/src/quickvm_gc.c \
    $$PWD/../../../../quickcompiler/src/quickvm_native.c \
    $$PWD/../../../../quickcompiler/src/quickvm_exec.c \
    $$PWD/../../../../quickcompiler/src/quickvm_utils.c
} else {
    unix {
        LIBS += -L$$PWD/../../../engines/quickvm/lib/x86/linux -lquickvm
    }
}


