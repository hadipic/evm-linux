add_definitions(
    -DCONFIG_EVM_MODULE_GPIO
    -DCONFIG_EVM_MODULE_UART
    -DCONFIG_EVM_MODULE_PROCESS
    -DCONFIG_EVM_MODULE_EVENT
    -DCONFIG_EVM_MODULE_WLAN
    -DCONFIG_EVM_MODULE_REPL
)

idf_component_register( SRCS 
                        "app.c"
                        INCLUDE_DIRS 
                        "."
                        REQUIRES
                        mujs
                        iotjs)