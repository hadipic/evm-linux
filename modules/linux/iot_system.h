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
#ifndef IOT_SYSTEM_H
#define IOT_SYSTEM_H

#include "evm_module.h"
#include "uv.h"
#include <unistd.h>
#include <stdbool.h>

#define DEVICE_IO_NAME_LEN 64
#define DEVICE_IO_PATH_BUFFER_SIZE 64
#define DEVICE_IO_PIN_BUFFER_SIZE 10
#define DEVICE_IO_WRITE_BUFFER_SIZE 512


#define IOT_MAGIC_STRING_0 "0"
#define IOT_MAGIC_STRING_1 "1"
#define IOT_MAGIC_STRING_2 "2"
#define IOT_MAGIC_STRING_3 "3"

#define IOT_MAGIC_STRING_CREATE "create"

#define IOT_MAGIC_STRING_ABORT "abort"
#define IOT_MAGIC_STRING_ACKTYPE "type"

#define IOT_MAGIC_STRING_ADC "Adc"
#define IOT_MAGIC_STRING_ADDHEADER "addHeader"

#define IOT_MAGIC_STRING_ADDMEMBERSHIP "addMembership"

#define IOT_MAGIC_STRING_ADDRESS "address"
#define IOT_MAGIC_STRING_ARCH "arch"
#define IOT_MAGIC_STRING_ARGV "argv"
#define IOT_MAGIC_STRING_BASE64 "base64"

#define IOT_MAGIC_STRING_BASE64ENCODE "base64Encode"


#define IOT_MAGIC_STRING_BAUDRATE "baudRate"

#define IOT_MAGIC_STRING_BIND "bind"

#define IOT_MAGIC_STRING_BINDCONTROL "bindControl"

#define IOT_MAGIC_STRING_BINDING "binding"

#define IOT_MAGIC_STRING_BINDRAW "bindRaw"
#define IOT_MAGIC_STRING_BINDUSER "bindUser"

#define IOT_MAGIC_STRING_BITORDER "bitOrder"
#define IOT_MAGIC_STRING_BITORDER_U "BITORDER"
#define IOT_MAGIC_STRING_BITSPERWORD "bitsPerWord"

#define IOT_MAGIC_STRING_BOARD "board"

#define IOT_MAGIC_STRING_BOTH_U "BOTH"

#define IOT_MAGIC_STRING_BUFFER "Buffer"
#define IOT_MAGIC_STRING_BUILTIN_MODULES "builtin_modules"

#define IOT_MAGIC_STRING_BUS "bus"

#define IOT_MAGIC_STRING_BYTELENGTH "byteLength"
#define IOT_MAGIC_STRING_BYTEPARSED "byteParsed"
#define IOT_MAGIC_STRING_FROM_ARRAYBUFFER "fromArrayBuffer"

#define IOT_MAGIC_STRING_CA "ca"
#define IOT_MAGIC_STRING_CERT "cert"

#define IOT_MAGIC_STRING_CHDIR "chdir"

#define IOT_MAGIC_STRING_CHIP "chip"

#define IOT_MAGIC_STRING_CHIPSELECT "chipSelect"
#define IOT_MAGIC_STRING_CHIPSELECT_U "CHIPSELECT"

#define IOT_MAGIC_STRING_CLIENTID "clientId"

#define IOT_MAGIC_STRING_CLOSE "close"
#define IOT_MAGIC_STRING_CLOSESYNC "closeSync"
#define IOT_MAGIC_STRING_CODE "code"
#define IOT_MAGIC_STRING_COMPARE "compare"
#define IOT_MAGIC_STRING_COMPILE "compile"
#define IOT_MAGIC_STRING_COMPILEMODULE "compileModule"
#define IOT_MAGIC_STRING_CONFIG "config"
#define IOT_MAGIC_STRING_CONNECT "connect"
#define IOT_MAGIC_STRING_COPY "copy"

#define IOT_MAGIC_STRING_CREATEREQUEST "createRequest"

#define IOT_MAGIC_STRING__CREATESTAT "_createStat"
#define IOT_MAGIC_STRING_CREATETCP "createTCP"
#define IOT_MAGIC_STRING_CWD "cwd"
#define IOT_MAGIC_STRING_DATA "data"

#define IOT_MAGIC_STRING_DATABITS "dataBits"

#define IOT_MAGIC_STRING_DEBUG "debug"

#define IOT_MAGIC_STRING_DECODEFRAME "decodeFrame"

#define IOT_MAGIC_STRING_DEVICE "device"

#define IOT_MAGIC_STRING_DIRECTION "direction"
#define IOT_MAGIC_STRING_DIRECTION_U "DIRECTION"

#define IOT_MAGIC_STRING_DISCONNECT "disconnect"

#define IOT_MAGIC_STRING_DOEXIT "doExit"

#define IOT_MAGIC_STRING_DROPMEMBERSHIP "dropMembership"

#define IOT_MAGIC_STRING_DUTYCYCLE "dutyCycle"

#define IOT_MAGIC_STRING_EDGE "edge"
#define IOT_MAGIC_STRING_EDGE_U "EDGE"

#define IOT_MAGIC_STRING_EMIT "emit"
#define IOT_MAGIC_STRING_EMITEXIT "emitExit"

#define IOT_MAGIC_STRING_END "end"

#define IOT_MAGIC_STRING_ENV "env"
#define IOT_MAGIC_STRING_ERRNAME "errname"
#define IOT_MAGIC_STRING_EXECUTE "execute"
#define IOT_MAGIC_STRING_EXITCODE "exitCode"
#define IOT_MAGIC_STRING_EXPORT "export"

#define IOT_MAGIC_STRING_FALLING_U "FALLING"

#define IOT_MAGIC_STRING_FAMILY "family"
#define IOT_MAGIC_STRING_FINISH "finish"

#define IOT_MAGIC_STRING_FINISHREQUEST "finishRequest"

#define IOT_MAGIC_STRING_FLOAT_U "FLOAT"

#define IOT_MAGIC_STRING_FSTAT "fstat"

#define IOT_MAGIC_STRING_GC "gc"

#define IOT_MAGIC_STRING_GETADDRINFO "getaddrinfo"
#define IOT_MAGIC_STRING_GETSOCKNAME "getsockname"

#define IOT_MAGIC_STRING_GPIO "Gpio"

#define IOT_MAGIC_STRING_HANDLER "handler"
#define IOT_MAGIC_STRING_HANDLETIMEOUT "handleTimeout"
#define IOT_MAGIC_STRING_HEADERS "headers"
#define IOT_MAGIC_STRING_HEX "hex"

#define IOT_MAGIC_STRING_HIGH_U "HIGH"

#define IOT_MAGIC_STRING_HOME_U "HOME"
#define IOT_MAGIC_STRING_HOST "host"
#define IOT_MAGIC_STRING_HTTPPARSER "HTTPParser"
#define IOT_MAGIC_STRING_HTTP_VERSION_MAJOR "http_major"
#define IOT_MAGIC_STRING_HTTP_VERSION_MINOR "http_minor"

#define IOT_MAGIC_STRING_IN "IN"

#define IOT_MAGIC_STRING__INCOMING "_incoming"
#define IOT_MAGIC_STRING_IPV4 "IPv4"
#define IOT_MAGIC_STRING_IPV6 "IPv6"
#define IOT_MAGIC_STRING_ISALIVEEXCEPTFOR "isAliveExceptFor"
#define IOT_MAGIC_STRING_ISDEVUP "isDevUp"
#define IOT_MAGIC_STRING_ISDIRECTORY "isDirectory"
#define IOT_MAGIC_STRING_ISFILE "isFile"

#define IOT_MAGIC_STRING_ISSERVER "isServer"


#define IOT_MAGIC_STRING_KEEPALIVE "keepalive"

#define IOT_MAGIC_STRING_KEY "key"
#define IOT_MAGIC_STRING_LENGTH "length"
#define IOT_MAGIC_STRING_LISTEN "listen"
#define IOT_MAGIC_STRING_LOOPBACK "loopback"

#define IOT_MAGIC_STRING_LSB "LSB"
#define IOT_MAGIC_STRING_MAXSPEED "maxSpeed"

#define IOT_MAGIC_STRING_MESSAGE "message"

#define IOT_MAGIC_STRING_METHOD "method"
#define IOT_MAGIC_STRING_METHODS "methods"
#define IOT_MAGIC_STRING_MKDIR "mkdir"
#define IOT_MAGIC_STRING_MODE "mode"

#define IOT_MAGIC_STRING_MODE_U "MODE"

#define IOT_MAGIC_STRING_MQTTINIT "MqttInit"
#define IOT_MAGIC_STRING_MQTTMESSAGE "MqttMessage"
#define IOT_MAGIC_STRING_MQTTRECEIVE "MqttReceive"

#define IOT_MAGIC_STRING_MSB "MSB"


#define IOT_MAGIC_STRING_NONE_U "NONE"

#define IOT_MAGIC_STRING_ONACK "onack"

#define IOT_MAGIC_STRING_ONBODY "OnBody"
#define IOT_MAGIC_STRING_ONCLOSE "onclose"
#define IOT_MAGIC_STRING_ONCLOSED "onClosed"
#define IOT_MAGIC_STRING_ONCONNECTION "onconnection"
#define IOT_MAGIC_STRING_ONDATA "onData"
#define IOT_MAGIC_STRING_ONEND "onEnd"
#define IOT_MAGIC_STRING_ONERROR "onError"

#define IOT_MAGIC_STRING_ONHANDSHAKEDONE "onhandshakedone"

#define IOT_MAGIC_STRING_ONHEADERSCOMPLETE "OnHeadersComplete"
#define IOT_MAGIC_STRING_ONHEADERS "OnHeaders"
#define IOT_MAGIC_STRING_ONMESSAGECOMPLETE "OnMessageComplete"
#define IOT_MAGIC_STRING_ONMESSAGE "onmessage"
#define IOT_MAGIC_STRING__ONNEXTTICK "_onNextTick"

#define IOT_MAGIC_STRING_ONPING "onping"

#define IOT_MAGIC_STRING_ONPINGRESP "onpingresp"

#define IOT_MAGIC_STRING_ONPUBREC "onpubrec"
#define IOT_MAGIC_STRING_ONPUBREL "onpubrel"

#define IOT_MAGIC_STRING_ONREAD "onread"
#define IOT_MAGIC_STRING_ONSOCKET "onSocket"
#define IOT_MAGIC_STRING_ONTIMEOUT "onTimeout"
#define IOT_MAGIC_STRING__ONUNCAUGHTEXCEPTION "_onUncaughtException"

#define IOT_MAGIC_STRING_ONWRITE "onwrite"

#define IOT_MAGIC_STRING_ONWRITABLE "onWritable"

#define IOT_MAGIC_STRING_OPENDRAIN_U "OPENDRAIN"

#define IOT_MAGIC_STRING_OPEN "open"

#define IOT_MAGIC_STRING_OUT_U "OUT"

#define IOT_MAGIC_STRING_OWNER "owner"

#define IOT_MAGIC_STRING_PARSEHANDSHAKEDATA "parseHandshakeData"

#define IOT_MAGIC_STRING_PASSWORD "password"

#define IOT_MAGIC_STRING_PAUSE "pause"
#define IOT_MAGIC_STRING_PERIOD "period"
#define IOT_MAGIC_STRING_PID "pid"
#define IOT_MAGIC_STRING_PIN "pin"

#define IOT_MAGIC_STRING_PING "ping"

#define IOT_MAGIC_STRING_PLATFORM "platform"

#define IOT_MAGIC_STRING_PONG "pong"

#define IOT_MAGIC_STRING_PORT "port"

#define IOT_MAGIC_STRING_PREPAREHANDSHAKE "prepareHandshake"

#define IOT_MAGIC_STRING_PRIVATE "_private"
#define IOT_MAGIC_STRING_PROTOTYPE "prototype"

#define IOT_MAGIC_STRING_PUBLISH "publish"

#define IOT_MAGIC_STRING_PULLDOWN_U "PULLDOWN"
#define IOT_MAGIC_STRING_PULLUP_U "PULLUP"
#define IOT_MAGIC_STRING_PUSHPULL_U "PUSHPULL"


#define IOT_MAGIC_STRING_QOS "qos"

#define IOT_MAGIC_STRING_READDIR "readdir"
#define IOT_MAGIC_STRING_READ "read"
#define IOT_MAGIC_STRING_READSOURCE "readSource"
#define IOT_MAGIC_STRING_READSTART "readStart"
#define IOT_MAGIC_STRING_READSYNC "readSync"
#define IOT_MAGIC_STRING_READUINT8 "readUInt8"

#define IOT_MAGIC_STRING_RECVSTART "recvStart"
#define IOT_MAGIC_STRING_RECVSTOP "recvStop"

#define IOT_MAGIC_STRING_REF "ref"

#define IOT_MAGIC_STRING_REJECTUNAUTHORIZED "rejectUnauthorized"


#define IOT_MAGIC_STRING_REMAINING "remaining"

#define IOT_MAGIC_STRING_RENAME "rename"
#define IOT_MAGIC_STRING_REQUEST_U "REQUEST"
#define IOT_MAGIC_STRING_RESPONSE_U "RESPONSE"
#define IOT_MAGIC_STRING_RESUME "resume"

#define IOT_MAGIC_STRING_RETAIN "retain"

#define IOT_MAGIC_STRING__REUSEADDR "_reuseAddr"

#define IOT_MAGIC_STRING_RISING_U "RISING"

#define IOT_MAGIC_STRING_RMDIR "rmdir"

#define IOT_MAGIC_STRING_RSAVERIFY "rsaVerify"

#define IOT_MAGIC_STRING_SEND "send"

#define IOT_MAGIC_STRING_SENDACK "sendAck"

#define IOT_MAGIC_STRING_SENDREQUEST "sendRequest"

#define IOT_MAGIC_STRING_SERVERNAME "servername"


#define IOT_MAGIC_STRING_SETADDRESS "setAddress"


#define IOT_MAGIC_STRING_CONFIGURE "configure"


#define IOT_MAGIC_STRING_SETDIRECTIONSYNC "setDirectionSync"


#define IOT_MAGIC_STRING_SETDUTYCYCLE "setDutyCycle"
#define IOT_MAGIC_STRING_SETDUTYCYCLESYNC "setDutyCycleSync"
#define IOT_MAGIC_STRING_SETENABLE "setEnable"
#define IOT_MAGIC_STRING_SETENABLESYNC "setEnableSync"
#define IOT_MAGIC_STRING_SETFREQUENCY "setFrequency"
#define IOT_MAGIC_STRING_SETFREQUENCYSYNC "setFrequencySync"


#define IOT_MAGIC_STRING_SETFILTER "setFilter"

#define IOT_MAGIC_STRING_SETKEEPALIVE "setKeepAlive"

#define IOT_MAGIC_STRING_SETPERIOD "setPeriod"
#define IOT_MAGIC_STRING_SETPERIODSYNC "setPeriodSync"

#define IOT_MAGIC_STRING_SETTIMEOUT "setTimeout"

#define IOT_MAGIC_STRING_SHAENCODE "shaEncode"

#define IOT_MAGIC_STRING_SHOULDKEEPALIVE "shouldkeepalive"
#define IOT_MAGIC_STRING_SHUTDOWN "shutdown"
#define IOT_MAGIC_STRING_SLICE "slice"

#define IOT_MAGIC_STRING_SPI "Spi"

#define IOT_MAGIC_STRING_START "start"
#define IOT_MAGIC_STRING_STAT "stat"
#define IOT_MAGIC_STRING_STATS "stats"
#define IOT_MAGIC_STRING_STATUS_MSG "status_msg"
#define IOT_MAGIC_STRING_STATUS "status"
#define IOT_MAGIC_STRING_STDERR "stderr"
#define IOT_MAGIC_STRING_STDOUT "stdout"
#define IOT_MAGIC_STRING_STOP "stop"

#define IOT_MAGIC_STRING_SUBSCRIBE "subscribe"


#define IOT_MAGIC_STRING_TLSSOCKET "TLSSocket"
#define IOT_MAGIC_STRING_TLSCONTEXT "TlsContext"
#define IOT_MAGIC_STRING_TLSINIT "TlsInit"


#define IOT_MAGIC_STRING_TOPIC "topic"

#define IOT_MAGIC_STRING_TOSTRING "toString"

#define IOT_MAGIC_STRING_TRANSFER "transfer"
#define IOT_MAGIC_STRING_TRANSFERSYNC "transferSync"

#define IOT_MAGIC_STRING_UNLINK "unlink"
#define IOT_MAGIC_STRING_UNREF "unref"

#define IOT_MAGIC_STRING_UNSUBSCRIBE "unsubscribe"

#define IOT_MAGIC_STRING_UPGRADE "upgrade"

#define IOT_MAGIC_STRING_USERNAME "username"

#define IOT_MAGIC_STRING_URL "url"
#define IOT_MAGIC_STRING_VERSION "version"

#define IOT_MAGIC_STRING_WILL "will"

#define IOT_MAGIC_STRING_WRITEUINT8 "writeUInt8"
#define IOT_MAGIC_STRING_WRITE "write"
#define IOT_MAGIC_STRING_WRITEDECODE "writeDecode"
#define IOT_MAGIC_STRING_WRITESYNC "writeSync"

#define IOT_MAGIC_STRING__WRITE "_write"

#define IOT_MAGIC_STRING_WSINIT "wsInit"
#define IOT_MAGIC_STRING_WSRECEIVE "wsReceive"
#define IOT_MAGIC_STRING_WSRECEIVEHANDSHAKEDATA "ReceiveHandshakeData"

#define IOT_MAGIC_STRING_MODULE_NAME "MODULE_NAME"



#define IOT_MAGIC_STRING_ERROR "Error"

#ifdef __cplusplus
extern "C" {
#endif

int system_check_path(const char* path);
int system_open_write_close(const char* path, const char* value);
int system_open_read_close(const char* path, char* buffer, unsigned buffer_len);
int system_device_open(const char* export_path, uint32_t value,
                         const char* exported_path,
                         const char** created_files,
                         int created_files_length);
int system_device_close(const char* export_path, uint32_t value);
void system_set_uv_loop(uv_loop_t *loop);
uv_loop_t *system_get_uv_loop();
void system_loop();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
