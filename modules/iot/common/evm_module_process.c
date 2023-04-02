/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"

#ifdef EVM_USE_LIBUV
static void setup_env(evm_t *e, evm_val_t process) {
    const char *evm_path, *extra_module_path;
    evm_path = getenv(IOT_MAGIC_STRING_EVM_PATH_U);
    extra_module_path = getenv(IOT_MAGIC_STRING_EVM_MODULE_PATH_U);

    evm_prop_set(e, process, IOT_MAGIC_STRING_EVM_PATH_U, evm_mk_string(e, evm_path ? evm_path:""));
    evm_prop_set(e, process, IOT_MAGIC_STRING_EVM_MODULE_PATH_U, evm_mk_string(e, extra_module_path ? extra_module_path:""));
}
#endif

void evm_module_process(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
#ifdef EVM_USE_LIBUV
    setup_env(e, obj);
#endif
    evm_module_add(e, "process", obj);
}
