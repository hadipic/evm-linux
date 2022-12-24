#ifndef QUICKVM_JS_PARSE
#define QUICKVM_JS_PARSE

#include "quickvm.h"

#define QVM_VAR_NAME_LEN    256

QVM_API qvm_value_t qvm_js_parse(qvm_state_t *e, const char *path);
QVM_API qvm_value_t qvm_js_parse_string(qvm_state_t *e, char *content);

#endif
