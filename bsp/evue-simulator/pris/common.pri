# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/include
INCLUDEPATH += $$PWD/../../../modules/linux

# components
INCLUDEPATH += $$PWD/../../../components/zmalloc

DEFINES += EVM_USE_LIBUV
DEFINES += EVM_USE_MODULE_FS
DEFINES += EVM_USE_MODULE_LVGL
DEFINES += EVM_USE_MODULE_LVGL_STYLE
DEFINES += EVM_USE_MODULE_CFFI
DEFINES += EVM_USE_MODULE_PROCESS
DEFINES += EVM_USE_MODULE_TIMER
DEFINES += EVM_USE_MODULE_NET
DEFINES += EVM_USE_MODULE_LVGL_IMAGE
DEFINES += EVM_USE_MODULE_CJSON

SOURCES += \
    $$PWD/../../../modules/linux/evm_main.c

contains(DEFINES, EVM_USE_MODULE_NET) {
LIBS += -lmbedtls -lmbedx509 -lmbedcrypto
}

contains(DEFINES, CONFIG_EVM_MODULE_HTTP_PARSER) {
INCLUDEPATH += $$PWD/../../../components/http-parser
SOURCES += \
    $$PWD/../../../components/http-parser/http_parser.c
}

SOURCES += \
    $$PWD/../../../components/zmalloc/zmalloc.c

SOURCES += \
    $$PWD/../../../modules/gui/lvgl/evm_module_lvgl.c \
    $$PWD/../../../modules/gui/lvgl/evm_module_lvgl_style.c \
    $$PWD/../../../modules/gui/lvgl/evm_module_lvgl_event.c \
    $$PWD/../../../modules/gui/lvgl/evm_module_lvgl_misc.c \
    $$PWD/../../../modules/gui/lvgl/evm_module_lvgl_timeout.c \
    $$PWD/../../../modules/gui/lvgl/evm_module_lvgl_image.c

SOURCES += \
    $$PWD/../../../modules/linux/evm_port_platform.c \
    $$PWD/../../../modules/linux/evm_port_gpio.c \
    $$PWD/../../../modules/linux/evm_port_fs.c \
    $$PWD/../../../modules/linux/evm_port_wifi.c \
    $$PWD/../../../modules/linux/evm_port_uart.c

SOURCES += \
    $$PWD/../../../modules/common/evm_module.c \
    $$PWD/../../../modules/common/evm_module_cffi.c \
    $$PWD/../../../modules/common/evm_module_gpio.c \
    $$PWD/../../../modules/common/evm_module_uart.c \
    $$PWD/../../../modules/common/evm_module_console.c \
    $$PWD/../../../modules/common/evm_module_timer.c \
    $$PWD/../../../modules/common/evm_module_fs.c \
    $$PWD/../../../modules/common/evm_module_wifi.c \
    $$PWD/../../../modules/common/evm_module_net.c \
    $$PWD/../../../modules/common/evm_module_process.c

SOURCES += \
    $$PWD/../../../modules/common/tls_client.c \
    $$PWD/../../../modules/common/tls_certificate.c

SOURCES += \
    $$PWD/../../../modules/freertos/evm_port_msgbus.c \
    $$PWD/../../../modules/freertos/evm_port_timer.c

contains(DEFINES, EVM_USE_MODULE_CJSON) {
INCLUDEPATH += $$PWD/../../../components/cjson
SOURCES += \
    $$PWD/../../../modules/common/evm_module_cjson.c
SOURCES += \
    $$PWD/../../../components/cjson/cJSON.c
}

