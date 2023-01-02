INCLUDEPATH += $$PWD/../../../components/libeuv/inc

DEFINES += EUV_USE_FREERTOS

HEADERS += \
    $$PWD/../../../components/libeuv/inc/uv.h

SOURCES += \
    $$PWD/../../../components/libeuv/src/uv-common.c \
    $$PWD/../../../components/libeuv/src/uv_fs.c \
    $$PWD/../../../components/libeuv/src/uv_timer.c \
    $$PWD/../../../components/libeuv/src/uv_handle.c \
    $$PWD/../../../components/libeuv/src/uv_loop.c \
    $$PWD/../../../components/libeuv/src/uv_async.c \
    $$PWD/../../../components/libeuv/src/thread.c


