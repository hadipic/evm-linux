DEFINES += LV_CONF_INCLUDE_SIMPLE

INCLUDEPATH +=  $$PWD/../components/lvgl/lv_drivers
INCLUDEPATH +=  $$PWD/../components/lvgl

unix{
LIBS += -lSDL2 -lm
}

SOURCES += \
        $$PWD/../components/lvgl/lv_drivers/sdl/sdl.c \
        $$PWD/../components/lvgl/lv_drivers/sdl/sdl_common.c \
        $$PWD/../components/lvgl/lv_drivers/sdl/sdl_gpu.c

HEADERS += \
    $$PWD/../components/lvgl/lv_drivers/sdl/sdl.h \
    $$PWD/../components/lvgl/lv_drivers/sdl/sdl_common.h \
    $$PWD/../components/lvgl/lv_drivers/sdl/sdl_common_internal.h \
    $$PWD/../components/lvgl/lv_drivers/sdl/sdl_gpu.h

