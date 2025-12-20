idf_component_register(
    SRCS 
        "evm_module_lvgl.c"
        "evm_module_lvgl_event.c"
        "evm_module_lvgl_misc.c"
        "evm_module_lvgl_style.c"
        "evm_module_lvgl_image.c"
        "evm_module_lvgl_timeout.c"
        
    INCLUDE_DIRS 
        "."
        "../../../engines/quickjs"
        "../../../include"  # تغییر این خط - مسیر صحیح به پوشه include
        
    REQUIRES 
        quickjs
        lvgl
        esp_modules
        lv-fs
        vfs  
        sdmmc  

)