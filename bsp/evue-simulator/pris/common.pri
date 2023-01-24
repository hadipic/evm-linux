# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/iot/common
INCLUDEPATH += $$PWD/../../../modules/iot/linux

DEFINES += CONFIG_EVM_MODULE_LVGL
DEFINES += CONFIG_EVM_MODULE_LVGL_STYLE
DEFINES += CONFIG_EVM_MODULE_CFFI
DEFINES += CONFIG_EVM_MODULE_PROCESS
DEFINES += CONFIG_EVM_MODULE_FS
DEFINES += CONFIG_EVM_USE_UV
DEFINES += CONFIG_EVM_MODULE_ADC
DEFINES += CONFIG_EVM_MODULE_GPIO
DEFINES += CONFIG_EVM_MODULE_I2C
DEFINES += CONFIG_EVM_MODULE_SPI
DEFINES += CONFIG_EVM_MODULE_UART
DEFINES += CONFIG_EVM_MODULE_TIMER
DEFINES += CONFIG_EVM_MODULE_PWM
DEFINES += CONFIG_EVM_MODULE_TLS
DEFINES += CONFIG_EVM_MODULE_TCP

unix {
SOURCES += \
    $$PWD/../../../modules/iot/linux/linux_module_pwm.c \
    $$PWD/../../../modules/iot/linux/linux_module_repl.c \
    $$PWD/../../../modules/iot/linux/linux_system.c \
    $$PWD/../../../modules/iot/linux/linux_module_adc.c \
    $$PWD/../../../modules/iot/linux/linux_module_i2c.c \
    $$PWD/../../../modules/iot/linux/linux_module_gpio.c \
    $$PWD/../../../modules/iot/linux/linux_module_uart.c \
    $$PWD/../../../modules/iot/linux/linux_uv.c \
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

