#ifdef CONFIG_EVM_MODULE_CFFI
#include "evm_module.h"

enum
{
    CFFI_OK,
    CFFI_FUNCTION_NOT_EXISTED,
    CFFI_ARG_TYPE_IS_NOT_BOOL,
    CFFI_ARG_TYPE_IS_NOT_INT,
    CFFI_ARG_TYPE_IS_NOT_FLOAT,
    CFFI_ARG_TYPE_IS_NOT_DOUBLE,
    CFFI_ARG_TYPE_IS_NOT_STRING,
    CFFI_ARG_TYPE_IS_NOT_CPOINTER,
    CFFI_ARG_TYPE_NOT_SUPPORT,
    CFFI_RETURN_TYPE_CPOINTER_IS_NULL,
    CFFI_RETURN_TYPE_EVM_TYPE_IS_NULL,
    CFFI_RETURN_TYPE_STRING_CREATE_FAILED,
    CFFI_RETURN_TYPE_BUFFER_CREATE_FAILED,
    CFFI_RETURN_TYPE_NOT_SUPPORT
};

typedef uint8_t CFFI_ERROR;

#define FFI_ARGS \
    fargs[0], fargs[1], fargs[2], fargs[3], fargs[4], fargs[5], fargs[6], fargs[7], \
    fargs[8], fargs[9], fargs[10], fargs[11], fargs[12], fargs[13], fargs[14], fargs[15], \
    fargs[16], fargs[17], fargs[18], fargs[19], fargs[20], fargs[21], fargs[22], fargs[23], \
    fargs[24], fargs[25], fargs[26], fargs[27], fargs[28], fargs[29], fargs[30], fargs[31]

typedef intptr_t  qint;

typedef qint (*func_p_0)(uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_1)(uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_2)(double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_3)(double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_4)(uintptr_t,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_5)(uintptr_t,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_6)(double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_7)(double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_0b1110)(double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_0b1111)(double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_0b11110)(double,double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_0b11111)(double,double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_0b111110)(double,double,double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_0b111111)(double,double,double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_0b1111110)(double,double,double,double,double,double,uintptr_t,uintptr_t,uintptr_t);
typedef double (*func_p_0b1111111)(double,double,double,double,double,double,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_0b11111110)(double,double,double,double,double,double,double,uintptr_t,uintptr_t);
typedef double (*func_p_0b11111111)(double,double,double,double,double,double,double,uintptr_t,uintptr_t);
typedef qint (*func_p_0b111111110)(double,double,double,double,double,double,double,double,uintptr_t);
typedef double (*func_p_0b111111111)(double,double,double,double,double,double,double,double,uintptr_t);
typedef qint (*func_p_0b1111111110)(double,double,double,double,double,double,double,double,double);
typedef double (*func_p_0b1111111111)(double,double,double,double,double,double,double,double,double);

typedef qint (*func_p_12)(qint,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_24)(qint,qint,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_28)(qint,double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_60)(qint,double,double,double,double,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_124)(qint,double,double,double,double,double,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_p_252)(qint,double,double,double,double,double,double,uintptr_t,uintptr_t);


typedef float (*func_f_1)(uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_2)(float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_3)(float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_4)(uintptr_t,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_5)(uintptr_t,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_6)(float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_7)(float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_0b1110)(float,float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_0b1111)(float,float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_0b11110)(float,float,float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_0b11111)(float,float,float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_0b111110)(float,float,float,float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_0b111111)(float,float,float,float,float,uintptr_t,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_0b1111110)(float,float,float,float,float,float,uintptr_t,uintptr_t,uintptr_t);
typedef float (*func_f_0b1111111)(float,float,float,float,float,float,uintptr_t,uintptr_t,uintptr_t);
typedef qint (*func_f_0b11111110)(float,float,float,float,float,float,float,uintptr_t,uintptr_t);
typedef float (*func_f_0b11111111)(float,float,float,float,float,float,float,uintptr_t,uintptr_t);
typedef qint (*func_f_0b111111110)(float,float,float,float,float,float,float,float,uintptr_t);
typedef float (*func_f_0b111111111)(float,float,float,float,float,float,float,float,uintptr_t);
typedef qint (*func_f_0b1111111110)(float,float,float,float,float,float,float,float,float);
typedef float (*func_f_0b1111111111)(float,float,float,float,float,float,float,float,float);

union _ffi_val { void *p; uintptr_t w; double d; float f; qint i64; };
typedef  union _ffi_val ffi_val;

typedef ffi_val (*func_p)(ffi_val ,...);

ffi_val fficall(const char* signature, ...){
    int fargc = strlen(signature) - 1;
    ffi_val fargs[fargc], res;

    va_list args;
    va_start(args, signature);
    uintptr_t f = va_arg(args, uintptr_t);
    for(int i = 0; i < fargc; i++)
    {
      fargs[i] = va_arg(args, ffi_val);
    }
    va_end(args);

    res = ((func_p)f)(FFI_ARGS);

    return res;
}

static CFFI_ERROR error_code = CFFI_OK;

static evm_val_t cffi_exec(evm_t *e, evm_val_t p, int argc, evm_val_t *v, const char *funcname, const char * signature, uintptr_t funcID){
    error_code = CFFI_OK;
    int i = 0;
    int fargc = strlen(signature) - 1;
    int type = (signature[0] == 'd' || signature[0] == 'f') ? 1 : 0;

    int offset = 0;
    if (signature[0] == 'f'){
        offset = 100;
    }
    ffi_val fargs[fargc], res;
    for (i = 0; i < fargc; i++) {
        if ( signature[i+1] == 'd' || signature[i+1] == 'f' ) {
          type |= 1 << (i + 1);
        }
        evm_val_t value = *(v+i);
        switch (signature[i + 1]) {
            case 'b': {
                if (!evm_is_boolean(e, value)){
                    error_code = CFFI_ARG_TYPE_IS_NOT_BOOL;
                    goto failed;
                }
                fargs[i].w = evm_2_boolean(e, value);
            }break;
            case 'i': {
                if (!evm_is_number(e, value)){
                    error_code = CFFI_ARG_TYPE_IS_NOT_INT;
                    goto failed;
                }
                fargs[i].w = evm_2_integer(e, value);
            } break;
            case 'd': {
                if (!evm_is_number(e, value)){
                    error_code = CFFI_ARG_TYPE_IS_NOT_DOUBLE;
                    goto failed;
                }
                fargs[i].d = evm_2_double(e, value);
            }
            break;
            case 'f': {
                if (!evm_is_number(e, value)){
                    error_code = CFFI_ARG_TYPE_IS_NOT_DOUBLE;
                    goto failed;
                }
                fargs[i].f = evm_2_double(e, value);
                offset = 100;
            }
            break;
            case 's': {
                if (!evm_is_string(e, value) && !evm_is_undefined(e, value) && !evm_is_null(e, value)){
                    error_code = CFFI_ARG_TYPE_IS_NOT_STRING;
                    goto failed;
                }
                if(evm_is_string(e, value)){
                    fargs[i].w = (uintptr_t)evm_2_string(e, value);
                }else{
                    fargs[i].w = (uintptr_t)NULL;
                }
            } break;
            case 'p': {
                if (!evm_is_object(e, value)){
                    error_code = CFFI_ARG_TYPE_IS_NOT_CPOINTER;
                    goto failed;
                }
                fargs[i].w = (uintptr_t)evm_object_get_user_data(e, value);
            }break;
            default: {
                error_code = CFFI_ARG_TYPE_NOT_SUPPORT;
                goto failed;
            };
        }
    }

    uintptr_t f = (uintptr_t) funcID;
    type = type + offset;
    switch (type) {
         case 0: res.i64 = ((func_p_0)f)(fargs[0].w, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 1: res.d = ((func_p_1)f)(fargs[0].w, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 2: res.i64 = ((func_p_2)f)(fargs[0].d, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 3: res.d = ((func_p_3)f)(fargs[0].d, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 4: res.i64 = ((func_p_4)f)(fargs[0].w, fargs[1].d, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 5: res.d = ((func_p_5)f)(fargs[0].w, fargs[1].d, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 6: res.i64 = ((func_p_6)f)(fargs[0].d, fargs[1].d, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 7: res.d = ((func_p_7)f)(fargs[0].d, fargs[1].d, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b1110: res.i64 = ((func_p_0b1110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b1111: res.d = ((func_p_0b1111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b11110: res.i64 = ((func_p_0b11110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b11111: res.d = ((func_p_0b11111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b111110: res.i64 = ((func_p_0b111110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b111111: res.d = ((func_p_0b111111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 0b1111110: res.i64 = ((func_p_0b1111110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].w, fargs[8].w); break;
         case 0b1111111: res.d = ((func_p_0b1111111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].w, fargs[8].w); break;
         case 0b11111110: res.i64 = ((func_p_0b11111110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].d, fargs[8].w); break;
         case 0b11111111: res.d = ((func_p_0b11111111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].d, fargs[8].w); break;
         case 0b111111110: res.i64 = ((func_p_0b111111110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].d, fargs[8].d); break;
         case 0b111111111: res.d = ((func_p_0b111111111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].d, fargs[8].d); break;
         case 0b1111111110: res.i64 = ((func_p_0b1111111110)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].d, fargs[8].d); break;
         case 0b1111111111: res.d = ((func_p_0b1111111111)f)(fargs[0].d, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].d, fargs[8].d); break;
         case 12: res.i64 = ((func_p_12)f)(fargs[0].w, fargs[1].d, fargs[2].d, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 24: res.i64 = ((func_p_24)f)(fargs[0].w, fargs[1].w, fargs[2].d, fargs[3].d, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 28: res.i64 = ((func_p_28)f)(fargs[0].w, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 60: res.i64 = ((func_p_60)f)(fargs[0].w, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 124: res.i64 = ((func_p_124)f)(fargs[0].w, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 252: res.i64 = ((func_p_252)f)(fargs[0].w, fargs[1].d, fargs[2].d, fargs[3].d, fargs[4].d, fargs[5].d, fargs[6].d, fargs[7].w, fargs[8].w); break;

         case 101: res.f = ((func_f_1)f)(fargs[0].w, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 102: res.i64 = ((func_f_2)f)(fargs[0].f, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 103: res.f = ((func_f_3)f)(fargs[0].f, fargs[1].w, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 104: res.i64 = ((func_f_4)f)(fargs[0].w, fargs[1].f, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 105: res.f = ((func_f_5)f)(fargs[0].w, fargs[1].f, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 106: res.i64 = ((func_f_6)f)(fargs[0].f, fargs[1].f, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 107: res.f = ((func_f_7)f)(fargs[0].f, fargs[1].f, fargs[2].w, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b1110: res.i64 = ((func_f_0b1110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b1111: res.f = ((func_f_0b1111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].w, fargs[4].w, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b11110: res.i64 = ((func_f_0b11110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b11111: res.f = ((func_f_0b11111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].w, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b111110: res.i64 = ((func_f_0b111110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b111111: res.f = ((func_f_0b111111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].w, fargs[7].w, fargs[8].w); break;
         case 100 + 0b1111110: res.i64 = ((func_f_0b1111110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].w, fargs[8].w); break;
         case 100 + 0b1111111: res.f = ((func_f_0b1111111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].w, fargs[8].w); break;
         case 100 + 0b11111110: res.i64 = ((func_f_0b11111110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].f, fargs[8].w); break;
         case 100 + 0b11111111: res.f = ((func_f_0b11111111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].f, fargs[8].w); break;
         case 100 + 0b111111110: res.i64 = ((func_f_0b111111110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].f, fargs[8].f); break;
         case 100 + 0b111111111: res.f = ((func_f_0b111111111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].f, fargs[8].f); break;
         case 100 + 0b1111111110: res.i64 = ((func_f_0b1111111110)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].f, fargs[8].f); break;
         case 100 + 0b1111111111: res.f = ((func_f_0b1111111111)f)(fargs[0].f, fargs[1].f, fargs[2].f, fargs[3].f, fargs[4].f, fargs[5].f, fargs[6].f, fargs[7].f, fargs[8].f); break;
         default:res = fficall(signature, funcID, FFI_ARGS);;
       }

    switch (signature[0]) {
        case 'b': {
            return evm_mk_boolean(e, (int) res.i64);
        }case 'i': {
            return evm_mk_number(e, res.i64);
        }case 'd': {
            return evm_mk_number(e, (double) res.d);
        }case 'f': {
            return evm_mk_number(e, (double) res.f);
        }case 's': {
            if (res.w == 0){
                error_code = CFFI_RETURN_TYPE_CPOINTER_IS_NULL;
                goto failed;
            }
            evm_val_t ret = evm_mk_string(e, (char *)res.w);
            return ret;
        }case 'v': {
            return EVM_UNDEFINED;
        }case 'p': {
            if (res.p == NULL){
                error_code = CFFI_RETURN_TYPE_CPOINTER_IS_NULL;
                goto failed;
            }
            return evm_object_create_user_data(e, (void *)res.p);
        }
        default: {
            error_code = CFFI_RETURN_TYPE_NOT_SUPPORT;
            goto failed;
        }
    }
failed:
    return EVM_UNDEFINED;
}

//invoke(name, arg1, arg2 ....)
static evm_val_t evm_module_cffi_invoke(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    evm_val_t cffi_module = evm_module_get(e, "cffi");
    evm_val_t registry = evm_prop_get(e, cffi_module, "$registry");
    evm_val_t invokable = evm_prop_get(e, registry, evm_2_string(e, v[0]));
    if( evm_is_undefined(e, invokable) ) {
        return EVM_UNDEFINED;
    }
    evm_module_cffi_t *cffi = evm_object_get_user_data(e, invokable);
    return cffi_exec(e, invokable, argc - 2, v + 1, cffi->funcname, cffi->signature, cffi->funcID);
}

void evm_module_cffi_add(evm_t *e, evm_module_cffi_t *cffis) {
    evm_val_t cffi_module = evm_module_get(e, "cffi");
    evm_val_t registry = evm_prop_get(e, cffi_module, "$registry");
    while(cffis->funcname && cffis->signature) {
        evm_val_t cffi_obj = evm_object_create_user_data(e, cffis);
        evm_prop_set(e, registry, cffis->funcname, cffi_obj);
        cffis++;
    }
    evm_val_free(e, cffi_module);
    evm_val_free(e, registry);
}

evm_err_t evm_module_cffi(evm_t *e)
{
    evm_val_t obj = evm_object_create(e);
    evm_val_t registry = evm_object_create(e);
    evm_prop_set(e, obj, "invoke", evm_mk_native(e, evm_module_cffi_invoke, "invoke", 0));
    evm_prop_set(e, obj, "$registry", registry);
    evm_module_add(e, "cffi", obj);
    return ec_ok;
}
#endif
