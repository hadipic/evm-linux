#include "evm_port_adc.h"
#include "bflb_adc.h"

typedef struct port_adc_t {
    struct bflb_device_s* device;
} port_adc_t;

evm_port_adc_t *evm_port_adc_init(void) {
    evm_port_adc_t* dev = evm_malloc(sizeof(evm_port_adc_t));
    dev->pin = -1;
    dev->data = evm_malloc(sizeof(port_adc_t));
    memset(dev->data, 0, sizeof(port_adc_t));
    return dev;
}

static int8_t pin2ch(uint32_t pin) {
    switch (pin) {
        case 0:
            return ADC_CHANNEL_9;
        case 1:
            return ADC_CHANNEL_8;
        case 2:
            return ADC_CHANNEL_2;
        case 3:
            return ADC_CHANNEL_3;
        case 10:
            return ADC_CHANNEL_7;
        case 12:
            return ADC_CHANNEL_6;
        case 13:
            return ADC_CHANNEL_5;
        case 14:
            return ADC_CHANNEL_4;
        case 19:
            return ADC_CHANNEL_1;
        case 20:
            return ADC_CHANNEL_0;
        case 27:
            return ADC_CHANNEL_10;
        case 28:
            return ADC_CHANNEL_11;
        default:
            return -1;
    }
}

int evm_port_adc_open(evm_port_adc_t *info, int pin) {
    port_adc_t *dev = (port_adc_t*)info->data;

    dev->device = bflb_device_get_by_name("adc");

    struct bflb_adc_config_s cfg;
    cfg.clk_div = ADC_CLK_DIV_32;
    cfg.scan_conv_mode = true;
    cfg.continuous_conv_mode = false;
    cfg.differential_mode = false;
    cfg.resolution = ADC_RESOLUTION_16B;
    cfg.vref = ADC_VREF_3P2V;

    struct bflb_adc_channel_s channel;
    channel.pos_chan = pin2ch(pin);
    channel.neg_chan = ADC_CHANNEL_GND;

    bflb_adc_init(dev->device, &cfg);
    bflb_adc_channel_config(dev->device, &channel, 1);

    return 0;
}

int evm_port_adc_close(evm_port_adc_t *info) {
    port_adc_t *dev = (port_adc_t*)info->data;
    if (NULL != dev) {
        evm_free(dev);
    }
    return 0;
}

int evm_port_adc_read(evm_port_adc_t *info) {
    port_adc_t *dev = (port_adc_t*)info->data;
    bflb_adc_start_conversion(dev->device);
    while (bflb_adc_get_count(dev->device) < 1) {
        bflb_mtimer_delay_ms(1);
    }
    uint32_t raw_data = bflb_adc_read_raw(dev->device);
    bflb_adc_stop_conversion(dev->device);
    struct bflb_adc_result_s result;
    bflb_adc_parse_result(dev->device, &raw_data, &result, 1);
    return result.millivolt;
}



