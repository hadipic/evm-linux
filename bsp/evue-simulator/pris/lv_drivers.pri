DEFINES += LV_CONF_INCLUDE_SIMPLE

INCLUDEPATH +=  $$PWD/../../../components/lvgl/lv_drivers
INCLUDEPATH +=  $$PWD/../../../components/lvgl

unix{
LIBS += -lSDL2 -lm
}
win32{
LIBS += -L$$PWD/../SDL2 -lSDL2 -lm
}

SOURCES += \
        ../../../components/lvgl/lv_drivers/sdl/sdl.c \
        ../../../components/lvgl/lv_drivers/sdl/sdl_common.c \
        ../../../components/lvgl/lv_drivers/sdl/sdl_gpu.c

HEADERS += \
    ../../../components/lvgl/lv_drivers/sdl/sdl.h \
    ../../../components/lvgl/lv_drivers/sdl/sdl_common.h \
    ../../../components/lvgl/lv_drivers/sdl/sdl_common_internal.h \
    ../../../components/lvgl/lv_drivers/sdl/sdl_gpu.h

