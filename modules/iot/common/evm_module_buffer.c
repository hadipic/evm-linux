#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_BUFFER

evm_val_t evm_module_buffer_class_instantiate(evm_t *e, int size);

static int hex_2_oct(int h) {
    int re = 0;
    int k = 16;
    int n = 1;
    while (h != 0)
    {
        re += (h % 10) * n;
        h /= 10;
        n *= k;
    }
    return re;
}

//new Buffer(array)
//new Buffer(buffer)
//new Buffer(size)
//new Buffer(str[, encoding])
EVM_FUNCTION(evm_module_buffer_class_new)
{
    EVM_EPCV;
    EVM_UNUSED(p);
    evm_val_t buf_obj;
    int length = 0;

    if (evm_is_integer(e, v[0])) {
        length = evm_2_integer(e, v[0]);
        buf_obj = evm_module_buffer_class_instantiate(e, length);
    } else if (evm_is_list(e, v[0])) {
        length = evm_list_len(e, v[0]);
        buf_obj = evm_module_buffer_class_instantiate(e, length);
        evm_val_t prop;
        uint8_t *buffer = evm_buffer_addr(e, buf_obj);
        uint8_t b;
        for (int i = 0; i < length; i++) {
            prop = evm_list_get(e, v[0], i);
            evm_val_free(e, prop);
            if (evm_is_number(e, prop)) {
                b = (uint8_t)evm_2_integer(e, prop);
                buffer[i] = b;
            }
        }
    } else if (evm_is_buffer(e, v[0])) {
        length = evm_buffer_len(e, v[0]);
        buf_obj = evm_module_buffer_class_instantiate(e, length);
        uint8_t *buffer = evm_buffer_addr(e, buf_obj);
        memcpy(buffer, evm_buffer_addr(e, v[0]), length);
    } else if (evm_is_string(e, v[0])) {
        if (argc > 1 && evm_is_string(e, v [1]) && !strcmp(evm_2_string(e, v[1]), "hex")) {
            length = 0;
            const char *p = evm_2_string(e, v[0]);
            char t[2] = {0};
            while (*p != '\0' && *p) {
                strncpy(t, (const char *)p, 2);
                if (atoi(t))
                    length++;
                p += 2;
            }

            buf_obj = evm_module_buffer_class_instantiate(e, length);
            uint8_t *buffer = evm_buffer_addr(e, buf_obj);
            char n;
            p = evm_2_string(e, v[0]);
            uint32_t cnt = 0;
            while (*p != '\0' && *p) {
                strncpy(t, (const char *)p, 2);
                n = (char)hex_2_oct(atoi(t));
                buffer[cnt] = n;
                p += 2;
                cnt++;
            }
        } else {
            length = evm_string_len(e, v[0]);
            buf_obj = evm_module_buffer_class_instantiate(e, length);
            memcpy(evm_buffer_addr(e, buf_obj), evm_2_string(e, v[0]), length);
        }
    }
    EVM_RETURN(buf_obj);
}

//Buffer.byteLength(str, encoding)
//encoding: hex | bytes(default)
EVM_FUNCTION(evm_module_buffer_byteLength)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    EVM_UNUSED(p);
    EVM_UNUSED(argc);
    EVM_UNUSED(v);
    EVM_RETURN(evm_mk_number(e, evm_string_len(e, v[0])));
}

//Buffer.concat(list)
EVM_FUNCTION(evm_module_buffer_concat)
{
    EVM_EPCV;
    EVM_UNUSED(p);
    if (argc < 1 || !evm_is_list(e, v[0]))
        EVM_RETURN(EVM_UNDEFINED);

    int len = evm_list_len(e, v[0]);
    int length = 0;
    int buffer_length = 0;
    evm_val_t prop;
    for (int i = 0; i < len; i++) {
        prop = evm_list_get(e, v[0], i);
        evm_val_free(e, prop);
        if (evm_is_buffer(e, prop)) {
            buffer_length += evm_buffer_len(e, prop);
            length++;
        }
    }

    evm_val_t buf = evm_module_buffer_class_instantiate(e, buffer_length);
    int i = 0, cnt = 0;
    while (i < length) {
        prop = evm_list_get(e, v[0], i);
        evm_val_free(e, prop);
        memcpy(evm_buffer_addr(e, buf) + cnt, evm_buffer_addr(e, prop), evm_buffer_len(e, prop));
        cnt += evm_buffer_len(e, prop);
        i++;
    }

    EVM_RETURN(buf);
}

//Buffer.from(array)
//Buffer.from(buffer)
//Buffer.from(string[,encoding])
//Buffer.from(arrayBuffer[, byteOffset[, length]])
EVM_FUNCTION(evm_module_buffer_from)
{
    EVM_EPCV;
    EVM_RETURN( evm_module_buffer_class_new(EVM_ARGS));
}

//Buffer.isBuffer(buffer)
EVM_FUNCTION(evm_module_buffer_isBuffer)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    EVM_UNUSED(p);
    if (argc < 1)
        EVM_RETURN( EVM_UNDEFINED);

    if (evm_is_buffer(e, v[0]))
        EVM_RETURN( evm_mk_boolean(e, 1));

    EVM_RETURN( evm_mk_boolean(e, 0));
}

//buf.length
EVM_FUNCTION(evm_module_buffer_class_get_length)
{
    EVM_EPCV;
    EVM_UNUSED(e);EVM_UNUSED(p);EVM_UNUSED(argc);
    EVM_RETURN( evm_mk_number(e, evm_buffer_len(e, v[0])));
}

//buf.compare(otherBuffer)
EVM_FUNCTION(evm_module_buffer_class_compare)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    if (argc < 1 || !evm_is_buffer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED);

    int p_len = evm_buffer_len(e, p);
    int v_len = evm_buffer_len(e, v[0]);
    // return -1 if first lower than second
    // return 1 if second lower than first
    // return 0 if first equal second
    uint8_t *p_addr = evm_buffer_addr(e, p);
    uint8_t *v_addr = evm_buffer_addr(e, v[0]);
    if (p_len == v_len) {
        for(int i = 0; i < p_len; i++) {
            if (p_addr[i] < v_addr[i]) {EVM_RETURN( evm_mk_number(e, -1));}
            else if (p_addr[i] > v_addr[i]) {EVM_RETURN( evm_mk_number(e, 1));}
        }
        EVM_RETURN( evm_mk_number(e, 0));
    } else if (p_len < v_len) { // length different
        EVM_RETURN( evm_mk_number(e, -1)); // return 1 if first less than second
    } else { // p_len > v_len
        EVM_RETURN( evm_mk_number(e, 1)); // return -1 if first rather than second
    }
    EVM_RETURN( EVM_UNDEFINED);
}

//buf.copy(targetBuffer[, targetStart[, sourceStart[, sourceEnd]]])
EVM_FUNCTION(evm_module_buffer_class_copy)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    if (argc < 1 || !evm_is_buffer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED);

    uint8_t *source = evm_buffer_addr(e, p);
    uint8_t *target = evm_buffer_addr(e, v[0]);
    int target_length = evm_buffer_len(e, v[0]);
    int source_start = 0;
    int source_end = evm_buffer_len(e, p);

    int target_start = 0;
    if (argc >= 1 && evm_is_integer(e, v[1]))
        target_start = evm_2_integer(e, v[1]);
    if (argc >= 2 && evm_is_integer(e, v[2]))
        source_start = evm_2_integer(e, v[2]);
    if (argc >= 3 && evm_is_integer(e, v[3]))
        source_end = evm_2_integer(e, v[3]);

    if (source_start > source_end)
        EVM_RETURN( EVM_UNDEFINED);

    for(int i = target_start; i < target_length; i++) {
        if (source_start + i < source_end)
            memcpy(target + target_start + i, source + source_start + i, 1);
    }
    EVM_RETURN( evm_mk_number(e, source_end - source_start))
}

//buf.equals(otherBuffer)
EVM_FUNCTION(evm_module_buffer_class_equals)
{
    EVM_EPCV;
    if (argc < 1 || !evm_is_buffer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED);

    evm_val_t result = evm_module_buffer_class_compare(EVM_ARGS);
    EVM_RETURN( evm_2_boolean(e, result) == 0 ? evm_mk_boolean(e, 1) : evm_mk_boolean(e, 0));
}

//buf.fill(value)
EVM_FUNCTION(evm_module_buffer_class_fill)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    if (argc < 1 || !evm_is_integer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED);

    int value = evm_2_integer(e, v[0]);
    uint8_t *buffer = evm_buffer_addr(e, p);
    EVM_ASSERT(buffer);

    int length = evm_buffer_len(e, p);
    for(int i = 0; i < length; i++) {
        buffer[i] = value;
    }
    EVM_RETURN( p)
}

//buf.slice([start[, end]])
EVM_FUNCTION(evm_module_buffer_class_slice)
{
    EVM_EPCV;
    // 根据开始下标和结束下标获取某一段buffer
    int start = 0;
    int end = evm_buffer_len(e, p);
    if (argc >= 1 && evm_is_integer(e, v[0])) {
        start = evm_2_integer(e, v[0]);
    }
    if (argc >= 2 && evm_is_integer(e, v[1])) {
        end = evm_2_integer(e, v[1]);
    }
    if (start > end)
        EVM_RETURN( EVM_UNDEFINED)

    int length = end - start;

    evm_val_t buf = evm_module_buffer_class_instantiate(e, length);
    char *b = (char *)evm_buffer_addr(e, p);
    int cnt = 0;
    for(int i = start; i < end; i++) {
        memcpy(evm_buffer_addr(e, buf) + cnt, (uint8_t *)(b + i), 1);
        cnt++;
    }

    EVM_RETURN( buf)
}

//buf.toString([start[, end]])
EVM_FUNCTION(evm_module_buffer_class_toString)
{
    EVM_EPCV;
    int start = 0;
    int end = evm_buffer_len(e, p);

    if (argc > 0 && evm_is_integer(e, v[0]))
        start = evm_2_integer(e, v[0]);

    if (argc > 1 && evm_is_integer(e, v[1]))
        end = evm_2_integer(e, v[1]);

    if (start > end)
        EVM_RETURN( EVM_UNDEFINED)

    evm_val_t result = evm_mk_lstring(e, (char*)evm_buffer_addr(e, p) + start, end - start);
    EVM_RETURN( result)
}

//buf.write(string[, offset[, length]])
EVM_FUNCTION(evm_module_buffer_class_write)
{
    EVM_EPCV;
    if (argc < 1 || !evm_is_string(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED)

    int offset = 0;
    int length = evm_string_len(e, v[0]);

    if (argc > 1 && evm_is_integer(e, v[1]))
        offset = evm_2_integer(e, v[1]);

    if (argc > 2 && evm_is_integer(e, v[2]))
        length = evm_2_integer(e, v[2]);

    memcpy(evm_buffer_addr(e, p) + offset, (void *)evm_2_string(e, v[0]), length);
    EVM_RETURN( evm_mk_number(e, length))
}

//buf.writeUInt8(value, offset[, noAssert])
EVM_FUNCTION(evm_module_buffer_class_writeUInt8)
{
    EVM_EPCV;
    if (argc < 1 || !evm_is_integer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED)

    int offset = 0;
    if (argc > 1 && evm_is_integer(e, v[1])) {
        offset = evm_2_integer(e, v[1]);
    }

    if (offset > evm_buffer_len(e, p)) {
        evm_throw(e, evm_mk_string(e, "buffer subscript index overflow"));
    }

    int value = evm_2_integer(e, v[0]);
    if (value < 0 || value > 255) {
        evm_throw(e, evm_mk_string(e, "value must between 0 and 255"));
    }

    uint8_t *buf = evm_buffer_addr(e, p);

    buf[offset] = evm_2_integer(e, v[0]);
    EVM_RETURN( evm_mk_number(e, offset + 1))
}

//buf.writeUInt16LE(value, offset[, noAssert])
EVM_FUNCTION(evm_module_buffer_class_writeUInt16LE)
{
    EVM_EPCV;
    if (argc < 1 || !evm_is_integer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED)

    int offset = 0;
    if (argc > 1 && evm_is_integer(e, v[1]))
        offset = evm_2_integer(e, v[1]);

    if (offset + 2 > evm_buffer_len(e, p)) {
        evm_throw(e, evm_mk_string(e, "buffer subscript index overflow"));
    }

    uint8_t *buf = evm_buffer_addr(e, p);
    int value = evm_2_integer(e, v[0]);
    memcpy(buf + offset, &value, sizeof(uint16_t));
    EVM_RETURN( evm_mk_number(e, offset + 1))
}

//buf.writeUInt32LE(value, offset[, noAssert])
EVM_FUNCTION(evm_module_buffer_class_writeUInt32LE)
{
    EVM_EPCV;
    if (argc < 1 || !evm_is_integer(e, v[0]))
        EVM_RETURN( EVM_UNDEFINED)

    int offset = 0;
    if (argc > 1 && evm_is_integer(e, v[1]))
        offset = evm_2_integer(e, v[1]);

    if (offset + 4 > evm_buffer_len(e, p)) {
        evm_throw(e, evm_mk_string(e, "buffer subscript index overflow"));
    }

    uint8_t *buf = evm_buffer_addr(e, p);
    uint32_t value = (uint32_t)evm_2_integer(e, v[0]);
    memcpy(buf + offset, &value, sizeof(uint32_t));
    EVM_RETURN( evm_mk_number(e, offset + 1))
}

//buf.readInt8(offset[, noAssert])
EVM_FUNCTION(evm_module_buffer_class_readInt8)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    int offset = 0;
    if (argc > 0 && evm_is_integer(e, v[0]))
        offset = evm_2_integer(e, v[0]);

    uint8_t *buf = evm_buffer_addr(e, p);
    int8_t value = (int8_t)buf[offset];

    EVM_RETURN( evm_mk_number(e, value))
}

//buf.readUInt8(offset[, noAssert])
EVM_FUNCTION(evm_module_buffer_class_readUInt8)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    int offset = 0;
    if (argc > 0 && evm_is_integer(e, v[0]))
        offset = evm_2_integer(e, v[0]);

    uint8_t *buf = evm_buffer_addr(e, p);
    uint8_t value = (uint8_t)buf[offset];

    EVM_RETURN( evm_mk_number(e, value))
}

//buf.readUInt16LE(offset[, noAssert])
EVM_FUNCTION(evm_module_buffer_class_readUInt16LE)
{
    EVM_EPCV;
    EVM_UNUSED(e);
    int offset = 0;
    if (argc > 0 && evm_is_integer(e, v[0]))
        offset = evm_2_integer(e, v[0]);

    uint8_t *buf = evm_buffer_addr(e, p);
    uint16_t value = 0;
    memcpy(&value, buf, sizeof(uint16_t));

    EVM_RETURN( evm_mk_number(e, value))
}

EVM_FUNCTION(evm_module_buffer_alloc)
{
    EVM_EPCV;
    EVM_RETURN( evm_module_buffer_class_instantiate(e, evm_2_integer(e, v[0])))
}

evm_val_t evm_module_buffer_class_instantiate(evm_t *e, int size)
{
    uint8_t *buf = malloc(size);
    EVM_ASSERT(buf);
    evm_val_t obj = evm_buffer_create(e, buf, size);
    free(buf);
    evm_prop_set(e, obj, "length", evm_mk_number(e, size));
    evm_prop_set(e, obj, "compare", evm_mk_native(e, evm_module_buffer_class_compare, "compare", 1));
    evm_prop_set(e, obj, "copy", evm_mk_native(e, evm_module_buffer_class_copy, "copy", 1));
    evm_prop_set(e, obj, "equals", evm_mk_native(e, evm_module_buffer_class_equals, "equals", 1));
    evm_prop_set(e, obj, "fill", evm_mk_native(e, evm_module_buffer_class_fill, "fill", 1));
    evm_prop_set(e, obj, "slice", evm_mk_native(e, evm_module_buffer_class_slice, "slice", 1));
    evm_prop_set(e, obj, "toString", evm_mk_native(e, evm_module_buffer_class_toString, "toString", 1));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_buffer_class_write, "write", 1));
    evm_prop_set(e, obj, "writeUInt8", evm_mk_native(e, evm_module_buffer_class_writeUInt8, "writeUInt8", 1));
    evm_prop_set(e, obj, "writeUInt16LE", evm_mk_native(e, evm_module_buffer_class_writeUInt16LE, "writeUInt16LE", 1));
    evm_prop_set(e, obj, "writeUInt32LE", evm_mk_native(e, evm_module_buffer_class_writeUInt32LE, "writeUInt32LE", 1));
    evm_prop_set(e, obj, "readInt8", evm_mk_native(e, evm_module_buffer_class_readInt8, "readInt8", 1));
    evm_prop_set(e, obj, "readUInt8", evm_mk_native(e, evm_module_buffer_class_readUInt8, "readUInt8", 1));
    evm_prop_set(e, obj, "readUInt16LE", evm_mk_native(e, evm_module_buffer_class_readUInt16LE, "readUInt16LE", 1));
    return obj;
}

evm_err_t evm_module_buffer(evm_t *e)
{
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "alloc", evm_mk_native(e, evm_module_buffer_alloc, "readUInt16LE", 1));
    evm_prop_set(e, obj, "byteLength", evm_mk_native(e, evm_module_buffer_byteLength, "byteLength", 1));
    evm_prop_set(e, obj, "concat", evm_mk_native(e, evm_module_buffer_concat, "concat", 1));
    evm_prop_set(e, obj, "from", evm_mk_native(e, evm_module_buffer_from, "from", 1));
    evm_prop_set(e, obj, "isBuffer", evm_mk_native(e, evm_module_buffer_isBuffer, "isBuffer", 1));
    evm_module_add(e, "buffer", obj);
    return ec_ok;
}
#endif
