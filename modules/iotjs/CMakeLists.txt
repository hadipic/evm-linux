set(MODULE_DIR ./common)
set(ESP_DIR ./espressif)

set(module_src
    ${MODULE_DIR}/evm_module.c
    ${MODULE_DIR}/evm_module_adc.c
    ${MODULE_DIR}/evm_module_assert.c
    ${MODULE_DIR}/evm_module_buffer.c
    ${MODULE_DIR}/evm_module_cffi.c
    ${MODULE_DIR}/evm_module_dns.c
    ${MODULE_DIR}/evm_module_events.c

    ${MODULE_DIR}/evm_module_fs.c
    ${MODULE_DIR}/evm_module_gpio.c
    ${MODULE_DIR}/evm_module_i2c.c
    ${MODULE_DIR}/evm_module_libc.c
    ${MODULE_DIR}/evm_module_network.c
    ${MODULE_DIR}/evm_module_process.c
    ${MODULE_DIR}/evm_module_repl.c
    ${MODULE_DIR}/evm_module_timers.c
    ${MODULE_DIR}/evm_module_uart.c
    ${MODULE_DIR}/evm_module_wlan.c
)

set(esp_src
    ${ESP_DIR}/esp_module_event.c
    ${ESP_DIR}/esp_module_gpio.c
    ${ESP_DIR}/esp_module_repl.c
    ${ESP_DIR}/esp_module_timers.c
    ${ESP_DIR}/esp_module_uart.c
    ${ESP_DIR}/esp_module_wlan.c
    ${ESP_DIR}/evm_main.c
)

if (EVM_USE_MUJS)
    message(STATUS "use mujs")
    set(ENGINE mujs)
else()
    message(STATUS "use default")
    set(ENGINE mujs)
endif()

idf_component_register(SRCS
                       ${module_src}
                       ${esp_src}
                       INCLUDE_DIRS 
                       .
                       ../../include
                       REQUIRES
                       ${ENGINE}
                       freertos
                       mbedtls
                       lwip)
            
target_compile_options(${COMPONENT_LIB} PRIVATE 
    -Wno-error
    -Wno-unused-variable
    -Wno-unused-label
    -Wno-unused-function
    -Wno-uninitialized
    -Wno-misleading-indentation
    -Wno-parentheses
    -Wno-pointer-sign
    -Wno-return-type
    -Wno-format-overflow
    -Wno-comment
    -Wno-multistatement-macros
    -Wno-implicit-function-declaration
    -Wno-incompatible-pointer-types )

