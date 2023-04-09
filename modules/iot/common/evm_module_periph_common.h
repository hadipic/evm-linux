/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_PERIPH_COMMON
#define EVM_MODULE_PERIPH_COMMON

#include "iot_uv.h"

typedef enum {
  kAdcOpOpen,
  kAdcOpRead,
  kAdcOpClose,
  kGpioOpOpen,
  kGpioOpWrite,
  kGpioOpRead,
  kGpioOpClose,
  kI2cOpOpen,
  kI2cOpClose,
  kI2cOpWrite,
  kI2cOpRead,
  kPwmOpClose,
  kPwmOpOpen,
  kPwmOpSetDutyCycle,
  kPwmOpSetEnable,
  kPwmOpSetFrequency,
  kPwmOpSetPeriod,
  kSpiOpClose,
  kSpiOpOpen,
  kSpiOpTransferArray,
  kSpiOpTransferBuffer,
  kUartOpClose,
  kUartOpOpen,
  kUartOpWrite
} iot_periph_op_t;

typedef struct {
  uint8_t op;
  bool result;
  void* data;
} iot_periph_data_t;

typedef struct iot_adc_platform_data_s iot_adc_platform_data_t;

typedef struct {
  evm_val_t jobject;
  iot_adc_platform_data_t* platform_data;
  int32_t value;
} iot_adc_t;


typedef enum {
  kGpioDirectionIn = 0,
  kGpioDirectionOut,
  __kGpioDirectionMax
} GpioDirection;

typedef enum {
  kGpioModeNone = 0,
  kGpioModePullup,
  kGpioModePulldown,
  kGpioModeFloat,
  kGpioModePushpull,
  kGpioModeOpendrain,
  __kGpioModeMax
} GpioMode;

typedef enum {
  kGpioEdgeNone = 0,
  kGpioEdgeRising,
  kGpioEdgeFalling,
  kGpioEdgeBoth,
  __kGpioEdgeMax
} GpioEdge;

typedef struct iot_gpio_platform_data_s iot_gpio_platform_data_t;

// This Gpio class provides interfaces for GPIO operation.
typedef struct {
  evm_val_t jobject;
  iot_gpio_platform_data_t* platform_data;

  bool value;
  uint32_t pin;
  GpioDirection direction;
  GpioMode mode;
  GpioEdge edge;
} iot_gpio_t;

// Forward declaration of platform data. These are only used by platform code.
// Generic I2C module never dereferences platform data pointer.
typedef struct iot_i2c_platform_data_s iot_i2c_platform_data_t;
// This I2c class provides interfaces for I2C operation.
typedef struct {
  evm_val_t jobject;
  iot_i2c_platform_data_t* platform_data;

  char* buf_data;
  uint8_t buf_len;
  uint8_t address;
} iot_i2c_t;

typedef enum {
  kSpiMode_0,
  kSpiMode_1,
  kSpiMode_2,
  kSpiMode_3,
  __kSpiModeMax
} SpiMode;

typedef enum { kSpiCsNone, kSpiCsHigh, __kSpiCsMax } SpiChipSelect;

typedef enum { kSpiOrderMsb, kSpiOrderLsb, __kSpiOrderMax } SpiOrder;

// Forward declaration of platform data. These are only used by platform code.
// Generic SPI module never dereferences platform data pointer.
typedef struct iot_spi_platform_data_s iot_spi_platform_data_t;
// This SPI class provides interfaces for SPI operation.
typedef struct {
  evm_val_t jobject;
  iot_spi_platform_data_t* platform_data;

  SpiMode mode;
  SpiChipSelect chip_select;
  SpiOrder bit_order;
  uint8_t bits_per_word;
  uint16_t delay;
  uint32_t max_speed;
  bool loopback;

  // SPI buffer
  char* tx_buf_data;
  char* rx_buf_data;
  uint8_t buf_len;
} iot_spi_t;

#define UART_WRITE_BUFFER_SIZE 512

typedef struct iot_uart_platform_data_s iot_uart_platform_data_t;

typedef struct {
  intptr_t device_fd;
  unsigned baud_rate;
  uint8_t data_bits;
  char *buf_data;
  unsigned buf_len;

  iot_uart_platform_data_t* platform_data;
} iot_uart_t;

typedef struct iot_pwm_platform_data_s iot_pwm_platform_data_t;

typedef struct {
  evm_val_t jobject;
  iot_pwm_platform_data_t* platform_data;

  uint32_t pin;
  double duty_cycle;
  double period;
  bool enable;
} iot_pwm_t;

void iot_periph_call_async(void* data, evm_val_t jcallback, uint8_t op, uv_work_cb worker);
const char* iot_periph_error_str(uint8_t op);

#endif
