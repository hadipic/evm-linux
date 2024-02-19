# evm
INCLUDEPATH += $$PWD/../include

# iot modules
INCLUDEPATH += $$PWD/../modules/common
INCLUDEPATH += $$PWD/../modules/linux

# components
INCLUDEPATH += $$PWD/../components/zmalloc

DEFINES += EVM_USE_LIBUV
#DEFINES += EVM_USE_MODULE_FS
DEFINES += EVM_USE_MODULE_LVGL
DEFINES += EVM_USE_MODULE_LVGL_STYLE
DEFINES += EVM_USE_MODULE_CFFI
DEFINES += EVM_USE_MODULE_LVGL_IMAGE
DEFINES += EVM_USE_MODULE_CJSON
DEFINES += EVM_USE_MODULE_HEATSHRINK
DEFINES += EVM_USE_MODULE_BASE64
#DEFINES += EVM_USE_MODULE_ADC
#DEFINES += EVM_USE_MODULE_PWM
#DEFINES += EVM_USE_MODULE_UART
#DEFINES += EVM_USE_MODULE_GPIO
#DEFINES += EVM_USE_MODULE_I2C
#DEFINES += EVM_USE_MODULE_TIMER
#DEFINES += EVM_USE_MODULE_TCP

SOURCES += \
    $$PWD/../modules/linux/evm_main.c

contains(DEFINES, EVM_USE_MODULE_NET) {
LIBS += -lmbedtls -lmbedx509 -lmbedcrypto
}

contains(DEFINES, CONFIG_EVM_MODULE_HTTP_PARSER) {
INCLUDEPATH += $$PWD/../components/http-parser
SOURCES += \
    $$PWD/../components/http-parser/http_parser.c
}

SOURCES += \
    $$PWD/../components/zmalloc/zmalloc.c

SOURCES += \
    $$PWD/../modules/gui/lvgl/evm_module_lvgl.c \
    $$PWD/../modules/gui/lvgl/evm_module_lvgl_style.c \
    $$PWD/../modules/gui/lvgl/evm_module_lvgl_event.c \
    $$PWD/../modules/gui/lvgl/evm_module_lvgl_misc.c \
    $$PWD/../modules/gui/lvgl/evm_module_lvgl_timeout.c \
    $$PWD/../modules/gui/lvgl/evm_module_lvgl_image.c


SOURCES += \
    $$PWD/../modules/common/evm_module.c \
    $$PWD/../modules/common/evm_module_cffi.c \
    $$PWD/../modules/common/evm_module_console.c \
    $$PWD/../modules/common/evm_module_process.c


contains(DEFINES, EVM_USE_MODULE_CJSON) {
INCLUDEPATH += $$PWD/../components/cjson
SOURCES += \
    $$PWD/../modules/common/evm_module_cjson.c
SOURCES += \
    $$PWD/../components/cjson/cJSON.c
}

contains(DEFINES, EVM_USE_MODULE_HEATSHRINK) {
INCLUDEPATH += $$PWD/../components/heatshrink
SOURCES += \
    $$PWD/../modules/common/compress_heatshrink.c \
    $$PWD/../modules/common/evm_module_heatshrink.c

SOURCES += \
    $$PWD/../components/heatshrink/heatshrink_decoder.c \
    $$PWD/../components/heatshrink/heatshrink_encoder.c
}

contains(DEFINES, EVM_USE_MODULE_BASE64) {
SOURCES += \
    $$PWD/../modules/common/evm_module_base64.c
}

#SOURCES += \
#    $$PWD/../modules/common/evm_module_adc.c \
#    $$PWD/../modules/common/evm_module_gpio.c \
#    $$PWD/../modules/common/evm_module_i2c.c \
#    $$PWD/../modules/common/evm_module_periph_common.c \
#    $$PWD/../modules/common/evm_module_pwm.c \
#    $$PWD/../modules/common/evm_module_timer.c \
#    $$PWD/../modules/common/evm_module_tcp.c \
#    $$PWD/../modules/common/evm_module_tls.c \
#    $$PWD/../modules/common/evm_module_uart.c

#unix {
#SOURCES += \
#    $$PWD/../modules/linux/iot_system.c \
#    $$PWD/../modules/linux/iot_uv.c \
#    $$PWD/../modules/linux/linux_module_adc.c \
#    $$PWD/../modules/linux/linux_module_gpio.c \
#    $$PWD/../modules/linux/linux_module_i2c.c \
#    $$PWD/../modules/linux/linux_module_pwm.c \
#    $$PWD/../modules/linux/linux_module_uart.c
#}
