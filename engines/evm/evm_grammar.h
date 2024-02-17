#ifndef EVM_GRAMMAR_H
#define EVM_GRAMMAR_H

#include "evm.h"

#define EVM_VARNAME_LEN         128

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

typedef int (*grammar_cfunc_t)(struct evm_parser_t *p);

#define ELEMENT_SECTION\
    uint8_t token;\
    uint8_t suffix;\
    int row;\
    void *action;\

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
    evm_t *e;
    double num;
    char name[EVM_VARNAME_LEN];
    evm_atom_t atom_str;
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
} evm_parser_t;

EVM_API evm_val_t evm_function_create(evm_t *e);
EVM_API evm_atom_t evm_str_insert(evm_t *e, const char *str, int alloc);
EVM_API const char *evm_atom_to_string(evm_t * e, evm_atom_t key);
EVM_API evm_grm_t *evm_load_grammar(evm_t *e, const char *file, grammar_cfunc_t *cfuncs);
EVM_API int evm_parse(evm_t *e, char *file);
EVM_API evm_val_t evm_atom_get(evm_t * e, evm_atom_t key);

#endif

