/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifdef CONFIG_EVM_MODULE_PWM

#include "evm_module_pwm.h"

IOT_DEFINE_PERIPH_CREATE_FUNCTION(pwm)

static void pwm_worker(uv_work_t* work_req) {
  iot_periph_data_t* worker_data =
      (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);
  iot_pwm_t* pwm = (iot_pwm_t*)worker_data->data;

  switch (worker_data->op) {
    case kPwmOpClose:
      worker_data->result = iot_pwm_close(pwm);
      break;
    case kPwmOpOpen:
      worker_data->result = iot_pwm_open(pwm);
      break;
    case kPwmOpSetDutyCycle:
      worker_data->result = iot_pwm_set_dutycycle(pwm);
      break;
    case kPwmOpSetEnable:
      worker_data->result = iot_pwm_set_enable(pwm);
      break;
    case kPwmOpSetFrequency: /* update the period */
    case kPwmOpSetPeriod:
      worker_data->result = iot_pwm_set_period(pwm);
      break;
    default:
      EVM_ASSERT(!"Invalid Operation");
  }
}

EVM_FUNCTION(pwm_close) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);
  iot_periph_call_async(pwm, v[0], kPwmOpClose,
                          pwm_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_close_sync) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  if (!iot_pwm_close(pwm)) {
      evm_throw(e, evm_mk_string(e, iot_periph_error_str(kPwmOpClose)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_set_duty_cycle) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  evm_val_t jcallback = v[1];

  pwm->duty_cycle = evm_2_integer(e, v[0]);
  if (pwm->duty_cycle < 0.0 || pwm->duty_cycle > 1.0) {
    evm_throw(e, evm_mk_string(e, "pwm.dutyCycle must be within 0.0 and 1.0"));
  }

  iot_periph_call_async(pwm, jcallback, kPwmOpSetDutyCycle, pwm_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_set_duty_cycle_sync) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  pwm->duty_cycle = evm_2_integer(e, v[0]);
  if (pwm->duty_cycle < 0.0 || pwm->duty_cycle > 1.0) {
    evm_throw(e, evm_mk_string(e, "pwm.dutyCycle must be within 0.0 and 1.0"));
  }

  if (!iot_pwm_set_dutycycle(pwm)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kPwmOpSetDutyCycle)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_set_enable) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  evm_val_t jcallback = v[1];

  pwm->enable = evm_2_boolean(e, v[0]);

  iot_periph_call_async(pwm, jcallback, kPwmOpSetEnable, pwm_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_set_enable_sync) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  pwm->enable = evm_2_boolean(e, v[0]);

  if (!iot_pwm_set_enable(pwm)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kPwmOpSetEnable)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

static evm_val_t pwm_set_period_or_frequency(evm_t *e, iot_pwm_t* pwm, evm_val_t v[], int argc, uint8_t op, bool async) {
  const double num_value = evm_2_double(e, v[0]);

  if (op == kPwmOpSetFrequency) {
    if (num_value <= 0) {
      evm_throw(e, evm_mk_string(e, "frequency must be greater than 0"));
    }
    pwm->period = 1.0 / num_value;

  } else {
    if (num_value < 0) {
      evm_throw(e, evm_mk_string(e, "period must be a positive value"));
    }
    pwm->period = num_value;
  }

  if (async) {
    iot_periph_call_async(pwm, v[1], op,
                            pwm_worker);
  } else {
    if (!iot_pwm_set_period(pwm)) {
      evm_throw(e, evm_mk_string(e, iot_periph_error_str(op)));
    }
  }

  EVM_RETURN_VAL(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_set_frequency) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  EVM_RETURN(pwm_set_period_or_frequency(e, pwm, v, argc, kPwmOpSetFrequency,
                                     true));
}

EVM_FUNCTION(pwm_set_frequency_sync) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  EVM_RETURN(pwm_set_period_or_frequency(e, pwm, v, argc, kPwmOpSetFrequency,
                                     false));
}

EVM_FUNCTION(pwm_set_period) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  EVM_RETURN(pwm_set_period_or_frequency(e, pwm, v, argc, kPwmOpSetPeriod, true));
}

EVM_FUNCTION(pwm_set_period_sync) {
    EVM_EPCV;
  iot_pwm_t *pwm = evm_object_get_user_data(e, p);

  EVM_RETURN(pwm_set_period_or_frequency(e, pwm, v, argc, kPwmOpSetPeriod, false));
}

static evm_val_t pwm_set_configuration(iot_pwm_t* pwm,
                                           evm_val_t jconfig) {
  evm_t *e = evm_runtime();
  pwm->duty_cycle = evm_2_integer(e, evm_prop_get(e, jconfig, IOT_MAGIC_STRING_DUTYCYCLE));
  if (pwm->duty_cycle < 0.0 || pwm->duty_cycle > 1.0) {
    evm_throw(e, evm_mk_string(e, "pwm.dutyCycle must be within 0.0 and 1.0"));
  }

  pwm->period = evm_2_integer(e, evm_prop_get(e, jconfig, IOT_MAGIC_STRING_PERIOD));
  if (pwm->period < 0) {
    evm_throw(e, evm_mk_string(e, "pwm.period must be a positive value"));
  }

  pwm->pin = evm_2_integer(e, evm_prop_get(e, jconfig, IOT_MAGIC_STRING_PIN));

  EVM_RETURN_VAL(EVM_UNDEFINED);
}

EVM_FUNCTION(pwm_constructor) {
    EVM_EPCV;
  // Create PWM object
  evm_val_t jpwm = evm_object_create(e);
  iot_pwm_t* pwm = pwm_create(e, jpwm);

  evm_val_t jconfig = v[0];

  evm_val_t res = iot_pwm_set_platform_config(pwm, jconfig);
  EVM_ASSERT(evm_is_undefined(e, res));

  res = pwm_set_configuration(pwm, jconfig);
  EVM_ASSERT(evm_is_undefined(e, res));

  evm_val_t jcallback = v[1];

  // If the callback doesn't exist, it is completed synchronously.
  // Otherwise, it will be executed asynchronously.
  if (!evm_is_null(e, jcallback)) {
    iot_periph_call_async(pwm, jcallback, kPwmOpOpen, pwm_worker);
  } else if (!iot_pwm_open(pwm)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kPwmOpOpen)));
  }

  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_CLOSE, evm_mk_native(e, pwm_close, IOT_MAGIC_STRING_CLOSE, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_CLOSESYNC, evm_mk_native(e, pwm_close_sync, IOT_MAGIC_STRING_CLOSESYNC, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETDUTYCYCLE, evm_mk_native(e, pwm_set_duty_cycle, IOT_MAGIC_STRING_SETDUTYCYCLE, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETDUTYCYCLESYNC, evm_mk_native(e, pwm_set_duty_cycle_sync, IOT_MAGIC_STRING_SETDUTYCYCLESYNC, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETENABLE, evm_mk_native(e, pwm_set_enable, IOT_MAGIC_STRING_SETENABLE, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETENABLESYNC, evm_mk_native(e, pwm_set_enable_sync, IOT_MAGIC_STRING_SETENABLESYNC, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETFREQUENCY, evm_mk_native(e, pwm_set_frequency, IOT_MAGIC_STRING_SETFREQUENCY, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETFREQUENCYSYNC, evm_mk_native(e, pwm_set_frequency_sync, IOT_MAGIC_STRING_SETFREQUENCYSYNC, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETPERIOD, evm_mk_native(e, pwm_set_period, IOT_MAGIC_STRING_SETPERIOD, 0));
  evm_prop_set(e, jpwm, IOT_MAGIC_STRING_SETPERIODSYNC, evm_mk_native(e, pwm_set_period_sync, IOT_MAGIC_STRING_SETPERIODSYNC, 0));
  EVM_RETURN(jpwm);
}

void evm_module_pwm(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, pwm_constructor, IOT_MAGIC_STRING_CREATE, 0));
    evm_module_add(e, "pwm", obj);
}
#endif
