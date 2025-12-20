#ifndef EVM_GRAMMAR_H
#define EVM_GRAMMAR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define grm_malloc  malloc
#define grm_free    free

#define EVM_VARNAME_LEN         128
#define EVM_GRM_ARG_LEN         8
#define EVM_GRM_ARG_STACK_SIZE  32

enum TOKEN {
    TOKEN_FAIL = 0,
    TOKEN_OK,
    TOKEN_GRAMMAR,
    TOKEN_RULE,
    TOKEN_ALTERNATIVE,
    TOKEN_STRING,
    TOKEN_BLOCK,
    TOKEN_ID,
    TOKEN_QM,
    TOKEN_PLUS,
    TOKEN_STAR,
    TOKEN_REGEX,
    TOKEN_ACTION,
    TOKEN_LEX_EOF,
    TOKEN_LEX_STRING,
    TOKEN_LEX_NUMBER,
    TOKEN_LEX_ID,
    TOKEN_LEX_NEWLINE,
    TOKEN_CFUNC,
};

struct evm_parser_t;

typedef struct evm_grm_arg_t {
    union {
        int64_t int64;
        double number;
        char *str;
        void *ptr;
    }u;
} evm_grm_arg_t;

typedef struct evm_grm_ret_t {
    int token;
    evm_grm_arg_t arg1;
    evm_grm_arg_t arg2;
} evm_grm_ret_t;

typedef void (*grammar_cfunc_t)(struct evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);

#define ELEMENT_SECTION\
    uint8_t token;\
    uint8_t suffix;\
    int row;\

typedef struct evm_grm_elem_t {
    ELEMENT_SECTION;
    union {
        const char *text;
        const struct evm_grm_rule_t *rule;
        grammar_cfunc_t cfunc;
    } u;
} evm_grm_elem_t;

typedef struct evm_grm_alt_t {
    ELEMENT_SECTION;
    int size;
    const evm_grm_elem_t *elems;
} evm_grm_alt_t;

typedef struct evm_grm_rule_t {
    ELEMENT_SECTION;
    int size;
    const evm_grm_alt_t **alts;
} evm_grm_rule_t;

typedef struct evm_grm_t {
    int size;
    const evm_grm_rule_t *rules;
} evm_grm_t;

typedef struct evm_parser_t {
    double num;
    char name[EVM_VARNAME_LEN];
    char *str;
    int str_len;
    char *input;
    int input_len;
    int index;
    int row;
    const evm_grm_t *grammar;
    const char *multi_comment_pattern;
    const char *multi_comment_start;
    const char *single_comment_pattern;
    const char *single_comment_start;
    grammar_cfunc_t *cfuncs;
    evm_grm_arg_t *arg_sp_base;
    evm_grm_arg_t *arg_sp;
    int arg_stack_size;
} evm_parser_t;

extern void evm_push_arg(evm_parser_t *p, evm_grm_arg_t arg);
extern evm_grm_arg_t evm_get_arg(evm_parser_t *p, int idx);
extern evm_grm_arg_t evm_pop_arg(evm_parser_t *p);
extern evm_grm_t *evm_load_grammar(const char *file, grammar_cfunc_t *cfuncs);
extern int evm_parse(char *content);

#endif

