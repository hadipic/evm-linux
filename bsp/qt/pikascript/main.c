#include "evm_module.h"
#include "pikascript.h"

char __platfrom_getChar(void){
    return (char)getchar();
}

int main(int argc, char **argv)
{
    evm_main();
}
