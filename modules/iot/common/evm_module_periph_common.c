/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module_periph_common.h"

const char* iot_periph_error_str(uint8_t op) {
  switch (op) {
#if CONFIG_EVM_MODULE_ADC
    case kAdcOpClose:
      return "Close error, cannot close ADC";
    case kAdcOpOpen:
      return "Open error, cannot open ADC";
    case kAdcOpRead:
      return "Read error, cannot read ADC";
#endif /* ENABLE_MODULE_ADC */
#if CONFIG_EVM_MODULE_GPIO
    case kGpioOpOpen:
      return "Open error, cannot open GPIO";
    case kGpioOpWrite:
      return "Write error, cannot write GPIO";
    case kGpioOpRead:
      return "Read error, cannot read GPIO";
    case kGpioOpClose:
      return "Close error, cannot close GPIO";
#endif /* ENABLE_MODULE_GPIO */
#if CONFIG_EVM_MODULE_I2C
    case kI2cOpOpen:
      return "Open error, cannot open I2C";
    case kI2cOpWrite:
      return "Write error, cannot write I2C";
    case kI2cOpRead:
      return "Read error, cannot read I2C";
    case kI2cOpClose:
      return "Close error, cannot close I2C";
#endif /* ENABLE_MODULE_I2C */
#if CONFIG_EVM_MODULE_PWM
    case kPwmOpClose:
      return "Cannot close PWM device";
    case kPwmOpOpen:
      return "Failed to open PWM device";
    case kPwmOpSetDutyCycle:
      return "Failed to set duty-cycle";
    case kPwmOpSetEnable:
      return "Failed to set enable";
    case kPwmOpSetFrequency:
      return "Failed to set frequency";
    case kPwmOpSetPeriod:
      return "Failed to set period";
#endif /* ENABLE_MODULE_PWM */
#if CONFIG_EVM_MODULE_SPI
    case kSpiOpClose:
      return "Close error, cannot close SPI";
    case kSpiOpOpen:
      return "Open error, cannot open SPI";
    case kSpiOpTransferArray:
    case kSpiOpTransferBuffer:
      return "Transfer error, cannot transfer from SPI device";
#endif /* ENABLE_MODULE_SPI */
#if CONFIG_EVM_MODULE_UART
    case kUartOpClose:
      return "Close error, failed to close UART device";
    case kUartOpOpen:
      return "Open error, failed to open UART device";
    case kUartOpWrite:
      return "Write error, cannot write to UART device";
#endif /* ENABLE_MODULE_UART */
    default:
      return "Unknown error";
  }
}

static void after_worker(uv_work_t* work_req, int status) {
    evm_t *e = evm_runtime();
    iot_periph_data_t* worker_data =
      (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);

    int jargc = 0;
    evm_val_t jargs[2] = { EVM_UNDEFINED, EVM_UNDEFINED };

    if (status) {
        jargs[jargc++] = evm_mk_string(e, "System error");
    } else {
    if (!worker_data->result) {
        jargs[jargc++] = evm_mk_string(e, iot_periph_error_str(worker_data->op));
    } else {
        jargs[jargc++] = evm_mk_null(e);
        switch (worker_data->op) {
            case kAdcOpClose:
            case kAdcOpOpen:
            case kGpioOpClose:
            case kGpioOpOpen:
            case kGpioOpWrite:
            case kI2cOpClose:
            case kI2cOpOpen:
            case kI2cOpWrite:
            case kSpiOpClose:
            case kSpiOpOpen:
            case kPwmOpClose:
            case kPwmOpOpen:
            case kPwmOpSetDutyCycle:
            case kPwmOpSetEnable:
            case kPwmOpSetFrequency:
            case kPwmOpSetPeriod:
            case kUartOpClose:
            case kUartOpOpen:
            case kUartOpWrite: {
              break;
            }
            case kAdcOpRead: {
        #if CONFIG_EVM_MODULE_ADC
              iot_adc_t* adc = (iot_adc_t*)worker_data->data;
              jargs[jargc++] = evm_mk_number(e, adc->value);
        #endif /* ENABLE_MODULE_ADC */
              break;
            }
            case kGpioOpRead: {
        #if CONFIG_EVM_MODULE_GPIO
              iot_gpio_t* gpio = (iot_gpio_t*)worker_data->data;
              jargs[jargc++] = evm_mk_boolean(e, gpio->value);
        #endif /* ENABLE_MODULE_GPIO */
              break;
            }
            case kI2cOpRead: {
        #if CONFIG_EVM_MODULE_I2C
              iot_i2c_t* i2c = (iot_i2c_t*)worker_data->data;
              jargs[jargc++] = evm_buffer_create(e, (uint8_t*)i2c->buf_data, i2c->buf_len);
              evm_free(i2c->buf_data);
        #endif /* ENABLE_MODULE_I2C */
              break;
            }
            case kSpiOpTransferArray:
            case kSpiOpTransferBuffer: {
        #if CONFIG_EVM_MODULE_SPI
              iot_spi_t* spi = (iot_spi_t*)worker_data->data;
              // Append read data
              jargs[jargc++] = evm_buffer_create(e, (uint8_t*)spi->rx_buf_data, spi->buf_len);
              evm_free(spi->rx_buf_data);
        #endif /* ENABLE_MODULE_SPI */
              break;
            }
            default: {
              EVM_ASSERT(!"Unreachable");
              break;
            }
        }
    }
    #if CONFIG_EVM_MODULE_SPI
    if (worker_data->op == kSpiOpTransferArray) {
      iot_spi_t* spi = (iot_spi_t*)worker_data->data;
      evm_free(spi->tx_buf_data);
    }
    #endif /* ENABLE_MODULE_SPI */
    #if CONFIG_EVM_MODULE_UART
    if (worker_data->op == kUartOpWrite) {
      iot_uart_t* uart = (iot_uart_t*)worker_data->data;
      evm_free(uart->buf_data);
    }
    #endif /* ENABLE_MODULE_UART */
    }

    evm_val_t jcallback = *IOT_UV_REQUEST_CALLBACK(work_req);
    if (evm_is_callable(e, jcallback)) {
        evm_call_free(e, jcallback, EVM_UNDEFINED, jargc, jargs);
    }

    for (int i = 0; i < jargc; i++) {
        evm_val_free(e, jargs[i]);
    }

    iot_uv_request_destroy((uv_req_t*)work_req);
}


void iot_periph_call_async(void* data, evm_val_t jcallback, uint8_t op, uv_work_cb worker) {
  uv_loop_t* loop = system_get_uv_loop();

  uv_req_t* work_req = iot_uv_request_create(sizeof(uv_work_t), jcallback,
                                               sizeof(iot_periph_data_t));
  iot_periph_data_t* worker_data =
      (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);
  worker_data->op = op;
  worker_data->data = data;

  uv_queue_work(loop, (uv_work_t*)work_req, worker, after_worker);
}
