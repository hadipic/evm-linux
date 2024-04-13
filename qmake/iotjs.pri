DEFINES += ENABLE_MODULE_IOTJS_BASIC_MODULES
DEFINES += ENABLE_MODULE_IOTJS_CORE_MODULES
DEFINES += ENABLE_MODULE_ADC
DEFINES += ENABLE_MODULE_BLE
DEFINES += ENABLE_MODULE_CRYPTO
DEFINES += ENABLE_MODULE_DGRAM
DEFINES += ENABLE_MODULE_GPIO
DEFINES += ENABLE_MODULE_HTTP_SIGNATURE
DEFINES += ENABLE_MODULE_HTTPS
DEFINES += ENABLE_MODULE_I2C
DEFINES += ENABLE_MODULE_MQTT
DEFINES += ENABLE_MODULE_PWM
DEFINES += ENABLE_MODULE_SPI
DEFINES += ENABLE_MODULE_UART
DEFINES += ENABLE_MODULE_WEBSOCKET
#DEFINES += ENABLE_MODULE_TLS
DEFINES += ENABLE_MODULE_UDP

INCLUDEPATH +=  $$PWD/../components/jerry-wrapper
INCLUDEPATH +=  $$PWD/../components/http-parser

SOURCES += \
    $$PWD/../components/http-parser/http_parser.c


INCLUDEPATH +=  $$PWD/../modules/iotjs/include
INCLUDEPATH +=  $$PWD/../modules/iotjs/src
INCLUDEPATH +=  $$PWD/../modules/iotjs/src/modules


SOURCES += \
    $$PWD/../modules/iotjs/src/iotjs.c \
    $$PWD/../modules/iotjs/src/iotjs_binding.c \
    $$PWD/../modules/iotjs/src/iotjs_binding_helper.c \
    $$PWD/../modules/iotjs/src/iotjs_debuglog.c \
    $$PWD/../modules/iotjs/src/iotjs_env.c \
    $$PWD/../modules/iotjs/src/iotjs_module.c \
    $$PWD/../modules/iotjs/src/iotjs_string.c \
    $$PWD/../modules/iotjs/src/iotjs_string_ext.c \
    $$PWD/../modules/iotjs/src/iotjs_util.c \
    $$PWD/../modules/iotjs/src/iotjs_uv_handle.c \
    $$PWD/../modules/iotjs/src/iotjs_uv_request.c

unix {
SOURCES += \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_dns.c
}

SOURCES += \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_adc.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_blehcisocket.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_bridge.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_buffer.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_console.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_constants.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_crypto.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_fs.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_gpio.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_http_parser.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_i2c.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_mqtt.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_periph_common.c \
#    $$PWD/../modules/iotjs/src/modules/iotjs_module_process.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_pwm.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_spi.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_tcp.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_timer.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_uart.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_udp.c \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_websocket.c

contains(DEFINES, ENABLE_MODULE_TLS) {
SOURCES += \
    $$PWD/../modules/iotjs/src/modules/iotjs_module_tls.c
}

unix {
    INCLUDEPATH +=  $$PWD/../modules/iotjs/src/modules/linux
    INCLUDEPATH +=  $$PWD/../modules/iotjs/src/platform/linux
SOURCES += \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_adc-linux.c \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_blehcisocket-linux.c \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_gpio-linux.c \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_i2c-linux.c \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_pwm-linux.c \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_spi-linux.c \
    $$PWD/../modules/iotjs/src/modules/linux/iotjs_module_uart-linux.c

SOURCES += \
    $$PWD/../modules/iotjs/src/platform/linux/iotjs_systemio-linux.c 
}
