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

extern int platform_getchar(void);

EVM_FUNCTION(console_log) {
    EVM_EPCV;
    for (int i = 0; i < argc; i++) {
        char *s = evm_2_string(e, v[i]);
        printf("%s", s);
        evm_string_free(e, s);
    }
    printf("\r\n");
    EVM_RETURN(evm_mk_undefined(e))
}

//write(buf)
EVM_FUNCTION(console_write) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[0]);
    printf("%s", s);
    evm_string_free(e, s);
    EVM_RETURN(evm_mk_undefined(e))
}

//getc()
EVM_FUNCTION(console_getc) {
    EVM_EPCV;
    int c = platform_getchar();
    EVM_RETURN(evm_mk_number(e, c));
}

void evm_module_console(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "log", evm_mk_native(e, console_log, "log", EVM_VARARGS));
    evm_prop_set(e, obj, "getc", evm_mk_native(e, console_getc, "getc", EVM_VARARGS));
    evm_prop_set(e, obj, "write", evm_mk_native(e, console_write, "write", EVM_VARARGS));
    evm_global_set(e, "console", obj);
    evm_val_free(e, obj);
}

