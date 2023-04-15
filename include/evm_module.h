/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_H
#define EVM_MODULE_H

#include "evm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PATH_MAX_LEN    256

#define IOT_DEFINE_PERIPH_CREATE_FUNCTION(name)                             \
  static iot_##name##_t* name##_create(evm_t *e, evm_val_t jobject) {       \
    iot_##name##_t* data = evm_malloc(sizeof(iot_##name##_t));                   \
    iot_##name##_create_platform_data(data);                                \
    data->jobject = jobject;                                                  \
    evm_object_set_user_data(e, jobject, data); \
    return data;                                                              \
  }

#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_0 "0"
#define IOT_MAGIC_STRING_1 "1"
#define IOT_MAGIC_STRING_2 "2"
#define IOT_MAGIC_STRING_3 "3"
#endif
#define IOT_MAGIC_STRING_ABORT "abort"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_ACKTYPE "type"
#endif
#if EVM_USE_MODULE_ADC
#define IOT_MAGIC_STRING_ADC "Adc"
#endif
#define IOT_MAGIC_STRING_ADDHEADER "addHeader"
#if EVM_USE_MODULE_UDP
#define IOT_MAGIC_STRING_ADDMEMBERSHIP "addMembership"
#endif
#define IOT_MAGIC_STRING_ADDRESS "address"
#define IOT_MAGIC_STRING_ARCH "arch"
#define IOT_MAGIC_STRING_ARGV "argv"
#define IOT_MAGIC_STRING_BASE64 "base64"
#if EVM_USE_MODULE_CRYPTO
#define IOT_MAGIC_STRING_BASE64ENCODE "base64Encode"
#endif
#if EVM_USE_MODULE_UART
#define IOT_MAGIC_STRING_BAUDRATE "baudRate"
#endif
#define IOT_MAGIC_STRING_BIND "bind"
#if EVM_USE_MODULE_BLE
#define IOT_MAGIC_STRING_BINDCONTROL "bindControl"
#endif
#define IOT_MAGIC_STRING_BINDING "binding"
#if EVM_USE_MODULE_BLE
#define IOT_MAGIC_STRING_BINDRAW "bindRaw"
#define IOT_MAGIC_STRING_BINDUSER "bindUser"
#endif
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_BITORDER "bitOrder"
#define IOT_MAGIC_STRING_BITORDER_U "BITORDER"
#define IOT_MAGIC_STRING_BITSPERWORD "bitsPerWord"
#endif
#define IOT_MAGIC_STRING_BOARD "board"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_BOTH_U "BOTH"
#endif
#define IOT_MAGIC_STRING_BUFFER "Buffer"
#define IOT_MAGIC_STRING_BUILTIN_MODULES "builtin_modules"
#if EVM_USE_MODULE_I2C || EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_BUS "bus"
#endif
#define IOT_MAGIC_STRING_BYTELENGTH "byteLength"
#define IOT_MAGIC_STRING_BYTEPARSED "byteParsed"
#define IOT_MAGIC_STRING_FROM_ARRAYBUFFER "fromArrayBuffer"
#if EVM_USE_MODULE_HTTPS || EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_CA "ca"
#define IOT_MAGIC_STRING_CERT "cert"
#endif
#define IOT_MAGIC_STRING_CHDIR "chdir"
#if EVM_USE_MODULE_PWM
#define IOT_MAGIC_STRING_CHIP "chip"
#endif
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_CHIPSELECT "chipSelect"
#define IOT_MAGIC_STRING_CHIPSELECT_U "CHIPSELECT"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_CLIENTID "clientId"
#endif
#define IOT_MAGIC_STRING_CREATE "create"
#define IOT_MAGIC_STRING_CLOSE "close"
#define IOT_MAGIC_STRING_CLOSESYNC "closeSync"
#define IOT_MAGIC_STRING_CODE "code"
#define IOT_MAGIC_STRING_COMPARE "compare"
#define IOT_MAGIC_STRING_COMPILE "compile"
#define IOT_MAGIC_STRING_COMPILEMODULE "compileModule"
#define IOT_MAGIC_STRING_CONFIG "config"
#define IOT_MAGIC_STRING_CONNECT "connect"
#define IOT_MAGIC_STRING_COPY "copy"
#if EVM_USE_MODULE_HTTPS
#define IOT_MAGIC_STRING_CREATEREQUEST "createRequest"
#endif
#define IOT_MAGIC_STRING__CREATESTAT "_createStat"
#define IOT_MAGIC_STRING_CREATETCP "createTCP"
#define IOT_MAGIC_STRING_CWD "cwd"
#define IOT_MAGIC_STRING_DATA "data"
#if EVM_USE_MODULE_UART
#define IOT_MAGIC_STRING_DATABITS "dataBits"
#endif
#ifdef DEBUG
#define IOT_MAGIC_STRING_DEBUG "debug"
#endif
#define IOT_MAGIC_STRING_DEBUGGERGETSOURCE "debuggerGetSource"
#define IOT_MAGIC_STRING_DEBUGGERWAITSOURCE "debuggerWaitSource"
#if EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_DECODEFRAME "decodeFrame"
#endif
#define IOT_MAGIC_STRING_DEVICE "device"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_DIRECTION "direction"
#define IOT_MAGIC_STRING_DIRECTION_U "DIRECTION"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_DISCONNECT "disconnect"
#endif
#define IOT_MAGIC_STRING_DOEXIT "doExit"
#if EVM_USE_MODULE_UDP
#define IOT_MAGIC_STRING_DROPMEMBERSHIP "dropMembership"
#endif
#if EVM_USE_MODULE_PWM
#define IOT_MAGIC_STRING_DUTYCYCLE "dutyCycle"
#endif
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_EDGE "edge"
#define IOT_MAGIC_STRING_EDGE_U "EDGE"
#endif
#define IOT_MAGIC_STRING_EMIT "emit"
#define IOT_MAGIC_STRING_EMITEXIT "emitExit"
#if EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_END "end"
#endif
#define IOT_MAGIC_STRING_ENV "env"
#define IOT_MAGIC_STRING_ERRNAME "errname"
#define IOT_MAGIC_STRING_EXECUTE "execute"
#define IOT_MAGIC_STRING_EXITCODE "exitCode"
#define IOT_MAGIC_STRING_EXPORT "export"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_FALLING_U "FALLING"
#endif
#define IOT_MAGIC_STRING_FAMILY "family"
#define IOT_MAGIC_STRING_FINISH "finish"
#if EVM_USE_MODULE_HTTPS
#define IOT_MAGIC_STRING_FINISHREQUEST "finishRequest"
#endif
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_FLOAT_U "FLOAT"
#endif
#define IOT_MAGIC_STRING_FSTAT "fstat"
#if EXPOSE_GC
#define IOT_MAGIC_STRING_GC "gc"
#endif
#define IOT_MAGIC_STRING_GETADDRINFO "getaddrinfo"
#define IOT_MAGIC_STRING_GETSOCKNAME "getsockname"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_GPIO "Gpio"
#endif
#define IOT_MAGIC_STRING_HANDLER "handler"
#define IOT_MAGIC_STRING_HANDLETIMEOUT "handleTimeout"
#define IOT_MAGIC_STRING_HEADERS "headers"
#define IOT_MAGIC_STRING_HEX "hex"
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_HIGH_U "HIGH"
#endif
#define IOT_MAGIC_STRING_HOME_U "HOME"
#define IOT_MAGIC_STRING_HOST "host"
#define IOT_MAGIC_STRING_HTTPPARSER "HTTPParser"
#define IOT_MAGIC_STRING_HTTP_VERSION_MAJOR "http_major"
#define IOT_MAGIC_STRING_HTTP_VERSION_MINOR "http_minor"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_IN "IN"
#endif
#define IOT_MAGIC_STRING__INCOMING "_incoming"
#define IOT_MAGIC_STRING_EVM_PATH_U "EVM_PATH"
#define IOT_MAGIC_STRING_EVM_MODULE_PATH_U "EVM_MODULE_PATH"
#define IOT_MAGIC_STRING_IPV4 "IPv4"
#define IOT_MAGIC_STRING_IPV6 "IPv6"
#define IOT_MAGIC_STRING_ISALIVEEXCEPTFOR "isAliveExceptFor"
#define IOT_MAGIC_STRING_ISDEVUP "isDevUp"
#define IOT_MAGIC_STRING_ISDIRECTORY "isDirectory"
#define IOT_MAGIC_STRING_ISFILE "isFile"
#if EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_ISSERVER "isServer"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_KEEPALIVE "keepalive"
#endif
#define IOT_MAGIC_STRING_KEY "key"
#define IOT_MAGIC_STRING_LENGTH "length"
#define IOT_MAGIC_STRING_LISTEN "listen"
#define IOT_MAGIC_STRING_LOOPBACK "loopback"
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_LSB "LSB"
#define IOT_MAGIC_STRING_MAXSPEED "maxSpeed"
#endif
#if EVM_USE_MODULE_MQTT || EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_MESSAGE "message"
#endif
#define IOT_MAGIC_STRING_METHOD "method"
#define IOT_MAGIC_STRING_METHODS "methods"
#define IOT_MAGIC_STRING_MKDIR "mkdir"
#define IOT_MAGIC_STRING_MODE "mode"
#if EVM_USE_MODULE_SPI || EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_MODE_U "MODE"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_MQTTINIT "MqttInit"
#define IOT_MAGIC_STRING_MQTTMESSAGE "MqttMessage"
#define IOT_MAGIC_STRING_MQTTRECEIVE "MqttReceive"
#endif
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_MSB "MSB"
#endif
#if EVM_USE_MODULE_SPI || EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_NONE_U "NONE"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_ONACK "onack"
#endif
#define IOT_MAGIC_STRING_ONBODY "OnBody"
#define IOT_MAGIC_STRING_ONCLOSE "onclose"
#define IOT_MAGIC_STRING_ONCLOSED "onClosed"
#define IOT_MAGIC_STRING_ONCONNECTION "onconnection"
#define IOT_MAGIC_STRING_ONDATA "onData"
#define IOT_MAGIC_STRING_ONEND "onEnd"
#define IOT_MAGIC_STRING_ONERROR "onError"
#if EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_ONHANDSHAKEDONE "onhandshakedone"
#endif
#define IOT_MAGIC_STRING_ONHEADERSCOMPLETE "OnHeadersComplete"
#define IOT_MAGIC_STRING_ONHEADERS "OnHeaders"
#define IOT_MAGIC_STRING_ONMESSAGECOMPLETE "OnMessageComplete"
#define IOT_MAGIC_STRING_ONMESSAGE "onmessage"
#define IOT_MAGIC_STRING__ONNEXTTICK "_onNextTick"
#if EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_ONPING "onping"
#endif
#if EVM_USE_MODULE_MQTT || EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_ONPINGRESP "onpingresp"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_ONPUBREC "onpubrec"
#define IOT_MAGIC_STRING_ONPUBREL "onpubrel"
#endif
#define IOT_MAGIC_STRING_ONREAD "onread"
#define IOT_MAGIC_STRING_ONSOCKET "onSocket"
#define IOT_MAGIC_STRING_ONTIMEOUT "onTimeout"
#define IOT_MAGIC_STRING__ONUNCAUGHTEXCEPTION "_onUncaughtException"
#if EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_ONWRITE "onwrite"
#endif
#define IOT_MAGIC_STRING_ONWRITABLE "onWritable"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_OPENDRAIN_U "OPENDRAIN"
#endif
#define IOT_MAGIC_STRING_OPEN "open"
#define IOT_MAGIC_STRING_EXISTS "exists"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_OUT_U "OUT"
#endif
#define IOT_MAGIC_STRING_OWNER "owner"
#if EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_PARSEHANDSHAKEDATA "parseHandshakeData"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_PASSWORD "password"
#endif
#define IOT_MAGIC_STRING_PAUSE "pause"
#define IOT_MAGIC_STRING_PERIOD "period"
#define IOT_MAGIC_STRING_PID "pid"
#define IOT_MAGIC_STRING_PIN "pin"
#if EVM_USE_MODULE_MQTT || EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_PING "ping"
#endif
#define IOT_MAGIC_STRING_PLATFORM "platform"
#if EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_PONG "pong"
#endif
#define IOT_MAGIC_STRING_PORT "port"
#if EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_PREPAREHANDSHAKE "prepareHandshake"
#endif
#define IOT_MAGIC_STRING_PRIVATE "_private"
#define IOT_MAGIC_STRING_PROTOTYPE "prototype"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_PUBLISH "publish"
#endif
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_PULLDOWN_U "PULLDOWN"
#define IOT_MAGIC_STRING_PULLUP_U "PULLUP"
#define IOT_MAGIC_STRING_PUSHPULL_U "PUSHPULL"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_QOS "qos"
#endif
#define IOT_MAGIC_STRING_READDIR "readdir"
#define IOT_MAGIC_STRING_READ "read"
#define IOT_MAGIC_STRING_READSOURCE "readSource"
#define IOT_MAGIC_STRING_READSTART "readStart"
#define IOT_MAGIC_STRING_READSYNC "readSync"
#define IOT_MAGIC_STRING_READUINT8 "readUInt8"
#if EVM_USE_MODULE_DGRAM
#define IOT_MAGIC_STRING_RECVSTART "recvStart"
#define IOT_MAGIC_STRING_RECVSTOP "recvStop"
#endif
#define IOT_MAGIC_STRING_REF "ref"
#if EVM_USE_MODULE_TLS || EVM_USE_MODULE_HTTPS
#define IOT_MAGIC_STRING_REJECTUNAUTHORIZED "rejectUnauthorized"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_REMAINING "remaining"
#endif
#define IOT_MAGIC_STRING_RENAME "rename"
#define IOT_MAGIC_STRING_REQUEST_U "REQUEST"
#define IOT_MAGIC_STRING_RESPONSE_U "RESPONSE"
#define IOT_MAGIC_STRING_RESUME "resume"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_RETAIN "retain"
#endif
#define IOT_MAGIC_STRING__REUSEADDR "_reuseAddr"
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_RISING_U "RISING"
#endif
#define IOT_MAGIC_STRING_RMDIR "rmdir"
#if EVM_USE_MODULE_CRYPTO
#define IOT_MAGIC_STRING_RSAVERIFY "rsaVerify"
#endif
#define IOT_MAGIC_STRING_SEND "send"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_SENDACK "sendAck"
#endif
#define IOT_MAGIC_STRING_SENDREQUEST "sendRequest"
#if EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_SERVERNAME "servername"
#endif
#if EVM_USE_MODULE_I2C
#define IOT_MAGIC_STRING_SETADDRESS "setAddress"
#endif
#if EVM_USE_MODULE_UDP
#define IOT_MAGIC_STRING_CONFIGURE "configure"
#endif
#if EVM_USE_MODULE_GPIO
#define IOT_MAGIC_STRING_SETDIRECTIONSYNC "setDirectionSync"
#endif
#if EVM_USE_MODULE_PWM
#define IOT_MAGIC_STRING_SETDUTYCYCLE "setDutyCycle"
#define IOT_MAGIC_STRING_SETDUTYCYCLESYNC "setDutyCycleSync"
#define IOT_MAGIC_STRING_SETENABLE "setEnable"
#define IOT_MAGIC_STRING_SETENABLESYNC "setEnableSync"
#define IOT_MAGIC_STRING_SETFREQUENCY "setFrequency"
#define IOT_MAGIC_STRING_SETFREQUENCYSYNC "setFrequencySync"
#endif
#if EVM_USE_MODULE_BLE
#define IOT_MAGIC_STRING_SETFILTER "setFilter"
#endif
#define IOT_MAGIC_STRING_SETKEEPALIVE "setKeepAlive"
#if EVM_USE_MODULE_PWM
#define IOT_MAGIC_STRING_SETPERIOD "setPeriod"
#define IOT_MAGIC_STRING_SETPERIODSYNC "setPeriodSync"
#endif
#define IOT_MAGIC_STRING_SETTIMEOUT "setTimeout"
#if EVM_USE_MODULE_CRYPTO
#define IOT_MAGIC_STRING_SHAENCODE "shaEncode"
#endif
#define IOT_MAGIC_STRING_SHOULDKEEPALIVE "shouldkeepalive"
#define IOT_MAGIC_STRING_SHUTDOWN "shutdown"
#define IOT_MAGIC_STRING_SLICE "slice"
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_SPI "Spi"
#endif
#define IOT_MAGIC_STRING_START "start"
#define IOT_MAGIC_STRING_STAT "stat"
#define IOT_MAGIC_STRING_STATS "stats"
#define IOT_MAGIC_STRING_STATUS_MSG "status_msg"
#define IOT_MAGIC_STRING_STATUS "status"
#define IOT_MAGIC_STRING_STDERR "stderr"
#define IOT_MAGIC_STRING_STDOUT "stdout"
#define IOT_MAGIC_STRING_STOP "stop"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_SUBSCRIBE "subscribe"
#endif
#if EVM_USE_MODULE_TLS
#define IOT_MAGIC_STRING_TLSSOCKET "TLSSocket"
#define IOT_MAGIC_STRING_TLSCONTEXT "TlsContext"
#define IOT_MAGIC_STRING_TLSINIT "TlsInit"
#endif
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_TOPIC "topic"
#endif
#define IOT_MAGIC_STRING_TOSTRING "toString"
#if EVM_USE_MODULE_SPI
#define IOT_MAGIC_STRING_TRANSFER "transfer"
#define IOT_MAGIC_STRING_TRANSFERSYNC "transferSync"
#endif
#define IOT_MAGIC_STRING_UNLINK "unlink"
#define IOT_MAGIC_STRING_UNREF "unref"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_UNSUBSCRIBE "unsubscribe"
#endif
#define IOT_MAGIC_STRING_UPGRADE "upgrade"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_USERNAME "username"
#endif
#define IOT_MAGIC_STRING_URL "url"
#define IOT_MAGIC_STRING_VERSION "version"
#if EVM_USE_MODULE_MQTT
#define IOT_MAGIC_STRING_WILL "will"
#endif
#define IOT_MAGIC_STRING_WRITEUINT8 "writeUInt8"
#define IOT_MAGIC_STRING_WRITE "write"
#define IOT_MAGIC_STRING_WRITEDECODE "writeDecode"
#define IOT_MAGIC_STRING_WRITESYNC "writeSync"
#if EVM_USE_MODULE_HTTPS
#define IOT_MAGIC_STRING__WRITE "_write"
#endif
#if EVM_USE_MODULE_WEBSOCKET
#define IOT_MAGIC_STRING_WSINIT "wsInit"
#define IOT_MAGIC_STRING_WSRECEIVE "wsReceive"
#define IOT_MAGIC_STRING_WSRECEIVEHANDSHAKEDATA "ReceiveHandshakeData"
#endif
#if EVM_USE_MODULE_BRIDGE
#define IOT_MAGIC_STRING_MODULE_NAME "MODULE_NAME"
#endif
#if EVM_USE_MODULE_TIZEN
#define IOT_MAGIC_STRING_TIZEN "tizen"
#define IOT_MAGIC_STRING_APP_CONTROL "appControl"
#endif
#if EVM_USE_MODULE_NAPI
#define IOT_MAGIC_STRING_ERROR "Error"
#endif


#define EVM_GPIO_DIRECTION_IN   0
#define EVM_GPIO_DIRECTION_OUT  1
#define EVM_GPIO_MODE_NONE      0
#define EVM_GPIO_MODE_PULLUP    1
#define EVM_GPIO_MODE_PULLDOWN  2
#define EVM_GPIO_MODE_FLOAT     3
#define EVM_GPIO_MODE_PUSHPULL  4
#define EVM_GPIO_MODE_OPENDRAIN 5
#define EVM_GPIO_EDGE_NONE      0
#define EVM_GPIO_EDGE_RISING    1
#define EVM_GPIO_EDGE_FALLING   2
#define EVM_GPIO_EDGE_BOTH      3

#define EVM_TIMER_PERIOD        0
#define EVM_TIMER_ONE_SHOT      1

#ifdef __linux
#define EVM_HEAP_SIZE (500 * 1024)
#define EVM_STACK_SIZE (50 * 1024)
#else
#define EVM_HEAP_SIZE (50 * 1024)
#define EVM_STACK_SIZE (5 * 1024)
#endif
#define EVM_MODULE_REGISTRY_SIZE 20

#ifdef EVM_USE_MODULE_ADC
extern void evm_module_adc(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_GPIO
extern void evm_module_gpio(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_TIMER
extern void evm_module_timers(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_I2C
extern void evm_module_i2c(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_UART
extern void evm_module_uart(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_FS
extern void evm_module_fs(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_UDP
extern evm_err_t evm_module_udp(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_NET
extern evm_err_t evm_module_net(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_EVENT
typedef void (*event_handler) (evm_t *e, void* ptr);
typedef struct evm_eventbus_t{
    event_handler handler;
    void* ptr;
} evm_eventbus_t;
extern evm_err_t evm_module_events(evm_t *e);
extern void evm_eventbus_init(void);
extern int evm_eventbus_set(evm_eventbus_t *msg);
extern int evm_eventbus_get(evm_eventbus_t *msg);
#endif

#ifdef EVM_USE_MODULE_DNS
extern evm_err_t evm_module_dns(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_BUFFER
extern evm_err_t evm_module_buffer(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_ASSERT
extern evm_err_t evm_module_assert(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_CFFI
typedef union  {
    void *p; 
    char *s; 
    double f64;
    float f32; 
    int32_t i32; 
    int64_t i64;
} evm_cffi_val_t;
extern void evm_cffi_exec_param(evm_t *e, evm_cffi_val_t *cffi_vals, const char *signature, int argc, evm_val_t *v);
extern evm_val_t evm_cffi_exec_ret(evm_t *e, evm_cffi_val_t cffi_val, const char *signature);
#endif

#ifdef EVM_USE_MODULE_LIBC
void evm_module_libc(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_WLAN
void evm_module_wlan(evm_t *e);
#endif

#ifdef EVM_USE_MODULE_REPL
void evm_run_repl(evm_t *e);
#endif

extern void evm_main(char *filename);
extern void evm_loop();

extern int evm_module_registry_add(evm_t *e, evm_val_t v);
extern evm_val_t evm_module_registry_get(evm_t *e, int id);
extern void evm_module_registry_remove(evm_t *e, int id);
extern void evm_module_next_tick(evm_t *e, int argc, evm_val_t *v);
extern evm_err_t evm_module_event_add_listener(evm_t *e, evm_val_t pthis, const char *type, evm_val_t listener);
extern void evm_module_event_remove_listener(evm_t *e, evm_val_t pthis, const char *type);
extern void evm_module_event_emit (evm_t *e, evm_val_t pthis, const char *type, int argc, evm_val_t *v);
void evm_module_init(evm_t *env);
extern evm_t *evm_runtime(void);

extern void *evm_adc_open(evm_t *e, evm_val_t obj);
extern int evm_adc_read(evm_t *e, void *dev);
extern void evm_adc_close(evm_t *e, void *dev);
extern void evm_adc_destroy(evm_t *e, void *dev);

extern void *evm_gpio_open(evm_t *e, evm_val_t obj);
extern void evm_gpio_set_direction(evm_t *e, void *dev, int value);
extern void evm_gpio_write(evm_t *e, void *dev, int value);
extern int evm_gpio_read(evm_t *e, void *dev);
extern void evm_gpio_close(evm_t *e, void *dev);
extern void evm_gpio_destroy(evm_t *e, void *dev);

extern void *evm_i2c_open(evm_t *e, evm_val_t obj);
extern void evm_i2c_read(evm_t *e, void *dev, void *buf, int size);
extern void evm_i2c_write(evm_t *e, void *dev, void *buf, int size);
extern void evm_i2c_close(evm_t *e, void *dev);
extern void evm_i2c_destroy(evm_t *e, void *dev);

extern void *evm_timer_open(evm_t *e, evm_val_t cb, int tick, int flag);
extern void evm_timer_destroy(evm_t *e, void *dev);

extern void *evm_uart_open(evm_t *e, evm_val_t obj);
extern int evm_uart_write(evm_t *e, void *dev, void *buffer, int size);
extern int evm_uart_read(evm_t *e, void *dev, void *buf, int size);
extern void evm_uart_close(evm_t *e, void *dev);
extern void evm_uart_destroy(evm_t *e, void *dev);

extern void evm_wlan_connect(evm_t *e, char *ssid, char *pwd);
extern void evm_wlan_disconnect(evm_t *e);
extern evm_val_t evm_wlan_scan(evm_t *e);
extern int evm_wlan_is_connectd(evm_t *e);
extern void evm_wlan_init(evm_t *e);

extern void evm_repl_init(evm_t *e);
extern void evm_repl_tty_write(int n, char *c);
extern char evm_repl_tty_read(evm_t *e);

#define DBGLEV_ERR 1
#define DBGLEV_WARN 2
#define DBGLEV_INFO 3

typedef int (*iot_console_out_t)(int level, const char* format, ...);
extern iot_console_out_t iot_console_out;
extern void iot_set_console_out(iot_console_out_t output);

#ifdef CONFIG_EVM_DEBUG_LOG


extern int iot_debug_level;
extern FILE* iot_log_stream;
extern const char* iot_debug_prefix[4];

#include <stdio.h>
#define DLOG_PRINT(lvl, ...)                                   \
  fprintf(iot_log_stream, "[%s] ", iot_debug_prefix[lvl]); \
  fprintf(iot_log_stream, __VA_ARGS__);                      \
  fprintf(iot_log_stream, "\n");                             \
  fflush(iot_log_stream);

#define IOTJS_DLOG(lvl, ...)                                        \
  do {                                                              \
    if (0 <= lvl && lvl <= iot_debug_level && iot_log_stream) { \
      if (iot_console_out) {                                      \
        iot_console_out(lvl, __VA_ARGS__);                        \
      } else {                                                      \
        DLOG_PRINT(lvl, __VA_ARGS__)                                \
      }                                                             \
    }                                                               \
  } while (0)
#define DLOG(...) IOTJS_DLOG(DBGLEV_ERR, __VA_ARGS__)
#define DDLOG(...) IOTJS_DLOG(DBGLEV_WARN, __VA_ARGS__)
#define DDDLOG(...) IOTJS_DLOG(DBGLEV_INFO, __VA_ARGS__)

/*
  Use DLOG for errors, default you will see them
  Use DDLOG for warnings, set iotjs_debug_level=2 to see them
  USE DDDLOG for information, set iotjs_debug_level=3 to see them
*/

#else /* !ENABLE_DEBUG_LOG */

#define IOTJS_DLOG(...)
#define DLOG(...)
#define DDLOG(...)
#define DDDLOG(...)

#endif /* ENABLE_DEBUG_LOG */

#ifdef __cplusplus
}
#endif

char* evm_buffer_allocate_from_number_array(evm_t *e, size_t size, const evm_val_t array);

#endif
