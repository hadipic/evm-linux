#ifdef CONFIG_EVM_MODULE_LIBC
#include "evm_module.h"

static evm_module_cffi_t cffi_file[] = {
    {"fopen", fopen, "pss"},
    {"fclose", fclose, "p"},
    {"fread", fread, "isiip"},
    {"fwrite", fwrite, "isiip"},
    {"fseek", fseek, "ipii"},
    {"ftell", ftell, "ip"},
    {"fflush", fflush, "ip"},
    {NULL, 0, NULL}
};

evm_err_t evm_module_libc(evm_t *e)
{
    evm_module_cffi_add(e, cffi_file);
    return ec_ok;
}
#endif
