cmake_minimum_required(VERSION 3.15)

set(engine mujs)
set(libuv libeuv)

include(proj.conf)

find_package(bouffalo_sdk REQUIRED HINTS $ENV{BL_SDK_BASE})

add_definitions(-DCONFIG_EVM_MODULE_ADC)
add_definitions(-DCONFIG_EVM_MODULE_CFFI)
add_definitions(-DCONFIG_EVM_MODULE_LVGL)
add_definitions(-DCONFIG_EVM_MODULE_LVGL_STYLE)

add_subdirectory(../../engines ../../engines)
add_subdirectory(../../components ../../components)
add_subdirectory(../../modules/iot ../../modules/iot)



sdk_add_include_directories(.)

sdk_set_main_file(main.c)

project(freertos)
