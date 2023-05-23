/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"

#if defined(__linux__) || defined(win32)
#include <unistd.h>
#endif

extern void platform_init(void);

static char app_path[128] = "";

const char *evm_get_app_path(void) {
    return app_path;
}

static void setup_env(evm_t *e, evm_val_t process) {
    const char *evm_path, *extra_module_path;

#if defined(__linux__) || defined(win32)
    evm_path = getenv("EVM_PATH");
    extra_module_path = getenv("EVM_MODULE_PATH");
    getcwd(app_path, 128);
#else
    evm_path = EVM_PATH;
    extra_module_path = EVM_MODULE_PATH;
    memcpy(app_path, EVM_APP_PATH, strlen(EVM_APP_PATH));
#endif

    evm_prop_set(e, process, "EVM_PATH", evm_mk_string(e, evm_path ? evm_path:""));
    evm_prop_set(e, process, "EVM_MODULE_PATH", evm_mk_string(e, extra_module_path ? extra_module_path:""));
    evm_prop_set(e, process, "APP_PATH", evm_mk_string(e, app_path));
}

void evm_module_process(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    setup_env(e, obj);
    evm_module_add(e, "process", obj);
    evm_val_free(e, obj);

    platform_init();
}
