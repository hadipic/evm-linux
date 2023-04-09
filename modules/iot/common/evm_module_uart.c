/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifdef EVM_USE_MODULE_UART

#include "evm_module_uart.h"

static void uart_worker(uv_work_t* work_req) {
    iot_periph_data_t* worker_data = (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);
    uv_handle_t* uart_poll_handle = (uv_handle_t*)worker_data->data;

    switch (worker_data->op) {
    case kUartOpOpen:
        worker_data->result = iot_uart_open(uart_poll_handle);
        break;
    case kUartOpWrite:
        worker_data->result = iot_uart_write(uart_poll_handle);
        break;
    case kUartOpClose:
        iot_uv_handle_close(uart_poll_handle, iot_uart_handle_close_cb);
        worker_data->result = true;
        break;
    default:
        DDDLOG("Invalid Operation");
        EVM_ASSERT(0);
    }
}

void iot_uart_register_read_cb(uv_poll_t* uart_poll_handle) {
    iot_uart_t* uart = (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);
    uv_loop_t* loop = system_get_uv_loop();
    uv_poll_init(loop, uart_poll_handle, uart->device_fd);
    uv_poll_start(uart_poll_handle, UV_READABLE, iot_uart_read_cb);
}

static evm_val_t uart_set_configuration(iot_uart_t* uart, evm_val_t jconfig) {
    evm_t *e = evm_runtime();
    evm_val_t jbaud_rate = evm_prop_get(e, jconfig, IOT_MAGIC_STRING_BAUDRATE);
    if (evm_is_undefined(e, jbaud_rate)) {
        uart->baud_rate = 9600;
    } else {
        if (!evm_is_number(e, jbaud_rate)) {
            evm_val_free(e, jbaud_rate);
            evm_throw(e, evm_mk_string(e, "Bad configuration - baud rate must be a Number"));
        }
        unsigned br = (unsigned)evm_2_integer(e, jbaud_rate);
        evm_val_free(e, jbaud_rate);

        if (br != 230400 && br != 115200 && br != 57600 && br != 38400 &&
            br != 19200 && br != 9600 && br != 4800 && br != 2400 && br != 1800 &&
            br != 1200 && br != 600 && br != 300 && br != 200 && br != 150 &&
            br != 134 && br != 110 && br != 75 && br != 50 && br != 0) {
            evm_throw(e, evm_mk_string(e, "Invalid baud rate"));
        }

        uart->baud_rate = br;
    }

    evm_val_t jdata_bits = evm_prop_get(e, jconfig, IOT_MAGIC_STRING_DATABITS);
    if (evm_is_undefined(e, jdata_bits)) {
        uart->data_bits = 8;
    } else {
        if (!evm_is_number(e, jdata_bits)) {
            evm_val_free(e, jdata_bits);
            evm_throw(e, evm_mk_string(e, "Bad configuration - data bits must be a Number"));
        }
        uint8_t db = (uint8_t)evm_2_integer(e, jdata_bits);
        evm_val_free(e, jdata_bits);

        if (db > 8 || db < 5) {
            evm_throw(e, evm_mk_string(e, "Invalid data bits"));
        }
        uart->data_bits = db;
    }

    return EVM_UNDEFINED;
}

EVM_FUNCTION(uart_open) {
    EVM_EPCV;
    const evm_val_t juart = evm_val_duplicate(e, v[0]);
    uv_handle_t* uart_poll_handle = iot_uv_handle_create(sizeof(uv_poll_t), juart, sizeof(iot_uart_t));
    iot_uart_t* uart = (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);
    iot_uart_create_platform_data(uart);
    uart->device_fd = -1;

    evm_val_t jconfig = v[1];

    evm_val_t res = iot_uart_set_platform_config(e, uart, jconfig);
    res = uart_set_configuration(uart, jconfig);

    DDDLOG("%s - baudRate: %d, dataBits: %d", __func__, uart->baud_rate, uart->data_bits);

    evm_val_t jcallback = v[2];
    if (argc > 1 && evm_is_callable(e, jcallback)) {
        iot_periph_call_async(uart_poll_handle, jcallback, kUartOpOpen, uart_worker);
    } else if (!iot_uart_open(uart_poll_handle)) {
        evm_throw(e, evm_mk_string(e, iot_periph_error_str(kUartOpOpen)));
    }

    EVM_RETURN(juart)
}

EVM_FUNCTION(uart_write) {
    EVM_EPCV;
    uv_handle_t *uart_poll_handle = evm_object_get_user_data(e, v[0]);

    iot_uart_t* uart =
      (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);
    uart->buf_data = evm_2_string(e, v[1]);
    uart->buf_len = evm_string_len(e, v[1]);

    iot_periph_call_async(uart_poll_handle, v[2],
                          kUartOpWrite, uart_worker);

    EVM_RETURN (EVM_UNDEFINED);
}

EVM_FUNCTION(uart_read) {
    EVM_EPCV;
    uv_handle_t *uart_poll_handle = evm_object_get_user_data(e, v[0]);

    iot_uart_read(uart_poll_handle);

    EVM_RETURN (EVM_UNDEFINED);
}

EVM_FUNCTION(uart_write_sync) {
    EVM_EPCV;
    uv_handle_t *uart_poll_handle = evm_object_get_user_data(e, v[0]);

    iot_uart_t* uart = (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);
    uart->buf_data = evm_2_string(e, v[1]);
    uart->buf_len = evm_string_len(e, v[1]);

    bool result = iot_uart_write(uart_poll_handle);

    if (!result) {
        evm_throw(e, evm_mk_string(e, iot_periph_error_str(kUartOpWrite)));
    }

    EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(uart_close) {
    EVM_EPCV;
    uv_handle_t *uart_poll_handle = evm_object_get_user_data(e, v[0]);

    iot_periph_call_async(uart_poll_handle, v[1],
                            kUartOpClose, uart_worker);

    EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(uart_close_sync) {
    EVM_EPCV;
    uv_handle_t *uart_poll_handle = evm_object_get_user_data(e, v[0]);

    iot_uv_handle_close(uart_poll_handle, iot_uart_handle_close_cb);
    EVM_RETURN(EVM_UNDEFINED);
}

void evm_module_uart(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_OPEN, evm_mk_native(e, uart_open, IOT_MAGIC_STRING_OPEN, 0));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CLOSE, evm_mk_native(e, uart_close, IOT_MAGIC_STRING_CLOSE, 0));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CLOSESYNC, evm_mk_native(e, uart_close_sync, IOT_MAGIC_STRING_CLOSESYNC, 0));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_READ, evm_mk_native(e, uart_read, IOT_MAGIC_STRING_READ, 0));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_WRITE, evm_mk_native(e, uart_write, IOT_MAGIC_STRING_WRITE, 0));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_WRITESYNC, evm_mk_native(e, uart_write_sync, IOT_MAGIC_STRING_WRITESYNC, 0));

    evm_module_add(e, "@native.uart", obj);
}
#endif
