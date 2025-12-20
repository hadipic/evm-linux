INCLUDEPATH += $$PWD/../components/libtuv/include
INCLUDEPATH += $$PWD/../components/libtuv/src

SOURCES += \
    $$PWD/../components/libtuv/src/fs-poll.c \
    $$PWD/../components/libtuv/src/inet.c \
    $$PWD/../components/libtuv/src/threadpool.c \
    $$PWD/../components/libtuv/src/tuv_debuglog.c \
    $$PWD/../components/libtuv/src/uv-common.c \
    $$PWD/../components/libtuv/src/version.c


unix {
SOURCES += \
    $$PWD/../components/libtuv/src/unix/async.c \
    $$PWD/../components/libtuv/src/unix/core.c \
    $$PWD/../components/libtuv/src/unix/fs.c \
    $$PWD/../components/libtuv/src/unix/getaddrinfo.c \
    $$PWD/../components/libtuv/src/unix/getnameinfo.c \
    $$PWD/../components/libtuv/src/unix/linux-core.c \
    $$PWD/../components/libtuv/src/unix/linux-syscalls.c \
    $$PWD/../components/libtuv/src/unix/loop-watcher.c \
    $$PWD/../components/libtuv/src/unix/loop.c \
    $$PWD/../components/libtuv/src/unix/poll.c \
    $$PWD/../components/libtuv/src/unix/process.c \
    $$PWD/../components/libtuv/src/unix/signal.c \
    $$PWD/../components/libtuv/src/unix/stream.c \
    $$PWD/../components/libtuv/src/unix/tcp.c \
    $$PWD/../components/libtuv/src/unix/timer.c \
    $$PWD/../components/libtuv/src/unix/thread.c \
    $$PWD/../components/libtuv/src/unix/udp.c
}

win32 {
SOURCES += \
    $$PWD/../components/libtuv/src/win/async.c \
    $$PWD/../components/libtuv/src/win/core.c \
    $$PWD/../components/libtuv/src/win/fs.c \
    $$PWD/../components/libtuv/src/win/fs-event.c \
    $$PWD/../components/libtuv/src/win/pipe.c \
    $$PWD/../components/libtuv/src/win/tty.c \
    $$PWD/../components/libtuv/src/win/snprintf.c \
    $$PWD/../components/libtuv/src/win/error.c \
    $$PWD/../components/libtuv/src/win/getaddrinfo.c \
    $$PWD/../components/libtuv/src/win/getnameinfo.c \
    $$PWD/../components/libtuv/src/win/winapi.c \
    $$PWD/../components/libtuv/src/win/handle.c \
    $$PWD/../components/libtuv/src/win/loop-watcher.c \
    $$PWD/../components/libtuv/src/win/poll.c \
    $$PWD/../components/libtuv/src/win/process.c \
    $$PWD/../components/libtuv/src/win/signal.c \
    $$PWD/../components/libtuv/src/win/stream.c \
    $$PWD/../components/libtuv/src/win/tcp.c \
    $$PWD/../components/libtuv/src/win/timer.c \
    $$PWD/../components/libtuv/src/win/thread.c \
    $$PWD/../components/libtuv/src/win/udp.c
}

