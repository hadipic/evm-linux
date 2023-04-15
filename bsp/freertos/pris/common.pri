# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/iot/common
INCLUDEPATH += $$PWD/../../../modules/iot/freertos

DEFINES += EVM_USE_MODULE_TIMER
DEFINES += EVM_USE_MODULE_CFFI

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
    $$PWD/../../../modules/iot/freertos/iot_system.c \
    $$PWD/../../../modules/iot/freertos/iot_uv.c \
    $$PWD/../../../modules/iot/freertos/uv.c \
    $$PWD/../../../modules/iot/freertos/uv_timer.c \
    $$PWD/../../../modules/iot/freertos/evm_main.c

SOURCES += \
    $$PWD/../../../modules/iot/common/evm_module.c \
    $$PWD/../../../modules/iot/common/evm_module_cffi.c \
    $$PWD/../../../modules/iot/common/evm_module_repl.c \
    $$PWD/../../../modules/iot/common/evm_module_periph_common.c \
    $$PWD/../../../modules/iot/common/evm_module_timer.c \
    $$PWD/../../../modules/iot/common/evm_module_process.c
