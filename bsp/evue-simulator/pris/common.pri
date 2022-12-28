# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/iot/common

DEFINES += CONFIG_EVM_DEBUG_LOG
DEFINES += CONFIG_EVM_MODULE_FS
DEFINES += CONFIG_EVM_MODULE_HTTP_PARSER
DEFINES += CONFIG_EVM_MODULE_TIMERS
DEFINES += CONFIG_EVM_MODULE_BUFFER
DEFINES += CONFIG_EVM_MODULE_ASSERT
DEFINES += CONFIG_EVM_MODULE_CFFI
DEFINES += CONFIG_EVM_MODULE_LIBC
DEFINES += CONFIG_EVM_MODULE_PROCESS
DEFINES += CONFIG_EVM_MODULE_ADC
DEFINES += CONFIG_EVM_MODULE_GPIO
DEFINES += CONFIG_EVM_MODULE_I2C
DEFINES += CONFIG_EVM_MODULE_SPI
DEFINES += CONFIG_EVM_MODULE_UART
DEFINES += CONFIG_EVM_MODULE_TIMER
DEFINES += CONFIG_EVM_MODULE_TCP
DEFINES += CONFIG_EVM_MODULE_TLS
DEFINES += CONFIG_EVM_MODULE_PWM

INCLUDEPATH +=  $$PWD/../../../components/lvgl/lvgl/src/extra/libs/png
DEFINES += CONFIG_EVM_MODULE_LVGL
DEFINES += LV_USE_PNG
DEFINES += LV_USE_FS_STDIO
DEFINES += LV_PNG_USE_LV_FILESYSTEM
SOURCES += \
    ../../../modules/iot/gui/lvgl/evm_module_lvgl.c \
    ../../../modules/iot/gui/lvgl/evm_module_lvgl_event.c \
    $$PWD/../../../modules/iot/gui/lvgl/evm_module_lvgl_image.c

contains(DEFINES, CONFIG_EVM_MODULE_TLS) {
LIBS += -lmbedtls -lmbedx509 -lmbedcrypto
}

contains(DEFINES, CONFIG_EVM_MODULE_HTTP_PARSER) {
INCLUDEPATH += $$PWD/../../../components/http-parser
SOURCES += \
    $$PWD/../../../components/http-parser/http_parser.c
SOURCES += \
    ../../../modules/iot/common/evm_module_http_parser.c
}

SOURCES += \
    ../../../modules/iot/common/evm_module.c \
    ../../../modules/iot/common/evm_module_events.c \
    ../../../modules/iot/common/evm_module_buffer.c \
    ../../../modules/iot/common/evm_module_cffi.c \
    ../../../modules/iot/common/evm_module_libc.c \
    ../../../modules/iot/common/evm_module_assert.c \
    ../../../modules/iot/common/evm_module_fs.c \
    ../../../modules/iot/common/evm_module_dns.c \
    ../../../modules/iot/common/evm_module_repl.c \
    ../../../modules/iot/common/evm_module_network.c \
    $$PWD/../../../modules/iot/linux/linux_system.c

SOURCES += \
    ../../../modules/iot/linux/linux_uv.c \
    ../../../modules/iot/linux/linux_module_adc.c \
    ../../../modules/iot/linux/linux_module_i2c.c \
    ../../../modules/iot/linux/linux_module_gpio.c \
    ../../../modules/iot/linux/linux_module_uart.c \
    ../../../modules/iot/linux/evm_module_tcp.c \
    ../../../modules/iot/linux/evm_module_tls.c \
    ../../../modules/iot/linux/evm_module_pwm.c \
    ../../../modules/iot/linux/evm_module_gpio.c \
    ../../../modules/iot/linux/evm_module_i2c.c \
    ../../../modules/iot/linux/evm_module_uart.c \
    ../../../modules/iot/linux/evm_module_adc.c \
    ../../../modules/iot/linux/evm_module_timer.c \
    ../../../modules/iot/linux/evm_module_process.c \
    ../../../modules/iot/linux/evm_module_periph_common.c \
    ../../../modules/iot/linux/linux_module_repl.c

SOURCES += \
    ../../../modules/iot/linux/linux_module_pwm.c

SOURCES += \
    ../../../modules/iot/linux/evm_main.c
