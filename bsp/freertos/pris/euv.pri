INCLUDEPATH += $$PWD/../../../include
INCLUDEPATH += $$PWD/../../../components/libeuv/inc

DEFINES += EUV_USE_FREERTOS

HEADERS += \
    $$PWD/../../../components/libeuv/inc/uv.h

SOURCES += \
    $$PWD/../../../components/libeuv/src/uv_fs.c \
    $$PWD/../../../components/libeuv/src/uv_timer.c \
    $$PWD/../../../components/libeuv/src/uv_handle.c \
    $$PWD/../../../components/libeuv/src/uv_request.c \
    $$PWD/../../../components/libeuv/src/uv_loop.c \
    $$PWD/../../../components/libeuv/src/uv_async.c \
    $$PWD/../../../components/libeuv/src/uv_thread.c \
    $$PWD/../../../components/libeuv/src/uv_poll.c \
    $$PWD/../../../components/libeuv/src/uv_core.c \
    $$PWD/../../../components/libeuv/src/uv_tcp.c \
    $$PWD/../../../components/libeuv/src/uv_common.c


