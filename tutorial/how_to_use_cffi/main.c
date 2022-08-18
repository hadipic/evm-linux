#include "evm_module.h"

int add(int a, int b) {
    printf("result = %d\r\n", a + b);
    return a + b;
}

static evm_module_cffi_t cffis[] = {
    {"add", add, "iii"},
    {NULL, 0, NULL}
};

int main()
{
    evm_t *e = evm_init();
    if (!e) {
        printf("Could not initialize EVM.\r\n");
        return 0;
    }
    //初始化evm模块
    evm_module_init(e);
    //注册c函数到cffi
    evm_module_cffi_add(e, cffis);
    //运行代码
    evm_run_file(e, "../../test/test_cffi.js");
    evm_deinit(e);
}
