#ifdef CONFIG_EVM_MODULE_HTTP_PARSER
#include "evm_module.h"
#include "http_parser.h"


typedef struct _http_options_t {
    evm_val_t value;
} http_options_t;

static evm_val_t get_http_options(http_parser *p){
    http_options_t *http_js =(http_options_t *)p->data;
    return http_js->value;
}

static void set_http_options(http_parser *p, evm_val_t res){
    http_options_t *options = evm_malloc(sizeof (http_options_t));
    options->value = res;
    p->data = (void*)options;
}

static void free_http_options(http_parser *p){
    http_options_t *http_js =(http_options_t *)p->data;
    http_js->value = EVM_UNDEFINED;
    evm_free(p->data);
    p->data = NULL;
}

static int url_cb(http_parser *p, const char *buf, size_t len)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onUrl");
    evm_val_t args[3];
    args[0] = res;
    args[1] = evm_mk_lstring(e, buf, len);
    args[2] = evm_mk_number(e, len);
    evm_call_free(e, cb, EVM_UNDEFINED, 3, args);
    return 0;
}

static int status_cb(http_parser *p, const char *buf, size_t len)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onStatus");
    evm_val_t args[3];
    args[0] = res;
    args[1] = evm_mk_number(e, p->status_code);
    args[2] = evm_mk_lstring(e, buf, len);
    evm_call_free(e, cb, EVM_UNDEFINED, 3, args);
    return 0;
}

static int header_field_cb(http_parser *p, const char *buf, size_t len)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onField");
    evm_val_t args[3];
    args[0] = res;
    args[1] = evm_mk_lstring(e, buf, len);
    args[2] = evm_mk_number(e, len);
    evm_call_free(e, cb, EVM_UNDEFINED, 3, args);
    return 0;
}

static int header_value_cb(http_parser *p, const char *buf, size_t len)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onValue");
    evm_val_t args[3];
    args[0] = res;
    args[1] = evm_mk_lstring(e, buf, len);
    args[2] = evm_mk_number(e, len);
    evm_call_free(e, cb, EVM_UNDEFINED, 3, args);
    return 0;
}

static int body_cb(http_parser *p, const char *buf, size_t len)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onBody");
    evm_val_t args[3];
    args[0] = res;
    args[1] = evm_buffer_create(evm_runtime(), buf, len);
    args[2] = evm_mk_number(e, len);
    evm_call_free(e, cb, EVM_UNDEFINED, 3, args);
    return 0;
}

static int headers_complete_cb(http_parser *p)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onHeadersComplete");
    evm_call(e, cb, EVM_UNDEFINED, 1, &res);
    return 0;
}

static int message_begin_cb(http_parser *p)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onMessageBegin");
    evm_call_free(e, cb, EVM_UNDEFINED, 1, &res);
    return 0;
}

static int message_complete_cb(http_parser *p)
{
    evm_t *e = evm_runtime();
    evm_val_t res = get_http_options(p);
    evm_val_t cb = evm_prop_get(e, res, "onMessageComplete");
    evm_val_t args[2];
    args[0] = res;
    args[1] = evm_mk_number(e, p->status_code);
    evm_call(e, cb, EVM_UNDEFINED, 2, args);
    return 0;
}

static http_parser_settings settings_dontcall = {
    .on_url = url_cb,
    .on_status = status_cb,
    .on_header_field = header_field_cb,
    .on_header_value = header_value_cb,
    .on_body = body_cb,
    .on_message_begin = message_begin_cb,
    .on_headers_complete = headers_complete_cb,
    .on_message_complete = message_complete_cb,
    .on_chunk_header = 0,
    .on_chunk_complete = 0
};

//execute(data)
static evm_val_t module_http_parser_execute(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    http_parser *parser = (http_parser *)evm_object_get_user_data(e, p);
    if( !parser ){
        return EVM_UNDEFINED;
    }

    if( argc == 0 || !evm_is_buffer(e, v[0]) ) {
        return EVM_UNDEFINED;
    }
    size_t nparsed;
    size_t recved = (size_t)evm_buffer_len(e, v[0]);
    nparsed = http_parser_execute(parser, &settings_dontcall, (const char *)evm_buffer_addr(e, v[0]), (size_t)recved);
    if (parser->upgrade) {
        return  evm_mk_boolean(e, 1);
    } else if (nparsed != recved) {
        return  evm_mk_boolean(e, 0);
    }
    return  evm_mk_boolean(e, 1);
}

static evm_val_t module_http_parser_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    EVM_UNUSED(e);EVM_UNUSED(argc);EVM_UNUSED(v);
    http_parser *parser = (http_parser *)evm_object_get_user_data(e, p);
    if( !parser ){
        return EVM_UNDEFINED;
    }
    free_http_options(parser);
    evm_free(parser);
    return EVM_UNDEFINED;
}

//create(type)
static evm_val_t module_http_parser_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    EVM_UNUSED(p);
    if( argc == 0 || !evm_is_number(e, v[0]) ) {
        evm_throw(e, evm_mk_string(e, "Http type must be defined"));
        return EVM_UNDEFINED;
    }
    int type = evm_2_integer(e, v[0]);
    http_parser *parser = evm_malloc(sizeof (http_parser));
    if( !parser ) {
        evm_throw(e, evm_mk_string(e, "Engine runs out of memory"));
        return EVM_UNDEFINED;
    }
    evm_val_t res = evm_object_create_user_data(e, parser);
    evm_prop_set(e, res, "execute", evm_mk_native(e, module_http_parser_execute, "execute", 0));
    evm_prop_set(e, res, "destroy", evm_mk_native(e, module_http_parser_destroy, "destroy", 0));
    http_parser_init(parser, (enum http_parser_type)type);
    set_http_options(parser, res);
    return res;
}

int evm_module_http_parser(evm_t *e) {
    evm_val_t builtin = evm_object_create(e);
    evm_prop_set(e, builtin, "create", evm_mk_native(e, module_http_parser_create, "create", 0));
    evm_prop_set(e, builtin, "REQUEST", evm_mk_number(e, HTTP_REQUEST));
    evm_prop_set(e, builtin, "RESPONSE", evm_mk_number(e, HTTP_RESPONSE));
    evm_module_add(e, "http_parser", builtin);
    return 1;
}
#endif
