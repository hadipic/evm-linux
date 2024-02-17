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
#ifdef EVM_USE_MODULE_BASE64

#include "evm_module.h"

static const char CHARACTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char INALPHABET[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const char BASE64DECODER[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3f,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
    0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24,
    0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,
    0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

int we_base64_enclen(int len) { return (((len + 3) / 3) * 4) + 1; }

int we_base64_declen(int len) { return (((len + 3) / 4) * 3) + 1; }

int we_base64_encode(char *base64, const void *data, int length) {
  char *p = base64;
  const unsigned char *d = (const unsigned char *)data;
  unsigned char in[3];
  int i, j, len;

  for (i = 0; i < length;) {
    len = 0;

    for (j = 0; j < 3; ++j) {
      in[j] = 0;

      if (i < length) {
        in[j] = d[i];
        len += 1;
      }
      i += 1;
    }

    if (len) {
      *p++ = CHARACTERS[in[0] >> 2];
      *p++ = CHARACTERS[((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)];
      *p++ = (unsigned char)((len > 1) ? CHARACTERS[((in[1] & 0x0f) << 2) |
                                                    ((in[2] & 0xc0) >> 6)]
                                       : '=');
      *p++ = (unsigned char)((len > 2) ? CHARACTERS[in[2] & 0x3f] : '=');
    }
  }

  return (int)(p - base64);
}

int we_base64_decode(void *buffer, const char *base64, int length) {
  unsigned char *p = (unsigned char *)buffer;
  int i, c = 0, bits = 0, char_count = 0;

  for (i = 0; i < length; ++i) {
    c = base64[i];

    if ('=' == c) {
      switch (char_count) {
      case 1:
        /* base64 encoding incomplete: at least 2 bits missing */
        break;

      case 2:
        *p++ = bits >> 10;
        break;

      case 3:
        *p++ = bits >> 16;
        *p++ = (bits >> 8) & 0xff;
        break;
      }

      break; /* break for */
    }

    if ((c < 255) && INALPHABET[c]) {
      bits += BASE64DECODER[c];
      char_count += 1;

      if (4 == char_count) {
        *p++ = bits >> 16;
        *p++ = (bits >> 8) & 0xff;
        *p++ = bits & 0xff;

        bits = 0;
        char_count = 0;
      } else
        bits <<= 6;
    }
  }

  return (int)(p - (unsigned char *)buffer);
}

EVM_FUNCTION(encode) {
    EVM_EPCV;
    if( argc == 0 || ( !evm_is_buffer(e, v[0]) && !evm_is_string(e, v[0]) ) )  {
        EVM_RETURN(EVM_UNDEFINED);
    }

    char *addr;
    uint32_t len;
    if( evm_is_string(e, v[0]) ) {
        addr = evm_2_string(e, v[0]);
        len = evm_string_len(e, v[0]);
    } else {
        addr = evm_buffer_addr(e, v[0]);
        len = evm_buffer_len(e, v[0]);
    }

    int enc_len = we_base64_enclen(len);
    char *str = evm_malloc(enc_len);
    we_base64_encode(str, addr, len);
    evm_val_t ret = evm_mk_lstring(e, str, enc_len);
    if( evm_is_string(e, v[0]) ) {
        evm_string_free(e, addr);
    }
    evm_free(str);
    return ret;
}

EVM_FUNCTION(decode) {
    EVM_EPCV;
    if( argc == 0 || ( !evm_is_buffer(e, v[0]) && !evm_is_string(e, v[0]) ) )  {
        EVM_RETURN(EVM_UNDEFINED);
    }
    char *addr;
    uint32_t len;
    if( evm_is_string(e, v[0]) ) {
        addr = evm_2_string(e, v[0]);
        len = evm_string_len(e, v[0]);
    } else {
        addr = evm_buffer_addr(e, v[0]);
        len = evm_buffer_len(e, v[0]);
    }

    int declen = we_base64_declen(len);
    uint8_t *buf = evm_malloc(declen);
    we_base64_decode(buf, addr, len);
    evm_val_t ret = evm_buffer_create(e, buf, declen);
    if( evm_is_string(e, v[0]) ) {
        evm_string_free(e, addr);
    }
    evm_free(buf);
    return ret;
}

void evm_module_base64(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "decode", evm_mk_native(e, decode, "decode", EVM_VARARGS));
    evm_prop_set(e, obj, "encode", evm_mk_native(e, encode, "encode", EVM_VARARGS));
    evm_module_add(e, "@native.base64", obj);
    evm_val_free(e, obj);
}
#endif
