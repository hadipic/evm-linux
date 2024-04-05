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
#include <time.h>
#include "iotjs.h"

int platform_getchar(void) {
    return getchar();
}

void platform_init(void) {

}

void *evm_malloc(size_t size)
{
    void * m = zmalloc(size);
    if( m )
        memset(m, 0 ,size);
    return m;
}

void evm_free(void * p)
{
    if(p)
        zfree(p);
}

void *evm_realloc(void * p, size_t size)
{
    return zrealloc(p, size);
}

uint8_t *evm_load_file(const char *filename, size_t *size) {
    FILE *f;
    uint8_t *buf;
    size_t buf_len;
    long lret;
    f = fopen(filename, "r");
    if (!f)
        return NULL;
    if (fseek(f, 0, SEEK_END) < 0)
        goto fail;
    lret = ftell(f);
    if (lret < 0)
        goto fail;

    buf_len = lret;
    if (fseek(f, 0, SEEK_SET) < 0)
        goto fail;
    buf = evm_malloc(buf_len + 1);
    if (!buf)
        goto fail;
    if (fread(buf, 1, buf_len, f) != buf_len) {
        evm_free(buf);
    fail:
        fclose(f);
        return NULL;
    }
    buf[buf_len] = '\0';
    fclose(f);
    *size = buf_len;
    return buf;
}

EVM_FUNCTION(native_clock) {
    EVM_EPCV;
    double clk = clock();
    EVM_RETURN_VAL(evm_mk_number(e,  clk / CLOCKS_PER_SEC));
}

void evm_main (char *filename) {
    evm_t *e = evm_init();
    evm_module_init(e);
    extern void evm_module_console(evm_t *e);
    evm_module_console(e);
    evm_run_file(e, EVM_UNDEFINED, filename);
    printf("finished");
}

