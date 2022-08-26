#ifdef CONFIG_EVM_MODULE_WLAN
#include "evm_module.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"

static int is_connected = 0;
static const char *TAG = "wifi softAP";

void evm_wlan_connect(evm_t *e, char *ssid, char *pwd) {
    wifi_config_t wifi_config;
    
    wifi_config.ap.ssid_len = strlen(ssid);
    memcpy(wifi_config.ap.ssid, ssid, wifi_config.ap.ssid_len);
    wifi_config.ap.channel = 6;
    memcpy(wifi_config.ap.password, pwd, strlen(pwd));
    wifi_config.ap.max_connection = 4;
    wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    if (strlen(pwd) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void evm_wlan_disconnect(evm_t *e) {
    if (evm_wlan_is_connectd(e)) {
        if( esp_wifi_disconnect() == ESP_OK )
            is_connected = 0;    
    }
}

int evm_wlan_is_connectd(evm_t *e) {
    return is_connected;
}

evm_val_t evm_wlan_scan(evm_t *e) {
    return EVM_UNDEFINED;
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        is_connected = 1;
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        is_connected = 0;
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

void evm_wlan_init(evm_t *e) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
}

#endif
