# evm
INCLUDEPATH += $$PWD/../../../include

# iot modules
INCLUDEPATH += $$PWD/../../../modules/iot/common

DEFINES += CONFIG_EVM_MODULE_ADC
DEFINES += CONFIG_EVM_MODULE_TIMER
DEFINES += CONFIG_EVM_MODULE_CFFI

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
    $$PWD/../../../modules/iot/common/iot_adc.c \
    $$PWD/../../../modules/iot/common/iot_system.c \
    $$PWD/../../../modules/iot/common/iot_uv.c \
    $$PWD/../../../modules/iot/common/evm_module.c \
    $$PWD/../../../modules/iot/common/evm_module_cffi.c \
    $$PWD/../../../modules/iot/common/evm_module_repl.c \
    $$PWD/../../../modules/iot/common/evm_module_periph_common.c \
    $$PWD/../../../modules/iot/common/evm_module_adc.c \
    $$PWD/../../../modules/iot/common/evm_module_timer.c \
    $$PWD/../../../modules/iot/common/evm_module_process.c
