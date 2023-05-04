cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED ENV{EVM_HOME})
    message( "please set EVM_HOME in your system environment")
endif()

set(EVM_HOME $ENV{EVM_HOME})

include(proj.conf)

find_package(bouffalo_sdk REQUIRED HINTS $ENV{BL_SDK_BASE})

set(engine jerryscript)

add_definitions(-DCONFIG_EVM_MODULE_CFFI)
add_definitions(-DCONFIG_EVM_MODULE_LVGL)
add_definitions(-DCONFIG_EVM_MODULE_LVGL_STYLE)

add_subdirectory(evm/engines engines)
add_subdirectory(evm/modules iot)

sdk_add_include_directories(.)
sdk_set_main_file(main.c)

project(freertos)
