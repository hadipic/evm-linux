#include "evm_module.h"
#include "evm_port_msgbus.h"

#include "tls_client.h"
#include "sys/socket.h"
#include "netdb.h"

#include "mbedtls/ssl.h"
#include "mbedtls/ssl_internal.h"
#include "mbedtls/compat-1.3.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#if defined (__linux__)
#include <unistd.h>
#endif

#define closesocket close

#include "FreeRTOS.h"
#include "task.h"

#define SOCKET_DEFAULT_TIMEO        6
#define EVENT_CONNECTED     1
#define EVENT_DISCONNECTED  2
#define EVENT_RECV          3
#define EVENT_CLOSE         4
#define EVENT_ERROR         5

#define SOCKET_FRAME_SIZE   2048
#define SOCKET_THREAD_PRIO  10

struct ssl_client {
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config config;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    int fd;
};

typedef struct _socket_client_t {
    char host[128];
    int port;
    int is_https;
    int id;
    evm_val_t obj;
    evm_val_t cb_close;
    evm_val_t cb_recv;
    evm_val_t cb_connected;
    evm_val_t cb_disconnected;
    evm_val_t cb_error;
    TaskHandle_t tid;
    int rx_buf_size;
    int rx_len;
    uint8_t *rx_buf;
    int tx_len;
    uint8_t *tx_buf;
    MbedTLSSession * tls_session;
} _socket_client_t;

#define RESPONSE_BUFSZ       4096

static int socket_open_tls(_socket_client_t *client) {
    client->tls_session = (MbedTLSSession*)evm_malloc(sizeof(MbedTLSSession));
    if( !client->tls_session ) {
        evm_print("cannot malloc memory(ssl_client_init)\n");
        return 0;
    }
    memset(client->tls_session, 0, sizeof(MbedTLSSession));
    char *host = client->host;
    int host_len = strlen(host);
    char port[10];
    sprintf(port, "%d", client->port);
    client->tls_session->host = evm_malloc(host_len + 1);
    memcpy(client->tls_session->host, host, host_len);
    client->tls_session->host[host_len] = 0;

    client->tls_session->port = evm_malloc(strlen(port));
    memcpy(client->tls_session->port, port, strlen(port));
    client->tls_session->port[strlen(port)] = 0;

    client->tls_session->buffer_len = RESPONSE_BUFSZ;
    client->tls_session->buffer = evm_malloc(client->tls_session->buffer_len);
    if(client->tls_session->buffer == NULL)
    {
        evm_print("no memory for tls_session buffer!");
        return 0;
    }

    int tls_ret = mbedtls_client_init(client->tls_session, (void *)"tlsclient", strlen("tlsclient"));
    if( tls_ret == 0 ) {
        evm_print("initialize https client failed return: -0x%x.", -tls_ret);
        return 0;
    }
    return 1;
}

static int _socket_handler(evm_t *e, int type, void* ptr) {
    _socket_client_t *client = ptr;
    switch (type) {
    case EVENT_CLOSE:{
        evm_call_free(e, client->cb_close, EVM_UNDEFINED, 1, &client->obj);
        break;
    }
    case EVENT_CONNECTED:{
        evm_call_free(e, client->cb_connected, EVM_UNDEFINED, 1, &client->obj);
        break;
    }
    case EVENT_DISCONNECTED:{
        evm_call_free(e, client->cb_disconnected, EVM_UNDEFINED, 1, &client->obj);
        break;
    }
    case EVENT_RECV:{
        evm_val_t args[2];
        args[0] = client->obj;
        args[1] = evm_buffer_create(e, client->rx_buf, client->rx_len);
        evm_free(client->rx_buf);
        evm_free(client);
        evm_call_free(e, client->cb_recv, EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[1]);
        break;
    }
    }
}

static void socket_tls_thread_entry(void *param) {
    _socket_client_t *client = param;
    int bytes = mbedtls_client_write(client->tls_session, client->tx_buf, client->tx_len);
    if( bytes <= 0 ) {
        rtos_msg_t msg;
        msg.handler = _socket_handler;
        msg.ptr = client;
        msg.type = EVENT_ERROR;
        evm_port_msgbus_put(&msg, 1);
        vTaskDelete(client->tid);
        return;
    }
    while(1) {
        int32_t length = mbedtls_client_read(client->tls_session, client->rx_buf, SOCKET_FRAME_SIZE);
        if (length > 0) {
            if (client->rx_buf) {
                _socket_client_t *local_client = evm_malloc(sizeof (_socket_client_t));
                if( !local_client ) {
                    vTaskDelete(client->tid);
                    return;
                }
                memcpy(local_client, client, sizeof (_socket_client_t));
                local_client->rx_len = length;
                local_client->rx_buf = evm_malloc(length);
                if( !client->rx_buf ) {
                    evm_free(local_client);
                    rtos_msg_t msg;
                    msg.handler = _socket_handler;
                    msg.ptr = client;
                    msg.type = EVENT_ERROR;
                    evm_port_msgbus_put(&msg, 1);
                    vTaskDelete(client->tid);
                    return;
                }
                memcpy(local_client->rx_buf, client->rx_buf, length);
                rtos_msg_t msg;
                msg.handler = _socket_handler;
                msg.ptr = local_client;
                msg.type = EVENT_RECV;
                evm_port_msgbus_put(&msg, 1);
            }
        } else {
            break;
        }
    }
    vTaskDelete(client->tid);
}

//close(socket);
EVM_FUNCTION(socket_close){
    EVM_EPCV;
    _socket_client_t *client = (_socket_client_t *)evm_object_get_user_data(e, v[0]);
    if( !client )
        EVM_RETURN(EVM_UNDEFINED);
    if( client->is_https ) {
        mbedtls_client_close(client->tls_session);
        rtos_msg_t msg;
        msg.handler = _socket_handler;
        msg.ptr = client;
        msg.type = EVENT_CLOSE;
        evm_port_msgbus_put(&msg, 1);
    } else {
        shutdown(client->id, SHUT_RDWR);
        closesocket(client->id);
    }
    EVM_RETURN(EVM_UNDEFINED);
}
//write(socket, buffer|string, len)
EVM_FUNCTION(socket_write){
    EVM_EPCV;
    ssize_t bytes = 0;
    int is_str = 0;
    _socket_client_t *client = (_socket_client_t *)evm_object_get_user_data(e, v[0]);
    if( !client )
        EVM_RETURN_VAL(evm_mk_number(e, 0));

    if( argc < 1 )
        EVM_RETURN_VAL(evm_mk_number(e, 0));

    uint8_t *buff = NULL;
    int len = 0;
    if( argc > 1 && evm_is_number(e, v[2]))
        len = (size_t)evm_2_integer(e, v[2]);

    if( evm_is_buffer(e, v[1]) ){
        buff = evm_buffer_addr(e, v[1]);
        int local_len = evm_buffer_len(e, v[1]);
        if( len == 0 )
            len = local_len;
        else
            len = len < local_len ? len:local_len;
    } else if( evm_is_string(e, v[1]) ){
        is_str = 1;
        buff = (uint8_t*)evm_2_string(e, v[1]);
        int local_len = evm_string_len(e, v[1]);
        if( len == 0 )
            len = local_len;
        else
            len = len < local_len ? len:local_len;
    }
    if (client->is_https)
    {
        client->tx_len = len;
        client->tx_buf = evm_malloc(len);
        memcpy(client->tx_buf, buff, len);
        if( is_str )
            evm_string_free(e, (char*)buff);

        if( !xTaskCreate( socket_tls_thread_entry, "socket_thread", 1024, client, 10, &client->tid ) )
        {
            closesocket(client->id);
            rtos_msg_t msg;
            msg.handler = _socket_handler;
            msg.ptr = client;
            msg.type = EVENT_CLOSE;
            evm_port_msgbus_put(&msg, 1);
            return EVM_UNDEFINED;
        }
        EVM_RETURN_VAL(evm_mk_number(e, bytes));
    }
    bytes = send(client->id, buff, len, 0);
    if( is_str )
        evm_string_free(e, (char*)buff);
    EVM_RETURN_VAL(evm_mk_number(e, bytes));
}
//read(socket, size)
EVM_FUNCTION(socket_read) {
    EVM_EPCV;
    _socket_client_t *client = (_socket_client_t *)evm_object_get_user_data(e, v[0]);
    EVM_ASSERT(client);

    if( argc < 2 || !evm_is_number(e, v[1]) )
        EVM_RETURN_VAL(evm_mk_number(e, 0));

    int size = evm_2_integer(e, v[0]);
    uint8_t *addr = evm_malloc(size);
    EVM_ASSERT(addr);
    if (client->is_https)
    {
        ssize_t res = mbedtls_client_read(client->tls_session, addr, size);
        evm_free(addr);
        EVM_RETURN_VAL(evm_mk_number(e, res));
    }
    ssize_t res = recv(client->id, addr, size, 0);
    evm_free(addr);
    EVM_RETURN_VAL(evm_mk_number(e, res));
}
//on(socket, event, callback)
EVM_FUNCTION(socket_on) {
    EVM_EPCV;
    _socket_client_t *client = (_socket_client_t *)evm_object_get_user_data(e, v[0]);
    EVM_ASSERT(client);

    if( argc < 3 || !evm_is_string(e, v[1]) || !evm_is_callable(e, v[2])) {\
        return EVM_UNDEFINED;
    }
    char *event = evm_2_string(e, v[0]);
    if( !strcmp(event, "recv") ) {
        client->cb_recv = evm_val_duplicate(e, v[2]);
    } else if( !strcmp(event, "connected") ) {
        client->cb_connected = evm_val_duplicate(e, v[2]);
    } else if( !strcmp(event, "disconnected") ) {
        client->cb_disconnected = evm_val_duplicate(e, v[2]);
    } else if( !strcmp(event, "close") ) {
        client->cb_close = evm_val_duplicate(e, v[2]);
    } else if( !strcmp(event, "error") ) {
        client->cb_error = evm_val_duplicate(e, v[2]);
    }
    evm_string_free(e, event);
    return EVM_UNDEFINED;
}

static void client_destory(_socket_client_t *thiz)
{
    if (thiz == NULL)
    {
        evm_print("netclient del : param is NULL, delete failed");
        return;
    }

    evm_print("netc[%ld] destory begin", thiz->id);

    if (thiz->id != -1) {
        closesocket(thiz->id);
    }
}

static void client_clean(_socket_client_t *client) {
    if( client->rx_buf )
        evm_free(client->rx_buf);
    if( client->tx_buf )
        evm_free(client->tx_buf);
    evm_free(client);
}

static int32_t socket_init(_socket_client_t *client) {
    int ret;
    struct timeval timeout;
    timeout.tv_sec = SOCKET_DEFAULT_TIMEO;
    timeout.tv_usec = 0;
    int socket_handle;

    evm_print("host: %s, port: %d \n", client->host, client->port);

    if( client->is_https ) {
        if(socket_open_tls(client) < 0)
        {
            evm_print("connect failed, https client open URI(%s) failed!", client->host);
            return 0;
        }
    }

    if( client->tls_session ) {
        int tls_ret = 0;

        if ((tls_ret = mbedtls_client_context(client->tls_session)) < 0)
        {
            evm_print("connect failed, https client context");
            return 0;
        }

        if ((tls_ret = mbedtls_client_connect(client->tls_session)) < 0)
        {
            evm_print("connect failed, https client connect");
            return 0;
        }

        socket_handle = client->tls_session->server_fd.fd;

        /* set recv timeout option */
        setsockopt(socket_handle, SOL_SOCKET, SO_RCVTIMEO, (void*) &timeout,
                sizeof(timeout));
        setsockopt(socket_handle, SOL_SOCKET, SO_SNDTIMEO, (void*) &timeout,
                sizeof(timeout));

        client->id = socket_handle;

        return 1;
    } else {

        struct sockaddr_in sock_addr;
        memset(&sock_addr, 0, sizeof(sock_addr));

        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = inet_addr(client->host);  
        sock_addr.sin_port = htons(client->port);  

        socket_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if( socket_handle == -1 ){
            evm_print("socket init : socket create failed\n");
            client_clean(client);
            return 0;
        }

        client->id = socket_handle;

        

        setsockopt(client->id, SOL_SOCKET, SO_RCVTIMEO, (void *) &timeout,
                   sizeof(timeout));
        setsockopt(client->id, SOL_SOCKET, SO_SNDTIMEO, (void *) &timeout,
                   sizeof(timeout));

        int32_t res = connect(socket_handle, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
        if (res == -1)
        {
            evm_print("connect failed\n");
            evm_free(client);
            return 0;
        }
        evm_print("connect successfully");
        return 1;
    }
    return 1;
}

static void socket_thread_entry(void *param) {
    _socket_client_t *client = (_socket_client_t *)param;

    if( socket_init(client) == 0 ) {
        vTaskDelete(client->tid);
        evm_print("Failed to create socket");
        return;
    }

    rtos_msg_t msg;
    msg.handler = _socket_handler;
    msg.ptr = client;
    msg.type = EVENT_CONNECTED;
    evm_port_msgbus_put(&msg, 1);

    while(1) {
        ssize_t length = recv(client->id, client->rx_buf, SOCKET_FRAME_SIZE, 0);
        if( length > 0 ){
            _socket_client_t *local_client = evm_malloc(sizeof (_socket_client_t));
            if( !local_client ) {
                vTaskDelete(client->tid);
                return; 
            }
            memcpy(local_client, client, sizeof (_socket_client_t));
            local_client->rx_len = length;
            local_client->rx_buf = evm_malloc(length);
            if( !client->rx_buf ) {
                evm_free(local_client);
                vTaskDelete(client->tid);
                return;
            }
            memcpy(local_client->rx_buf, client->rx_buf, length);
            rtos_msg_t msg;
            msg.handler = _socket_handler;
            msg.ptr = local_client;
            msg.type = EVENT_RECV;
            evm_port_msgbus_put(&msg, 1);
        } else  {
            break;
        }
    }

    msg.handler = _socket_handler;
    msg.ptr = client;
    msg.type = EVENT_RECV;
    evm_port_msgbus_put(&msg, 1);
    vTaskDelete(client->tid);
}
//destroy(socket)
EVM_FUNCTION(socket_destroy) {
    EVM_EPCV;
    _socket_client_t *client = (_socket_client_t *)evm_object_get_user_data(e, v[0]);
    EVM_ASSERT(client);
    evm_val_free(e, client->obj);
    evm_val_free(e, client->cb_close);
    evm_val_free(e, client->cb_connected);
    evm_val_free(e, client->cb_error);
    evm_val_free(e, client->cb_disconnected);
    evm_val_free(e, client->cb_recv);
    client_clean(client);
    return EVM_UNDEFINED;
}

//connect(address, port, [rx_buf_size, tx_buf_size])
EVM_FUNCTION(socket_connect) {
    EVM_EPCV;
    if( argc < 1 || !evm_is_object(e, v[0]) )
        return EVM_UNDEFINED;

    _socket_client_t *client = evm_malloc(sizeof(_socket_client_t));
    EVM_ASSERT(client);
    memset(client, 0, sizeof (_socket_client_t));
    client->tls_session = NULL;
    client->obj = EVM_UNDEFINED;
    client->id = -1;
    client->cb_recv = EVM_UNDEFINED;
    client->cb_connected = EVM_UNDEFINED;
    client->cb_disconnected = EVM_UNDEFINED;
    client->cb_close = EVM_UNDEFINED;
    client->cb_error = EVM_UNDEFINED;

    evm_val_t hostV = evm_prop_get(e, v[0], "host");
    evm_val_t tlsV = evm_prop_get(e, v[0], "tls");
    evm_val_t portV = evm_prop_get(e, v[0], "port");

    char *host = evm_2_string(e, hostV);
    memcpy(client->host, host, strlen(host));
    client->port = evm_2_integer(e, portV);
    client->is_https = evm_2_boolean(e, tlsV);
    evm_string_free(e, host);
    evm_val_free(e, hostV);
    evm_val_free(e, tlsV);
    evm_val_free(e, portV);

    client->rx_buf = evm_malloc(SOCKET_FRAME_SIZE);
    EVM_ASSERT(client->rx_buf);
    memset(client->rx_buf, 0, SOCKET_FRAME_SIZE);

    client->tx_buf = evm_malloc(SOCKET_FRAME_SIZE);
    EVM_ASSERT(client->tx_buf);
    memset(client->tx_buf, 0, SOCKET_FRAME_SIZE);

    evm_val_t obj = evm_object_create_user_data(e, client);
    if( client->is_https == 0 ) {
        if( !xTaskCreate( socket_thread_entry, "socket_thread", 1024, client, SOCKET_THREAD_PRIO, &client->tid ) )
        {
            closesocket(client->id);
            client_clean(client);
            return EVM_UNDEFINED;
        }
    }
    client->obj = evm_val_duplicate(e, obj);
    return obj;
}

//lookup(host, opt)
EVM_FUNCTION(socket_lookup) {
    EVM_EPCV;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;
    char buf[128];
    struct sockaddr_in  *ipv4;
    struct sockaddr_in6 *ipv6;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ALL;
    hints.ai_protocol = IPPROTO_TCP;

    char *host = evm_2_string(e, v[0]);
    char *opt = evm_2_string(e, v[1]);
    s = getaddrinfo(host, opt, &hints, &result);
    evm_string_free(e, host);
    evm_string_free(e, opt);
    if (s != 0) {
        return EVM_UNDEFINED;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        switch (rp->ai_family) {
        case AF_INET:
            ipv4 = (struct sockaddr_in *)rp->ai_addr;
            inet_ntop(rp->ai_family, &ipv4->sin_addr, buf, sizeof(buf));
            break;
        }
    }

    /* No longer needed */
    freeaddrinfo(result);

    return evm_string_create(e, buf);
}

void evue_module_net(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "connect", evm_mk_native(e, socket_connect, "connect", EVM_VARARGS));
    evm_prop_set(e, obj, "lookup", evm_mk_native(e, socket_lookup, "lookup", EVM_VARARGS));
    evm_module_add(e, "@native.net", obj);
    evm_val_free(e, obj);
}
