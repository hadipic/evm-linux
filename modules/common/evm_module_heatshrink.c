/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifdef EVM_USE_MODULE_HEATSHRINK

#include "evm_module.h"
#include "compress_heatshrink.h"

EVM_FUNCTION(compress){
    EVM_EPCV;
    if( argc > 0 ){
        uint8_t *in_it;
        uint32_t in_len, out_len;
        if( evm_is_buffer(e, v[0]) ) {
            in_it = evm_buffer_addr(e, v[0]);
            in_len = evm_buffer_len(e, v[0]);
        } else if( evm_is_string(e, v[0]) ) {
            in_it = evm_2_string(e, v[0]);
            in_len = evm_string_len(e, v[0]);
        }

        uint32_t compressedSize = heatshrink_encode_cb(heatshrink_var_input_cb, (uint32_t*)in_it, in_len, NULL, NULL, 0);
        if( evm_is_string(e, v[0]) ){
            evm_string_free(e, in_it);
        }

        uint8_t *out_it = evm_malloc(compressedSize);
        out_len = compressedSize;
        heatshrink_encode_cb(heatshrink_var_input_cb, (uint32_t*)in_it, in_len, heatshrink_var_output_cb, (uint32_t*)out_it, out_len);
        evm_val_t outVar = evm_buffer_create(e, out_it, out_len);
        evm_free(out_it);
        return outVar;
    }
    EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(decompress){
    EVM_EPCV;
    if( argc > 0 ){
        uint8_t * in_it;
        uint32_t in_len, out_len;
        if( evm_is_buffer(e, v[0]) ) {
            in_it = evm_buffer_addr(e, v[0]);
            in_len = evm_buffer_len(e, v[0]);
        } else if( evm_is_string(e, v[0]) ) {
            in_it = evm_2_string(e, v[0]);
            in_len = strlen(in_it);
        }

        uint32_t decompressedSize = heatshrink_decode(heatshrink_var_input_cb, (uint32_t*)in_it, in_len, NULL, 0);
        if( evm_is_string(e, v[0]) ){
            evm_string_free(e, in_it);
        }

        uint8_t *out_it = evm_malloc(decompressedSize);
        out_len = decompressedSize;
        heatshrink_decode_cb(heatshrink_var_input_cb, (uint32_t*)in_it, in_len, heatshrink_var_output_cb, (uint32_t*)out_it, out_len);

        evm_val_t outVar = evm_buffer_create(e, out_it, out_len);
        evm_free(out_it);
        return outVar;
    }
    EVM_RETURN(EVM_UNDEFINED);
}

void evm_module_heatshrink(evm_t *e){
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "compress", evm_mk_native(e, compress, "compress", EVM_VARARGS));
    evm_prop_set(e, obj, "decompress", evm_mk_native(e, decompress, "decompress", EVM_VARARGS));
    evm_module_add(e, "@native.heatshrink", obj);
    evm_val_free(e, obj);
}
#endif
