#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif

#ifdef __WIN64__
#include <conio.h>
#endif

#ifdef __linux__
char mygetch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    newt.c_cc[VEOL] = 1;
    newt.c_cc[VEOF] = 2;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#ifdef __WIN64__
char mygetch(void)
{
    return getch();
}

#endif

void evm_repl_init(evm_t *e) {

}

char evm_repl_tty_read(evm_t *e)
{
    EVM_UNUSED(e);
    return mygetch();
}

void evm_repl_tty_write(int n, char *s)
{
    if (n == 1){
        printf("%c", *s);
    } else {
        printf("%s", s);
    }
}


#endif


