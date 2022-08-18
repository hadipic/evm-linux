#include "evm_module.h"

extern void evm_main (const char *file);

int main(int argc, char **argv)
{
    evm_main(argv[1]);
}
