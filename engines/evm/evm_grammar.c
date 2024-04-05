#include "evm_grammar.h"

static inline char parse_next_ch(evm_parser_t *p, int index)
{
    return p->input[index];
}

static inline int parse_token_id(evm_parser_t *p, char *str, int len)
{
    char ch;
    int index = p->index;
    int str_index = 0;
    ch = p->input[index];
    do {
        if( ch != str[str_index] )
            return 0;
        index++;
        str_index++;
        ch = parse_next_ch(p, index);
    } while ( isalnum(ch) || ch == '_');

    if(str_index == len)
        return 1;
    return 0;
}

static inline void parse_eat_token(evm_parser_t *p, int len)
{
    p->index += len;
}

static int parse_token(evm_parser_t *p, const char *str, int len)
{
    char ch;
    int first_index = p->index;
    int index = p->index;
    int str_index = 0;

    if( parse_next_ch(p, index) == 0) {
        return TOKEN_FAIL;
    }

    if(isalpha(parse_next_ch(p, index)) || parse_next_ch(p, index) == '_')
        return parse_token_id(p, str, len);

    do {
        ch = parse_next_ch(p, index);
        if( ch == 0) {
            p->index = first_index;
            return TOKEN_FAIL;
        }
        if( ch != str[str_index] )
            return 0;
        index++;
        str_index++;
    } while ( str_index < len);

    return 1;
}

static int parse_token_with_eat(evm_parser_t *p, const char *str, int len)
{
    int res = parse_token(p, str, len);
    if(res)
        parse_eat_token(p, len);
    return res;
}

static inline int parse_hex_to_int(char s[])
{
    int i;
    int n = 0;
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))
        i = 2;
    else
        i = 0;
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i){
        if (tolower(s[i]) > '9')
            n = 16 * n + (10 + tolower(s[i]) - 'a');
        else
            n = 16 * n + (tolower(s[i]) - '0');
    }
    return n;
}

static inline int parse_is_hex(int c)
{
    if( isdigit(c) )
        return TOKEN_OK;
    if( c == 'x' || c == 'X')
        return TOKEN_OK;
    if( c >= 'a' && c <= 'f')
        return TOKEN_OK;
    if( c >= 'A' && c <= 'F')
        return TOKEN_OK;
    return TOKEN_FAIL;
}

#ifndef isalpha
#define isalpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#endif
#ifndef isdigit
#define isdigit(c) (c >= '0' && c <= '9')
#endif
#ifndef ishex
#define ishex(c) ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
#endif

static int parse_iswhite(int c)
{
    return c == 0x9 || c == 0xB || c == 0xC || c == 0x20 || c == 0xA0 || c == 0xFEFF;
}

static int parse_isnewline(int c)
{
    return c == 0xA || c == 0xD || c == 0x2028 || c == 0x2029;
}

static int parse_ishex(int c)
{
    return isdigit(c) || ishex(c);
}

static uint32_t const id_continue_table_ascii[4] = {
    0x00000000, 0x03FF0010, 0x87FFFFFE, 0x07FFFFFE
};

static inline int is_ident_next(int c)
{
    if ((uint32_t)c < 128) {
        return (id_continue_table_ascii[c >> 5] >> (c & 31)) & 1;
    } else {
        return !parse_iswhite(c) || c == 0x200C || c == 0x200D;
    }
}

static int parse_ident(evm_parser_t *p, char *name)
{
    char ch;
    int index;
    int len = 0;

    if(isdigit(parse_next_ch(p, p->index)))
        return TOKEN_FAIL;

    while(1) {
        index = p->index;
        ch = p->input[index];
        if( len >= EVM_VARNAME_LEN ) return TOKEN_FAIL;

        if( isalnum(ch) || '_' == ch || '$' == ch ) {
            p->index++;
            name[len] = ch;
            len++;
        } else {
            if(len)
            {
                name[len] = 0;
                return TOKEN_OK;
            }
            else
                return TOKEN_FAIL;
        }
    }
}

static int parse_check_escape(evm_parser_t *p, char *input) {
    char ch = input[0];
    if( ch == '\\' ) {
        ch = input[1];
        switch(ch) {
        case 'b': return '\b';
        case 'x': return 'x';
        case 'v': return '\v';
        case 'f': return '\f';
        case 'r': return '\r';
        case 'n': return '\n';
        case 't': return '\t';
        case '\'':return '\'';
        case '\\':{
            return '\\';
        }
        case '0':return '\0';
        case '"': return '"';
        default:
            return -1;
        }
    }
    return -1;
}

static int parse_check_str_len(evm_parser_t *p){
    uint8_t ch = 0;
    int len = 0;
    char *input = (char*)p->input + p->index;
    int doubleQuote = -1;
    if( input[0] == '"' ) {
        doubleQuote = 1;
    } else if( input[0] == '\'') {
        doubleQuote = 0;
    }
    char flag = 1;
    int escape_flag = 1;
    if( doubleQuote >= 0 ) {
        input++;
        do {
            if( input[0] == 0 )
                return -1;

            if( parse_check_escape(p, input) == -1) {
                ch = input[0];
                if( ch == '"' && doubleQuote == 0 ){
                    escape_flag = !escape_flag;
                } else if ( ch == '\'' && doubleQuote == 1) {
                    escape_flag = !escape_flag;
                }
                if( ch == '\\') {
                    input += 1;
                } else {
                    len += 1;
                    input++;
                }
            } else {
                ch = input[0];
                input += 2;
                if( escape_flag == 1)
                    len+=1;
                else
                    len += 2;
            }

            if( ch == 0x0D || ch == 0x0A ){
                return -1;
            }

            if( doubleQuote == 1 && ch == '"')
                flag = 0;

            if( doubleQuote == 0 && ch == '\'')
                flag = 0;
        } while( flag );
        return len;
    }
    return -1;
}

static uint8_t parse_hex_to_char(char ch)
{
    int n;
    if (tolower(ch) > '9')
        n = (10 + tolower(ch) - 'a');
    else
        n = (tolower(ch) - '0');
    return n;
}

static char *parse_stringLiteral(evm_parser_t *p)
{
    uint8_t ch;
    int escape;
    char flag = 1;
    int len = 0;
    len = parse_check_str_len(p);
    if( len == -1 )
        return NULL;
    char *str = (char*)grm_malloc(len);
    if( !str ) {
        return NULL;
    }
    memset(str, 0, len);
    len = 0;
    const char *input = p->input + p->index;
    int doubleQuote = -1;
    if( input[0] == '"' ) {
        doubleQuote = 1;
    } else if( input[0] == '\'') {
        doubleQuote = 0;
    }
    int escape_flag = 1;
    if( doubleQuote >= 0 ) {
        input++;
        p->index++;
        do {
            escape =parse_check_escape(p, input);
            if( escape == -1 ) {
                ch = input[0];
                if( ch == '"' && doubleQuote == 0 ){
                    escape_flag = !escape_flag;
                } else if ( ch == '\'' && doubleQuote == 1) {
                    escape_flag = !escape_flag;
                }
                if( ch == '\\' && escape_flag) {
                    input++;
                    p->index++;
                } else {
                    str[len++] = ch;
                    input++;
                    p->index++;
                }
            } else {
                if( escape_flag == 1) {
                    p->index += 2;
                    input += 2;
                    if( escape == 'x') {
                        if( !parse_is_hex(input[0]) || !parse_is_hex(input[1]) ) {
                            grm_free(str);
                            return NULL;
                        }
                        escape = parse_hex_to_char(input[0]);
                        escape <<= 4;
                        escape |= parse_hex_to_char(input[1]);
                        p->index += 2;
                        input += 2;
                    }
                    str[len++] = escape;
                } else {
                    str[len++] = input[0];
                    p->index += 1;
                    input += 1;
                    str[len++] = input[0];
                    p->index += 1;
                    input += 1;
                }
            }

            if( ch == 0x0D || ch == 0x0A ){
                grm_free(str);
                return NULL;
            }

            if( doubleQuote == 1 && ch == '"')
                flag = 0;

            if( doubleQuote == 0 && ch == '\'')
                flag = 0;
        } while( flag );
        str[len - 1] = 0;
        p->str_len = len;
        return str;
    }
    return NULL;
}

static int parse_numericLiteral(evm_parser_t *p)
{
    char ch;
    char *str = p->name;
    int len = 0;
    int index = p->index;
    if( isdigit( parse_next_ch(p, index) ) || parse_token(p, ".", 1) ) {
        do {
            index =  p->index;
            ch = parse_next_ch(p, index);
            if( !isdigit(ch) ) break;
            str[len++] = ch;
            p->index++;
        } while(isdigit(ch));

        if( parse_token(p, ".", 1) ) {
            if( len == 0 ){
                str[len++] = '0';
            }
            str[len++] = '.';
            parse_eat_token(p, 1);
            do {
                index =  p->index;
                ch = parse_next_ch(p, index);
                if( !isdigit(ch) ) break;
                str[len++] = ch;
                p->index++;
            } while(isdigit(ch));
        }

        if( p->input[p->index] == 'e' || p->input[p->index] == 'E' ) {
            parse_eat_token(p, 1);
            str[len++] = 'E';
            if( p->input[p->index] == '+' ) {
                str[len++] = '+';
                parse_eat_token(p, 1);
            } else if( p->input[p->index] == '-' ) {
                str[len++] = '-';
                parse_eat_token(p, 1);
            }
            do {
                index =  p->index;
                ch = parse_next_ch(p, index);
                if( !isdigit(ch) ) break;
                str[len++] = ch;
                p->index++;
            } while(isdigit(ch));
        }
        str[len++] = 0;
        p->num = atof(str);
        return TOKEN_LEX_NUMBER;
    }
    return TOKEN_FAIL;
}

static int parse_EOF(evm_parser_t *p)
{
    if( p->index >= p->input_len )
        return TOKEN_OK;
    if( !parse_next_ch(p, p->index) )
        return TOKEN_OK;
    return TOKEN_FAIL;
}

static int multicomment(evm_parser_t *p, const char *pattern)
{
    if( parse_token_with_eat(p, p->multi_comment_start, strlen(p->multi_comment_start)) ) {
        do {
            if( parse_token_with_eat(p, pattern + 3, strlen(pattern + 3)) ) {
                return TOKEN_OK;
            }
            if( p->input[p->index] == '\n' ) {
                p->row++;
            }
            if( parse_next_ch(p, p->index) == 0 ) {
                return TOKEN_OK;
            }
            p->index++;
        } while(1);
    } else
        return TOKEN_FAIL;
}

static int singlecomment(evm_parser_t *p, const char *pattern)
{
    if( parse_token_with_eat(p, p->single_comment_start, strlen(p->single_comment_start)) ) {
        do {
            if( p->input[p->index] == '\n' ) {
                p->index++;
                p->row++;
                return TOKEN_OK;
            }
            if( parse_next_ch(p, p->index) == 0 ) {
                return TOKEN_OK;
            }
            p->index++;
        } while(1);
    } else
        return TOKEN_FAIL;
}

static int grammar_LT_NL(evm_parser_t *e)
{
    int index = e->index;
    if( e->multi_comment_start
            && e->multi_comment_pattern
            && parse_token(e, e->multi_comment_start, strlen(e->multi_comment_start))
            && multicomment(e, e->multi_comment_pattern) )
        return 1;
    if( e->single_comment_start
            && e->single_comment_pattern
            && parse_token(e, e->single_comment_start, strlen(e->single_comment_start))
            && singlecomment(e, e->single_comment_pattern) )
        return 1;
    int ch = parse_next_ch(e, index);
    if( parse_iswhite(ch) ) {
        e->index++;return 1;
    } else if( parse_isnewline(ch) ){
        e->index++;
        e->row++;
        return 1;
    }
    return 0;
}

static void parse_init(evm_parser_t *p, char *content){
    memset(p, 0, sizeof(evm_parser_t));
    p->input = content;
    p->input_len = strlen(p->input);
    p->row = 1;
    p->index = 0;
    p->str = NULL;
    p->multi_comment_pattern = NULL;
    p->multi_comment_start = NULL;
    p->single_comment_pattern = NULL;
    p->single_comment_start = NULL;
    p->arg_sp_base = p->arg_sp = grm_malloc(sizeof (evm_grm_t) * EVM_GRM_ARG_STACK_SIZE);
    p->arg_stack_size = EVM_GRM_ARG_STACK_SIZE;
}

#define LT_NT   while(grammar_LT_NL(p))

static evm_grm_ret_t run_rule(evm_parser_t *p, const evm_grm_rule_t *rule, evm_grm_arg_t *args, evm_grm_ret_t *prev_ret);

static evm_grm_ret_t run_element(evm_parser_t *p, const evm_grm_elem_t *elem, evm_grm_arg_t *args, evm_grm_ret_t last_ret) {
    LT_NT;
    int tk = elem->token;
    evm_grm_ret_t ret = last_ret;
    switch (tk) {
    case TOKEN_CFUNC: {
        elem->u.cfunc(p, args, &ret);
        if( !ret.token ) {
            return ret;
        }
        return ret;
    }break;
    case TOKEN_ID: {
        const evm_grm_rule_t *rule = elem->u.rule;
        int suffix = elem->suffix;
        if( suffix == TOKEN_STAR ) {
            while( 1 ) {
                evm_grm_ret_t local_ret = run_rule(p, rule, args, &ret);
                if( !local_ret.token )
                    break;
                ret = local_ret;
            }
            return ret;
        } else if( suffix == TOKEN_PLUS ) {
            evm_grm_ret_t local_ret = run_rule(p, rule, args, &ret);
            if( !local_ret.token ) {
                return local_ret;
            }
            ret = local_ret;
            while( 1 ) {
                local_ret = run_rule(p, rule, args, &ret);
                if( !local_ret.token )
                    break;
                ret = local_ret;
            }
            return ret;
        } else if( suffix == TOKEN_QM ) {
            evm_grm_ret_t local_ret = run_rule(p, rule, args, &ret);
            if( local_ret.token ){
                 ret = local_ret;
            }
            return ret;
        }
        ret = run_rule(p, rule, NULL, &ret);
        return ret;
    } break;
    case TOKEN_STRING: {
        if( !parse_token_with_eat(p, elem->u.text, strlen(elem->u.text)) ) {
            break;
        }
        return ret;
    }break;
    case TOKEN_LEX_EOF: {
        if( !parse_EOF(p) )
            break;
        ret.token = TOKEN_LEX_EOF;
        return ret;
    } break;
    case TOKEN_LEX_NUMBER: {
        if( !parse_numericLiteral(p) )
            break;
        ret.token = TOKEN_LEX_NUMBER;
        return ret;
    } break;
    case TOKEN_LEX_STRING: {
        char *str = parse_stringLiteral(p);
        if( !str )
            break;
        if( p->str )
            grm_free(p->str);
        p->str = str;
        ret.token = TOKEN_LEX_STRING;
        return ret;
    } break;
    case TOKEN_LEX_NEWLINE:{
        int index = p->index;
        while(index > 0 ){
            index--;
            if( parse_iswhite(p->input[index]) )
                continue;
            else if( parse_isnewline(p->input[index]) )
                return ret;
            else{
                ret.token = TOKEN_FAIL;
                return ret;
            }
        }
        ret.token = TOKEN_FAIL;
        return ret;
    }
    case TOKEN_LEX_ID: {
        if( !parse_ident(p, p->name) )
            break;
        ret.token = TOKEN_LEX_ID;
        return ret;
    } break;
    case TOKEN_BLOCK: {
        int suffix = elem->suffix;
        if( suffix == TOKEN_STAR ) {
            while(1) {
                evm_grm_ret_t local_ret = run_rule(p, elem->u.rule, args, &ret);
                if( !local_ret.token )
                    break;
                ret = local_ret;
            }
            return ret;
        } else if( suffix == TOKEN_PLUS ) {
            ret = run_rule(p, elem->u.rule, args, &ret);
            if( !ret.token ){
                return ret;
            }
            while(1) {
                evm_grm_ret_t local_ret = run_rule(p, elem->u.rule, args, &ret);
                if( !local_ret.token )
                    break;
                ret = local_ret;
            }
            return ret;
        } else if( suffix == TOKEN_QM ) {
            evm_grm_ret_t local_ret = run_rule(p, elem->u.rule, args, &ret);
            if( local_ret.token ){
                ret = local_ret;
            }
            return ret;
        } else {
            ret = run_rule(p, elem->u.rule, args, &ret);
            return ret;
        }
    }break;
    }
    ret.token = TOKEN_FAIL;
    return ret;
}

static evm_grm_ret_t run_alternative(evm_parser_t *p, const evm_grm_alt_t *alt, evm_grm_arg_t *args, evm_grm_ret_t *prev_ret) {
    evm_grm_ret_t ret = {.token = TOKEN_OK};
    if( prev_ret )
        ret = *prev_ret;
    for(int i = 0; i < alt->size; i++) {
        const evm_grm_elem_t *elem = alt->elems + i;
        ret = run_element(p, elem, args, ret);
        if( !ret.token )
            return ret;
    }
    return ret;
}

static evm_grm_ret_t run_rule(evm_parser_t *p, const evm_grm_rule_t *rule, evm_grm_arg_t *args, evm_grm_ret_t *prev_ret) {
    evm_grm_ret_t ret = {.token = TOKEN_FAIL};
    for(int i = 0; i < rule->size; i++) {
        int index = p->index;
        int save_row = p->row;
        const evm_grm_alt_t *alt = rule->alts[i];
        if( !args ) {
            evm_grm_arg_t local_args[EVM_GRM_ARG_LEN];
            ret = run_alternative(p, alt, local_args, prev_ret);
            if( ret.token )
                return ret;
        } else {
            ret = run_alternative(p, alt, args, prev_ret);
            if( ret.token )
                return ret;
        }
        p->row = save_row;
        p->index = index;
    }
    return ret;
}

static int run_grammar(evm_parser_t *p) {
    const evm_grm_rule_t *rule = p->grammar->rules;
    return run_rule(p, rule, NULL, NULL).token;
}

static void check_arg_stack(evm_parser_t *p) {
    if( p->arg_sp - p->arg_sp_base >= p->arg_stack_size ) {
        int new_size = p->arg_stack_size + EVM_GRM_ARG_STACK_SIZE;
        evm_grm_arg_t *old_args = p->arg_sp_base;
        p->arg_sp_base = grm_malloc(sizeof (evm_grm_t) * new_size);
        memcpy(p->arg_sp_base, old_args, sizeof (evm_grm_t) * p->arg_stack_size);
        p->arg_sp = p->arg_sp_base + p->arg_stack_size;
        p->arg_stack_size += EVM_GRM_ARG_STACK_SIZE;
        grm_free(old_args);
    }
}

void evm_push_arg(evm_parser_t *p, evm_grm_arg_t arg) {
    check_arg_stack(p);
    *(p->arg_sp++) = arg;
}

evm_grm_arg_t evm_get_arg(evm_parser_t *p, int idx) {
    return *(p->arg_sp + idx - 1);
}

evm_grm_arg_t evm_pop_arg(evm_parser_t *p) {
    if( p->arg_sp > p->arg_sp_base )
        return *(--p->arg_sp);
    evm_grm_arg_t ret;
    ret.u.ptr = NULL;
    return ret;
}

extern const evm_grm_t evm_grammar;

int evm_parse(char *content) {
    evm_parser_t p;
    parse_init(&p, content);
    p.grammar = &evm_grammar;
    int tok = run_grammar(&p);
    if(p.str)
        grm_free(p.str);
    grm_free(p.arg_sp_base);
    return tok;
}

