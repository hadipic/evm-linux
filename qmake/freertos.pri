# freertos
INCLUDEPATH += $$PWD/../components/freertos/include

SOURCES += \
    $$PWD/../components/freertos/timers.c \
    $$PWD/../components/freertos/tasks.c \
    $$PWD/../components/freertos/stream_buffer.c \
    $$PWD/../components/freertos/queue.c \
    $$PWD/../components/freertos/list.c \
    $$PWD/../components/freertos/heap_4.c \
    $$PWD/../components/freertos/event_groups.c \
    $$PWD/../components/freertos/croutine.c

unix{
INCLUDEPATH += $$PWD/../components/freertos/portable/ThirdParty/GCC/Posix
INCLUDEPATH += $$PWD/../components/freertos/portable/ThirdParty/GCC/Posix/utils
SOURCES += \
    $$PWD/../components/freertos/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c \
    $$PWD/../components/freertos/portable/ThirdParty/GCC/Posix/port.c
}

win32{
INCLUDEPATH += $$PWD/../components/freertos/portable/MSVC-MingW
SOURCES += \
    $$PWD/../components/freertos/portable/MSVC-MingW/port.c
LIBS += -lwinmm
}

