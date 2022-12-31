#ifdef CONFIG_EVM_MODULE_GPIO

#include "evm_module_gpio.h"

IOT_DEFINE_PERIPH_CREATE_FUNCTION(gpio)

static void iot_gpio_destroy(iot_gpio_t* gpio) {
  iot_gpio_destroy_platform_data(gpio->platform_data);
  evm_free(gpio);
}

static void gpio_worker(uv_work_t* work_req) {
  iot_periph_data_t* worker_data =
      (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);
  iot_gpio_t* gpio = (iot_gpio_t*)worker_data->data;

  switch (worker_data->op) {
    case kGpioOpOpen:
      worker_data->result = iot_gpio_open(gpio);
      break;
    case kGpioOpWrite:
      worker_data->result = iot_gpio_write(gpio);
      break;
    case kGpioOpRead:
      worker_data->result = iot_gpio_read(gpio);
      break;
    case kGpioOpClose:
      worker_data->result = iot_gpio_close(gpio);
      break;
    default:
      EVM_ASSERT(!"Invalid Operation");
  }
}

static evm_val_t gpio_set_configuration(iot_gpio_t* gpio,
                                            evm_val_t jconfigurable) {
  evm_t *e = evm_runtime();
  evm_val_t jpin = evm_prop_get(e, jconfigurable, IOT_MAGIC_STRING_PIN);

  double pin = -1.0;
  if (!evm_is_number(e, jpin) || (pin = evm_2_integer(e, jpin)) < 0) {
    evm_val_free(e, jpin);
    evm_throw(e, evm_mk_string(e, "Bad arguments gpio.pin should be a number"));
  }
  gpio->pin = (uint32_t)pin;
  evm_val_free(e, jpin);

  // Direction
  evm_val_t jdirection =
      evm_prop_get(e, jconfigurable, IOT_MAGIC_STRING_DIRECTION);

  if (evm_is_undefined(e, jdirection)) {
    gpio->direction = kGpioDirectionOut;
  } else {
    if (evm_is_number(e, jdirection)) {
      gpio->direction = (GpioDirection)evm_2_integer(e, jdirection);
    } else {
      gpio->direction = __kGpioDirectionMax;
    }
    if (gpio->direction >= __kGpioDirectionMax) {
      evm_val_free(e, jdirection);
      evm_throw(e, evm_mk_string(e, "Bad arguments - gpio.direction should be DIRECTION.IN or OUT"));
    }
  }
  evm_val_free(e, jdirection);

  // Mode
  evm_val_t jmode =
      evm_prop_get(e, jconfigurable, IOT_MAGIC_STRING_MODE);

  if (evm_is_undefined(e, jmode)) {
    gpio->mode = kGpioModeNone;
  } else {
    if (evm_is_number(e, jmode)) {
      gpio->mode = (GpioMode)evm_2_integer(e, jmode);
    } else {
      gpio->mode = __kGpioModeMax;
    }
    if (gpio->mode >= __kGpioModeMax) {
      evm_throw(e, evm_mk_string(e,
                             "Bad arguments - gpio.mode should be MODE.NONE, "
                             "PULLUP, PULLDOWN, FLOAT, PUSHPULL or OPENDRAIN"));

    } else if (gpio->direction == kGpioDirectionIn &&
               gpio->mode != kGpioModeNone && gpio->mode != kGpioModePullup &&
               gpio->mode != kGpioModePulldown) {
      evm_throw(e, evm_mk_string(e,
                             "Bad arguments - DIRECTION.IN only supports "
                             "MODE.NONE, PULLUP and PULLDOWN"));

    } else if (gpio->direction == kGpioDirectionOut &&
               gpio->mode != kGpioModeNone && gpio->mode != kGpioModeFloat &&
               gpio->mode != kGpioModePushpull &&
               gpio->mode != kGpioModeOpendrain) {
      evm_throw(e, evm_mk_string(e,
                             "Bad arguments - DIRECTION.OUT only supports "
                             "MODE.NONE, FLOAT, PUSHPULL and OPENDRAIN"));
    }
  }
  evm_val_free(e, jmode);

  // Edge
  evm_val_t jedge =
      evm_prop_get(e, jconfigurable, IOT_MAGIC_STRING_EDGE);

  if (evm_is_undefined(e, jedge)) {
    gpio->edge = kGpioEdgeNone;
  } else {
    if (evm_is_number(e, jedge)) {
      gpio->edge = (GpioEdge)evm_2_integer(e, jedge);
    } else {
      gpio->edge = __kGpioEdgeMax;
    }
    if (gpio->edge >= __kGpioEdgeMax) {
      evm_val_free(e, jedge);
      evm_throw(e, evm_mk_string(e,
                             "Bad arguments - gpio.edge should be EDGE.NONE, "
                             "RISING, FALLING or BOTH"));
    }
  }
  evm_val_free(e, jedge);

  return EVM_UNDEFINED;
}

EVM_FUNCTION(gpio_close) {
    EVM_EPCV;
  iot_gpio_t *gpio = evm_object_get_user_data(e, p);

  iot_periph_call_async(gpio, v[0], kGpioOpClose,
                          gpio_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(gpio_close_sync) {
    EVM_EPCV;
  iot_gpio_t *gpio = evm_object_get_user_data(e, p);

  if (!iot_gpio_close(gpio)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kGpioOpClose)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

typedef enum { IOT_GPIO_WRITE, IOT_GPIO_WRITESYNC } iot_gpio_op_t;

evm_val_t gpio_do_write_or_writesync(evm_t*e, const evm_val_t jthis,
                                         const evm_val_t jargv[],
                                         int jargc,
                                         const iot_gpio_op_t gpio_op) {
  iot_gpio_t *gpio = evm_object_get_user_data(e, jthis);

  bool value;
  if (evm_is_number(e, jargv[0])) {
    value = (bool)evm_2_integer(e, jargv[0]);
  } else if (evm_is_boolean(e, jargv[0])) {
    value = evm_2_boolean(e, jargv[0]);
  } else {
    const evm_val_t jcallback = jargv[1];
    if (gpio_op == IOT_GPIO_WRITE && !evm_is_null(e, jcallback)) {
      const char* error_msg = iot_periph_error_str(kGpioOpWrite);
      evm_val_t error_str = evm_mk_string(e, error_msg);
      evm_call_free(e, jcallback, jthis, 1, &error_str);
      evm_val_free(e, error_str);
      return EVM_UNDEFINED;
    }

    evm_throw(e, evm_mk_string(e, "GPIO WriteSync Error - Wrong argument type"));
  }

  gpio->value = value;
  if (gpio_op == IOT_GPIO_WRITE) {
    iot_periph_call_async(gpio, jargv[1],
                            kGpioOpWrite, gpio_worker);
  } else {
    if (!iot_gpio_write(gpio)) {
      evm_throw(e, evm_mk_string(e, iot_periph_error_str(kGpioOpWrite)));
    }
  }

  return EVM_UNDEFINED;
}

EVM_FUNCTION(gpio_write) {
    EVM_EPCV;
  EVM_RETURN(gpio_do_write_or_writesync(e, p, v, argc,
                                    IOT_GPIO_WRITE));
}

EVM_FUNCTION(gpio_write_sync) {
    EVM_EPCV;
  EVM_RETURN(gpio_do_write_or_writesync(e, p, v, argc,
                                    IOT_GPIO_WRITESYNC));
}

EVM_FUNCTION(gpio_read) {
    EVM_EPCV;
  iot_gpio_t *gpio = evm_object_get_user_data(e, p);

  iot_periph_call_async(gpio, v[0], kGpioOpRead,
                          gpio_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(gpio_read_sync) {
    EVM_EPCV;
  iot_gpio_t *gpio = evm_object_get_user_data(e, p);

  if (!iot_gpio_read(gpio)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kGpioOpRead)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(gpio_set_direction_sync) {
    EVM_EPCV;
  iot_gpio_t *gpio = evm_object_get_user_data(e, p);

  int direction = evm_2_integer(e, v[0]);
  if (direction >= __kGpioDirectionMax) {
    evm_throw(e, evm_mk_string(e, "Bad arguments - gpio.direction should be DIRECTION.IN or OUT"));
  }
  gpio->direction = direction;

  if (!iot_gpio_set_direction(gpio)) {
    evm_throw(e, evm_mk_string(e, "GPIO SetDirectionSync Error - Cannot set direction"));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(gpio_constructor) {
    EVM_EPCV;
  // Create GPIO object
  evm_val_t jgpio = evm_object_create(e);
  iot_gpio_t* gpio = gpio_create(e, jgpio);

  evm_val_t config_res =
      gpio_set_configuration(gpio, v[0]);
  EVM_ASSERT(evm_is_undefined(e, config_res));

  const evm_val_t jcallback = v[1];

  // If the callback doesn't exist, it is completed synchronously.
  // Otherwise, it will be executed asynchronously.
  if (!evm_is_null(e, jcallback)) {
    iot_periph_call_async(gpio, jcallback, kGpioOpOpen, gpio_worker);
  } else if (!iot_gpio_open(gpio)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kGpioOpOpen)));
  }
  evm_prop_set(e, jgpio, IOT_MAGIC_STRING_CLOSE, evm_mk_native(e, gpio_close, IOT_MAGIC_STRING_CLOSE, 0));
  evm_prop_set(e, jgpio, IOT_MAGIC_STRING_CLOSESYNC, evm_mk_native(e, gpio_close_sync, IOT_MAGIC_STRING_CLOSESYNC, 0));
  evm_prop_set(e, jgpio, IOT_MAGIC_STRING_WRITE, evm_mk_native(e, gpio_write, IOT_MAGIC_STRING_WRITE, 0));
  evm_prop_set(e, jgpio, IOT_MAGIC_STRING_WRITESYNC, evm_mk_native(e, gpio_write_sync, IOT_MAGIC_STRING_WRITESYNC, 0));
  evm_prop_set(e, jgpio, IOT_MAGIC_STRING_READ, evm_mk_native(e, gpio_read, IOT_MAGIC_STRING_READ, 0));
  evm_prop_set(e, jgpio, IOT_MAGIC_STRING_READSYNC, evm_mk_native(e, gpio_read_sync, IOT_MAGIC_STRING_READSYNC, 0));
  EVM_RETURN(jgpio);
}

void evm_module_gpio(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, gpio_constructor, IOT_MAGIC_STRING_CREATE, 0));

    evm_val_t jdirection = evm_object_create(e);
    evm_prop_set(e, jdirection, IOT_MAGIC_STRING_IN, evm_mk_number(e, kGpioDirectionIn));
    evm_prop_set(e, jdirection, IOT_MAGIC_STRING_OUT_U, evm_mk_number(e, kGpioDirectionOut));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_DIRECTION_U, jdirection);

    // GPIO mode properties
    evm_val_t jmode = evm_object_create(e);
    evm_prop_set(e, jmode, IOT_MAGIC_STRING_NONE_U, evm_mk_number(e, kGpioModeNone));
    evm_prop_set(e, jmode, IOT_MAGIC_STRING_PULLUP_U,
                                     evm_mk_number(e, kGpioModePullup));
    evm_prop_set(e, jmode, IOT_MAGIC_STRING_PULLDOWN_U,
                                 evm_mk_number(e, kGpioModePulldown));
    evm_prop_set(e, jmode, IOT_MAGIC_STRING_FLOAT_U,
                                 evm_mk_number(e, kGpioModeFloat));
    evm_prop_set(e, jmode, IOT_MAGIC_STRING_PUSHPULL_U,
                                 evm_mk_number(e, kGpioModePushpull));
    evm_prop_set(e, jmode, IOT_MAGIC_STRING_OPENDRAIN_U,
                                 evm_mk_number(e, kGpioModeOpendrain));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_MODE_U, jmode);

    // GPIO edge properties
    evm_val_t jedge = evm_object_create(e);
    evm_prop_set(e, jedge, IOT_MAGIC_STRING_NONE_U,
                                 evm_mk_number(e,kGpioEdgeNone));
    evm_prop_set(e, jedge, IOT_MAGIC_STRING_RISING_U,
                                 evm_mk_number(e,kGpioEdgeRising));
    evm_prop_set(e, jedge, IOT_MAGIC_STRING_FALLING_U,
                                 evm_mk_number(e,kGpioEdgeFalling));
    evm_prop_set(e, jedge, IOT_MAGIC_STRING_BOTH_U,
                                 evm_mk_number(e,kGpioEdgeBoth));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_EDGE_U, jedge);

    evm_module_add(e, "gpio", obj);
}
#endif
