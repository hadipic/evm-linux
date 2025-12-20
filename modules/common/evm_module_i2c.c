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
#ifdef EVM_USE_MODULE_I2C

#include "evm_module_i2c.h"

IOT_DEFINE_PERIPH_CREATE_FUNCTION(i2c)

static void iot_i2c_destroy(iot_i2c_t* i2c) {
  iot_i2c_destroy_platform_data(i2c->platform_data);
  evm_free(i2c);
}

static void i2c_worker(uv_work_t* work_req) {
  iot_periph_data_t* worker_data =
      (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);
  iot_i2c_t* i2c = (iot_i2c_t*)worker_data->data;

  switch (worker_data->op) {
    case kI2cOpOpen:
      worker_data->result = iot_i2c_open(i2c);
      break;
    case kI2cOpWrite:
      worker_data->result = iot_i2c_write(i2c);
      break;
    case kI2cOpRead:
      worker_data->result = iot_i2c_read(i2c);
      break;
    case kI2cOpClose:
      worker_data->result = iot_i2c_close(i2c);
      break;
    default:
      EVM_ASSERT(!"Invalid Operation");
  }
}

EVM_FUNCTION(i2c_close) {
    EVM_EPCV;
  iot_i2c_t *i2c = evm_object_get_user_data(e, p);

  iot_periph_call_async(i2c, v[0], kI2cOpClose,
                          i2c_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(i2c_close_sync) {
    EVM_EPCV;
  iot_i2c_t *i2c = evm_object_get_user_data(e, p);

  if (!iot_i2c_close(i2c)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kI2cOpClose)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

static evm_val_t i2c_write_helper(evm_t *e, iot_i2c_t* i2c,
                                      const evm_val_t jargv[],
                                      int jargc, bool async) {
  evm_val_t jarray = jargv[0];

  // Set buffer length and data from jarray
  i2c->buf_len = evm_list_len(e, jarray);
  i2c->buf_data = evm_buffer_allocate_from_number_array(e, i2c->buf_len, jarray);

  if (async) {
    iot_periph_call_async(i2c, jargv[1], kI2cOpWrite,
                            i2c_worker);
  } else {
    if (!iot_i2c_write(i2c)) {
      evm_throw(e, evm_mk_string(e, iot_periph_error_str(kI2cOpWrite)));
    }
  }

  EVM_RETURN_VAL(EVM_UNDEFINED);
}

typedef enum { IOT_I2C_WRITE, IOT_I2C_WRITESYNC } iot_i2c_op_t;

static evm_val_t i2c_do_write_or_writesync(evm_t *e,
                                               const evm_val_t jthis,
                                               const evm_val_t jargv[],
                                               const int jargc,
                                               const iot_i2c_op_t i2c_op) {
  iot_i2c_t *i2c = evm_object_get_user_data(e, jthis);
  return i2c_write_helper(e, i2c, jargv, jargc, i2c_op == IOT_I2C_WRITE);
}

EVM_FUNCTION(i2c_write) {
    EVM_EPCV;
  EVM_RETURN(i2c_do_write_or_writesync(e, p, v, argc, IOT_I2C_WRITE));
}

EVM_FUNCTION(i2c_write_sync) {
    EVM_EPCV;
  EVM_RETURN(i2c_do_write_or_writesync(e, p, v, argc,
                                   IOT_I2C_WRITESYNC));
}

EVM_FUNCTION(i2c_read) {
    EVM_EPCV;
  iot_i2c_t *i2c = evm_object_get_user_data(e, p);
  i2c->buf_len = evm_2_integer(e, v[0]);

  iot_periph_call_async(i2c, v[1], kI2cOpRead,
                          i2c_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(i2c_read_sync) {
    EVM_EPCV;
  iot_i2c_t *i2c = evm_object_get_user_data(e, p);

  i2c->buf_len = evm_2_integer(e, v[0]);

  evm_val_t result;
  if (iot_i2c_read(i2c)) {
    result = evm_buffer_create(e, i2c->buf_data, i2c->buf_len);
  } else {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kI2cOpRead)));
  }

  evm_free(i2c->buf_data);

  EVM_RETURN(result);
}

EVM_FUNCTION(i2c_constructor) {
    EVM_EPCV;
  // Create I2C object
  const evm_val_t ji2c = evm_object_create(e);
  iot_i2c_t* i2c = i2c_create(e, ji2c);

  evm_val_t jconfig = v[0];

  iot_i2c_set_platform_config(e, i2c, jconfig);
  i2c->address = evm_2_integer(e, evm_prop_get(e, jconfig, IOT_MAGIC_STRING_ADDRESS));

  evm_val_t jcallback = v[1];

  // If the callback doesn't exist, it is completed synchronously.
  // Otherwise, it will be executed asynchronously.
  if (!evm_is_null(e, jcallback)) {
    iot_periph_call_async(i2c, jcallback, kI2cOpOpen, i2c_worker);
  } else if (!iot_i2c_open(i2c)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kI2cOpOpen)));
  }
  evm_prop_set(e, ji2c, IOT_MAGIC_STRING_CLOSE, evm_mk_native(e, i2c_close, IOT_MAGIC_STRING_CLOSE, 0));
  evm_prop_set(e, ji2c, IOT_MAGIC_STRING_CLOSESYNC, evm_mk_native(e, i2c_close_sync, IOT_MAGIC_STRING_CLOSESYNC, 0));
  evm_prop_set(e, ji2c, IOT_MAGIC_STRING_WRITE, evm_mk_native(e, i2c_write, IOT_MAGIC_STRING_WRITE, 0));
  evm_prop_set(e, ji2c, IOT_MAGIC_STRING_WRITESYNC, evm_mk_native(e, i2c_write_sync, IOT_MAGIC_STRING_WRITESYNC, 0));
  evm_prop_set(e, ji2c, IOT_MAGIC_STRING_READ, evm_mk_native(e, i2c_read, IOT_MAGIC_STRING_READ, 0));
  evm_prop_set(e, ji2c, IOT_MAGIC_STRING_READSYNC, evm_mk_native(e, i2c_read_sync, IOT_MAGIC_STRING_READSYNC, 0));
  EVM_RETURN(ji2c);
}

void evm_module_i2c(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, i2c_constructor, IOT_MAGIC_STRING_CREATE, 0));
    evm_module_add(e, "i2c", obj);
}
#endif
