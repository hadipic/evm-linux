/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_TYPE_H
#define EVM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#include "duk_forwdecl.h"
#include "duk_config.h"

#include "duktape.h"

#include "duk_tval.h"
#include "duk_internal.h"
#include "duk_dblunion.h"
#include "duk_fltunion.h"
#include "duk_util.h"
#include "duk_unicode.h"
#include "duk_builtins.h"
#include "duk_lexer.h"
#include "duk_js_bytecode.h"
#include "duk_js_compiler.h"
#include "duk_js.h"
#include "duk_json.h"
#include "duk_heaphdr.h"
#include "duk_hobject.h"
#include "duk_hthread.h"


typedef duk_context evm_t;
typedef duk_tval evm_val_t;

#define EVM_UNDEFINED \
    evm_mk_undefined(e)

typedef duk_int_t (*evm_native_t)(evm_t *);

#define EVM_FUNCTION(name)                                \
  static duk_ret_t name(evm_t *e)

#define EVM_ARGS    e

#define EVM_EPCV \
    int argc = duk_get_top(e);\
    evm_val_t *v = e->valstack_bottom;\
    duk_push_this(e);\
    evm_val_t p = *duk_get_tval(e, -1); \
    evm_val_free(e, p);\

#define EVM_RETURN(x)   \
    x;\
    return 1;\

#define EVM_RETURN_VAL(x)   x;return *duk_get_tval(e, -1);
#define EVM_VARARGS DUK_VARARGS


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
