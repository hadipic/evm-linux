sdk_generate_library()
sdk_add_include_directories(./common)
sdk_library_add_sources(common/evm_module.c)
sdk_library_add_sources(common/evm_module_cffi.c)
sdk_library_add_sources(common/evm_module_process.c)

sdk_library_add_sources(bouffalolab/evm_main.c)

sdk_add_include_directories(./gui/lvgl)
sdk_library_add_sources(gui/lvgl/evm_module_lvgl.c)
sdk_library_add_sources(gui/lvgl/evm_module_lvgl_event.c)
sdk_library_add_sources(gui/lvgl/evm_module_lvgl_misc.c)
sdk_library_add_sources(gui/lvgl/evm_module_lvgl_style.c)
