#include "evm_module.h"

char __platfrom_getChar(void){
    return (char)getchar();
}

int main(int argc, char **argv)
{
    evm_main(argv[1]);
}
