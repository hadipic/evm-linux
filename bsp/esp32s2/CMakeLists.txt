# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

option(EVM_USE_MUSJ "use mujs as main script engine" ON)

add_definitions(-DCONFIG_EVM_MODULE_GPIO 
                -DCONFIG_EVM_MODULE_UART 
                -DCONFIG_EVM_MODULE_PROCESS 
                -DCONFIG_EVM_MODULE_EVENT
                -DCONFIG_EVM_MODULE_WLAN
                -DCONFIG_EVM_MODULE_REPL)

set(EXTRA_COMPONENT_DIRS 
    ../../engines 
    ../../modules)

project(app)


