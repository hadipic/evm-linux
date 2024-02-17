/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include "evm_module.h"

#if defined(__linux__) || defined(win32)
#include <unistd.h>
#endif

extern void platform_init(void);

static char app_path[256] = "";

const char *evm_get_app_path(void) {
    return app_path;
}

static void setup_env(evm_t *e, evm_val_t process) {
    const char *evm_path = "", *extra_module_path = "";

#if defined(__linux__) || defined(win32)
    evm_path = getenv("EVM_PATH");
    extra_module_path = getenv("EVM_MODULE_PATH");
    getcwd(app_path, 256);
#else
    evm_path = EVM_PATH;
    extra_module_path = EVM_MODULE_PATH;
    memcpy(app_path, EVM_APP_PATH, strlen(EVM_APP_PATH));
#endif
    evm_val_t val = evm_mk_string(e, evm_path?evm_path:"");
    evm_prop_set(e, process, "EVM_PATH", val);
    evm_val_free(e, val);
    val = evm_mk_string(e, extra_module_path?extra_module_path:"");
    evm_prop_set(e, process, "EVM_MODULE_PATH", val);
    val = evm_mk_string(e, app_path);
    evm_prop_set(e, process, "APP_PATH", val);
    evm_val_free(e, val);
}

void evm_module_process(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    setup_env(e, obj);
    evm_module_add(e, "process", obj);
    evm_val_free(e, obj);
    platform_init();
}
