TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../engines/evm
INCLUDEPATH += $$PWD/../../components/cjson

SOURCES += \
        $$PWD/../../components/cjson/cJSON.c

SOURCES += \
        $$PWD/../../engines/evm/evm_grammar.c

SOURCES += \
        json.c \
        main.c

