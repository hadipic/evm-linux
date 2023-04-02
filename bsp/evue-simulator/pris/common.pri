# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/iot/common
INCLUDEPATH += $$PWD/../../../modules/iot/linux

DEFINES += EVM_USE_LIBUV
DEFINES += EVM_USE_MODULE_FS
DEFINES += EVM_USE_MODULE_LVGL
DEFINES += EVM_USE_MODULE_LVGL_STYLE
DEFINES += EVM_USE_MODULE_CFFI
DEFINES += EVM_USE_MODULE_PROCESS
DEFINES += EVM_USE_MODULE_TIMER

unix {
SOURCES += \
    $$PWD/../../../modules/iot/linux/evm_main.c
}

contains(DEFINES, CONFIG_EVM_MODULE_TLS) {
LIBS += -lmbedtls -lmbedx509 -lmbedcrypto
}

contains(DEFINES, CONFIG_EVM_MODULE_HTTP_PARSER) {
INCLUDEPATH += $$PWD/../../../components/http-parser
SOURCES += \
    $$PWD/../../../components/http-parser/http_parser.c

SOURCES += \
    $$PWD/../../../modules/iot/common/evm_module_http_parser.c
}

SOURCES += \
    $$PWD/../../../modules/iot/gui/lvgl/evm_module_lvgl.c \
    $$PWD/../../../modules/iot/gui/lvgl/evm_module_lvgl_style.c \
    $$PWD/../../../modules/iot/gui/lvgl/evm_module_lvgl_event.c \
    $$PWD/../../../modules/iot/gui/lvgl/evm_module_lvgl_misc.c \
    $$PWD/../../../modules/iot/gui/lvgl/evm_module_lvgl_image.c

SOURCES += \
    $$PWD/../../../modules/iot/common/iot_adc.c \
    $$PWD/../../../modules/iot/common/iot_system.c \
    $$PWD/../../../modules/iot/common/iot_uv.c \
    $$PWD/../../../modules/iot/common/evm_module.c \
    $$PWD/../../../modules/iot/common/evm_module_cffi.c \
    $$PWD/../../../modules/iot/common/evm_module_libc.c \
    $$PWD/../../../modules/iot/common/evm_module_repl.c \
    $$PWD/../../../modules/iot/common/evm_module_periph_common.c \
    $$PWD/../../../modules/iot/common/evm_module_fs.c \
    $$PWD/../../../modules/iot/common/evm_module_tcp.c \
    $$PWD/../../../modules/iot/common/evm_module_tls.c \
    $$PWD/../../../modules/iot/common/evm_module_pwm.c \
    $$PWD/../../../modules/iot/common/evm_module_gpio.c \
    $$PWD/../../../modules/iot/common/evm_module_i2c.c \
    $$PWD/../../../modules/iot/common/evm_module_uart.c \
    $$PWD/../../../modules/iot/common/evm_module_adc.c \
    $$PWD/../../../modules/iot/common/evm_module_timer.c \
    $$PWD/../../../modules/iot/common/evm_module_process.c

