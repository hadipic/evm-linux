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
