#include "evm.h"

//内置函数，打印hello world
evm_val_t native_print_helloworld(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    printf("hello world\r\n");
    return evm_mk_undefined(e);
}

int main()
{
    evm_t *e = evm_init();
    if (!e) {
        printf("Could not initialize EVM.\r\n");
        return 0;
    }

    //添加内置函数
    evm_val_t val = evm_mk_native(e, native_print_helloworld, "print_hello_world", 0);
    evm_global_set(e, "print_helloworld", val);
    evm_val_free(e, val);

    //运行内置函数
    val = evm_load_string(e, "print_helloworld();");
    evm_val_t pthis = evm_mk_undefined(e);
    evm_call_free(e, val, pthis, 0, NULL);
    evm_val_free(e, val);
    evm_val_free(e, pthis);
    evm_deinit(e);
}
