/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bflb_uart.h"

void *evm_malloc(size_t size)
{
    void * m = malloc(size);
    if( m )
        memset(m, 0 ,size);
    return m;
}

void evm_free(void * p)
{
    if(p)
        free(p);
}

void *evm_realloc(void * p, size_t size)
{
    return realloc(p, size);
}

uint8_t *evm_load_file(const char *filename, size_t *size) {
    FILE *f;
    uint8_t *buf;
    size_t buf_len;
    long lret;
    f = fopen(filename, "rb");
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

static int strEndswith(const char *str1, const char *str2)
{
    size_t l1 = strlen(str1), l2 = strlen(str2);
    return (0 == strcmp(str2, str1 + (l1 - l2)));
}

void evm_main (char *filename) {
    EVM_LOG("evm init\r\n");
    evm_t *e = evm_init();
    EVM_LOG("evm module init\r\n");
    evm_module_init(e);
    EVM_LOG("evm load file %s\r\n", filename);
    if (strEndswith(filename, "js")) {
        evm_run_file(e, EVM_UNDEFINED, filename);
    } else {
        evm_run_bytecode_file(e, filename);
    }
}