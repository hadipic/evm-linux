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

#include "evm.h"
#include "compress_heatshrink.h"
#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"

#define BUFFERSIZE 128

void heatshrink_ptr_output_cb(unsigned char ch, uint32_t *cbdata, uint32_t * count, uint32_t len) {
  unsigned char **outPtr = (unsigned char**)cbdata;
  *((*outPtr)++) = ch;
}
int heatshrink_ptr_input_cb(uint32_t *cbdata, uint32_t * count, uint32_t len) {
  HeatShrinkPtrInputCallbackInfo *info = (HeatShrinkPtrInputCallbackInfo *)cbdata;
  if (!info->len) return -1;
  info->len--;
  return *(info->ptr++);
}

void heatshrink_var_output_cb(unsigned char ch, uint32_t *cbdata, uint32_t * count, uint32_t len) {
  uint8_t * data = (uint8_t*)cbdata;
  if( *count >= len ) return;
  data[*count] = ch;
  *count += 1;
}

int heatshrink_var_input_cb(uint32_t *cbdata, uint32_t * count, uint32_t len) {
  uint8_t * data = (uint8_t*)cbdata;
  int d = -1;
  if( *count >= len ) return d;
  d = data[*count] & 0xFF;
  *count += 1;
  return d;
}

/** gets data from callback, writes to callback if nonzero. Returns total length. */
uint32_t heatshrink_encode_cb(int (*in_callback)(uint32_t *cbdata, uint32_t * cbcount, uint32_t len), uint32_t *in_cbdata, uint32_t in_len, void (*out_callback)(unsigned char ch, uint32_t *cbdata, uint32_t * count, uint32_t len), uint32_t *out_cbdata, uint32_t out_len) {
  heatshrink_encoder hse;
  uint8_t inBuf[BUFFERSIZE];
  uint8_t outBuf[BUFFERSIZE];
  heatshrink_encoder_reset(&hse);

  size_t i;
  size_t count = 0;
  size_t sunk = 0;
  size_t polled = 0;
  int lastByte = 0;
  size_t inBufCount = 0;
  size_t inBufOffset = 0;
  uint32_t bufCount = 0;
  while (lastByte >= 0 || inBufCount>0) {
    // Read data from input
    if (inBufCount==0) {
      inBufOffset = 0;
      while (inBufCount<BUFFERSIZE && lastByte>=0) {
        lastByte = in_callback(in_cbdata, &bufCount, in_len);
        if (lastByte >= 0)
          inBuf[inBufCount++] = (uint8_t)lastByte;
      }
    }
    // encode
    uint8_t ok = heatshrink_encoder_sink(&hse, &inBuf[inBufOffset], inBufCount, &count) >= 0;
    EVM_ASSERT(ok);EVM_UNUSED(ok);
    inBufCount -= count;
    inBufOffset += count;
    sunk += count;
    if ((inBufCount==0) && (lastByte < 0)) {
      heatshrink_encoder_finish(&hse);
    }

    HSE_poll_res pres;
    bufCount = 0;
    do {
      pres = heatshrink_encoder_poll(&hse, outBuf, sizeof(outBuf), &count);
      EVM_ASSERT(pres >= 0);
      if (out_callback)
        for (i=0;i<count;i++)
          out_callback(outBuf[i], out_cbdata, &bufCount, out_len);
      polled += count;
    } while (pres == HSER_POLL_MORE);
    EVM_ASSERT(pres == HSER_POLL_EMPTY);
    if ((inBufCount==0) && (lastByte < 0)) {
      heatshrink_encoder_finish(&hse);
    }
  }
  return (uint32_t)polled;
}

/** gets data from callback, writes it into callback if nonzero. Returns total length */
uint32_t heatshrink_decode_cb(int (*in_callback)(uint32_t *cbdata, uint32_t * count, uint32_t len), uint32_t *in_cbdata, uint32_t in_len, void (*out_callback)(unsigned char ch, uint32_t *cbdata, uint32_t * count, uint32_t len), uint32_t *out_cbdata, uint32_t out_len) {
  heatshrink_decoder hsd;
  uint8_t inBuf[BUFFERSIZE];
  uint8_t outBuf[BUFFERSIZE];
  heatshrink_decoder_reset(&hsd);

  size_t i;
  size_t count = 0;
  size_t sunk = 0;
  size_t polled = 0;
  int lastByte = 0;
  size_t inBufCount = 0;
  size_t inBufOffset = 0;
  uint32_t bufCount = 0;
  while (lastByte >= 0 || inBufCount>0) {
    // Read data from input
    if (inBufCount==0) {
      inBufOffset = 0;
      while (inBufCount<BUFFERSIZE && lastByte>=0) {
        lastByte = in_callback(in_cbdata, &bufCount, in_len);
        if (lastByte >= 0)
          inBuf[inBufCount++] = (uint8_t)lastByte;
      }
    }
    // decode
    uint8_t ok = heatshrink_decoder_sink(&hsd, &inBuf[inBufOffset], inBufCount, &count) >= 0;
    EVM_ASSERT(ok);EVM_UNUSED(ok);
    inBufCount -= count;
    inBufOffset += count;
    sunk += count;
    if ((inBufCount==0) && (lastByte < 0)) {
      heatshrink_decoder_finish(&hsd);
    }

    HSE_poll_res pres;
    bufCount = 0;
    do {
      pres = heatshrink_decoder_poll(&hsd, outBuf, sizeof(outBuf), &count);
      EVM_ASSERT(pres >= 0);
      if (out_callback)
        for (i=0;i<count;i++)
          out_callback(outBuf[i], out_cbdata, &bufCount, out_len);
      polled += count;
    } while (pres == HSER_POLL_MORE);
    EVM_ASSERT(pres == HSER_POLL_EMPTY);
    if (lastByte < 0) {
      heatshrink_decoder_finish(&hsd);
    }
  }
  return (uint32_t)polled;
}



/** gets data from array, writes to callback if nonzero. Returns total length. */
uint32_t heatshrink_encode(unsigned char *in_data, size_t in_len, void (*out_callback)(unsigned char ch, uint32_t *cbdata, uint32_t * count, uint32_t len), uint32_t *out_cbdata, uint32_t out_len) {
  HeatShrinkPtrInputCallbackInfo cbi;
  cbi.ptr = in_data;
  cbi.len = in_len;
  return heatshrink_encode_cb(heatshrink_ptr_input_cb, (uint32_t*)&cbi,in_len, out_callback, out_cbdata, out_len);
}

/** gets data from callback, writes it into array if nonzero. Returns total length */
uint32_t heatshrink_decode(int (*in_callback)(uint32_t *cbdata, uint32_t * count, uint32_t len), uint32_t *in_cbdata, uint32_t in_len, unsigned char *out_data, uint32_t out_len) {
  unsigned char *dataptr = out_data;
  return heatshrink_decode_cb(in_callback, in_cbdata, in_len, out_data?heatshrink_ptr_output_cb:NULL, out_data?(uint32_t*)&dataptr:NULL, out_len);
}

