#include "evm_module.h"

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif


#ifdef __WIN64__
#include <conio.h>
#endif

#ifdef __linux__
char platform_getchar(void)
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
char platform_getchar(void)
{
    return getch();
}
#endif

void platform_init() {

}
