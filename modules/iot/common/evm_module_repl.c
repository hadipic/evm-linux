#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_REPL

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#ifdef __WIN64__
#include <windows.h>
static HANDLE hout;
#endif


#define REPL_BUF_SIZE 128

#define BELL    "\007"
#define CRLF    "\r\n"
#define RIGHT   "\033[C"
#define LEFT    "\010"
#define PROMPT  ">>> "
#define LOGO    "\r\n\
 _____ __     __ __  __ \r\n\
| ____|\\ \\   / /|  \\/  | \r\n\
|  _|   \\ \\ / / | |\\/| | \r\n\
| |___   \\ V /  | |  | | \r\n\
|_____|   \\_/   |_|  |_| \r\n\
                         \r\n\
Github: https://gitee.com/scriptiot/evm \r\n\
Copyright (C) 2022\r\n\
\r\n>>> "

#define REPL_IN       0

enum repl_CTRL_TYPE {
    CON_CTRL_IDLE = 0,
    CON_CTRL_CHAR = 1,
    CON_CTRL_BACKSPACE,
    CON_CTRL_DELETE,
    CON_CTRL_TABLE,
    CON_CTRL_ENTER,
    CON_CTRL_ESCAPE,
    CON_CTRL_UP,
    CON_CTRL_DOWN,
    CON_CTRL_RIGHT,
    CON_CTRL_LEFT,
    CON_CTRL_HOME,
    CON_CTRL_END,
    CON_CTRL_F1,
    CON_CTRL_F2,
    CON_CTRL_F3,
    CON_CTRL_F4
};

enum REPL_HANDLE_RET {
    CON_EXECUTE_DEF = 0,
    CON_PREVENT_DEF = 1
};

static uint16_t repl_cursor = 0;
static int repl_last_key1 = 0;
static int repl_last_key2 = 0;
static size_t _repl_buffer_index = 0;
static char _repl_buffer[REPL_BUF_SIZE];

static int repl_input_insert(int len, char *s);
static void repl_puts(const char *s);
static void repl_putc(int c);
static int repl_input_char(int ch);

static void repl_input_delete(void)
{
    if( _repl_buffer_index <= 0 ) {
        repl_puts(BELL);
        return;
    }
    _repl_buffer_index--;
    _repl_buffer[_repl_buffer_index] = 0;
    repl_puts(LEFT);
    repl_putc(' ');
    repl_puts(LEFT);
}

static void repl_input_enter(void)
{
    _repl_buffer_index = 0;
    memset(_repl_buffer, 0, REPL_BUF_SIZE);
    repl_puts((char*)PROMPT);
}

static void repl_input_seek(int n)
{
    if( n > 0 && _repl_buffer[_repl_buffer_index + 1] != 0) {
        _repl_buffer_index++;
        repl_puts(RIGHT);
    } else if( n < 0 && _repl_buffer_index > 0){
        _repl_buffer_index--;
        repl_puts(LEFT);
    }
}

static int repl_input_parse(const char *input, int end, int *ppos, int *pch)
{
    int  type = CON_CTRL_IDLE;
    int  pos = *ppos;
    char key = input[pos++];

    if (key >= 32 && key < 127 && (repl_last_key2 != 27)) {
        *pch = key;
        type = CON_CTRL_CHAR;
    }
    else {
        if (key == 8) {
            type = CON_CTRL_BACKSPACE;
        } else if (key == 9) {
            type = CON_CTRL_TABLE;
        } else if (key == 13 || key == 10) {
            type = CON_CTRL_ENTER;
        } else if (key == 127) {
            type = CON_CTRL_DELETE;
        } else if (key == 27) {
            if (pos == end) {
                type = CON_CTRL_ESCAPE;
                repl_last_key2 = key;
            }
        } else if (key == 91 && repl_last_key2 == 27) {
            repl_last_key1 = key;
        } else if (repl_last_key2 == 27){
            if (key == 65) {
                type = CON_CTRL_UP;
            } else
            if (key == 66) {
                type = CON_CTRL_DOWN;
            } else
            if (key == 67) {
                type = CON_CTRL_RIGHT;
            } else
            if (key == 68) {
                type = CON_CTRL_LEFT;
            }
            if (key == 70) {
                type = CON_CTRL_END;
            }
            if (key == 72) {
                type = CON_CTRL_HOME;
            }

            repl_last_key2 = 0;
            repl_last_key1 = 0;
        }
#ifdef __WIN64__
        else if (key == -32){
            repl_last_key2 = key;
        }else if (repl_last_key2 == -32){
            if (key == 72) {
                type = CON_CTRL_UP;
            } else
            if (key == 80) {
                type = CON_CTRL_DOWN;
            } else
            if (key == 77) {
                type = CON_CTRL_RIGHT;
            } else
            if (key == 75) {
                type = CON_CTRL_LEFT;
            }
            repl_last_key2 = 0;
        }
#endif
        pos = end; // Skip all left input
    }
    *ppos = pos;

    return type;
}

void repl_exec(evm_t *e, const char *code){
    evm_val_t res = evm_run_string(e, code);
    if( !evm_is_undefined(e, res)) {
        repl_puts(evm_2_string(e, res));
	}
    evm_val_free(e, res);
}


static void repl_input_proc(evm_t *e, int type, int c)
{
    const char * code = _repl_buffer;
    int  len = strlen(code);
    if (type == CON_CTRL_ENTER) {
        repl_puts(CRLF);
#if (defined (__linux__) || defined (__WIN64__))
        if (!strcmp(code, "exit")){
            repl_puts("Thank you! May you enjoy evm!");
            repl_puts(CRLF);
            exit(0);
        }
#endif
        repl_exec(e, code);
        repl_puts(CRLF);
    }

    switch (type) {
    case CON_CTRL_IDLE:         break;
    case CON_CTRL_CHAR:         repl_input_char(c); break;
    case CON_CTRL_BACKSPACE:    repl_input_delete(); break;
    case CON_CTRL_DELETE:       repl_input_delete(); break;
    case CON_CTRL_TABLE:        repl_puts(BELL); break;
    case CON_CTRL_ENTER:        repl_input_enter(); break;
    case CON_CTRL_ESCAPE:       repl_puts(BELL); break;
    case CON_CTRL_UP:           repl_puts(BELL); break;
    case CON_CTRL_DOWN:         repl_puts(BELL); break;
    case CON_CTRL_RIGHT:        repl_input_seek(1);  break;
    case CON_CTRL_LEFT:         repl_input_seek(-1); break;
    case CON_CTRL_HOME:         repl_input_seek(-repl_cursor);  break;
    case CON_CTRL_END:          repl_input_seek(len - repl_cursor); break;
    case CON_CTRL_F1:
    case CON_CTRL_F2:
    case CON_CTRL_F3:
    case CON_CTRL_F4:           repl_puts(BELL); break;
    default: break;
    }
}

static void repl_input_handle(evm_t *e, int n, const void *data)
{
    int pos = 0;
    int ch = '.';
    while (pos < n) {
        int type = repl_input_parse(data, n, &pos, &ch);
        if ( (repl_last_key2 == 27) || (repl_last_key1 == 91)){
            continue;
        }
#ifdef __WIN64__
        if (repl_last_key2 == -32){
            continue;
        }
#endif
        repl_input_proc(e, type, ch);
    }
}

static int repl_init(void)
{
    _repl_buffer_index = 0;
    #ifdef __WIN64__
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

    return 0;
}

static int repl_input_char(int ch)
{
    char c = ch;

    return repl_input_insert(1, &c);
}

static int repl_input_insert(int len, char *s)
{
    if( _repl_buffer_index >= REPL_BUF_SIZE ) {
        _repl_buffer_index = 0;
        _repl_buffer[_repl_buffer_index++] = *s;
        return _repl_buffer_index;
    }
    _repl_buffer[_repl_buffer_index] = *s;
    repl_putc(*s);
    _repl_buffer_index++;
    return _repl_buffer_index;
}

static void repl_putc(int c)
{
    char ch = c;
    evm_repl_tty_write(1, &ch);
}

static void repl_puts(const char *s)
{
    while(*s != 0 ) {
		evm_repl_tty_write(1, (char*)s);
		s++;
	}
}

void evm_run_repl(evm_t *e) {
    evm_repl_init(e);
    repl_init();
    repl_puts((char*)LOGO);
    char input;
    while (1) {
        input = evm_repl_tty_read(e);
		if( input ) 
            repl_input_handle(e, 1, &input);
    }
    repl_puts("Quit repl\r\n");
}


#endif
