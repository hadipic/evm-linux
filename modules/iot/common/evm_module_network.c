#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_NET
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include "netdb.h"

typedef struct net_socket_t {
    struct sockaddr_in addr;
    int sockfd;
} net_socket_t;

//server.close()
static evm_val_t evm_module_net_server_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *server_sock = evm_object_get_user_data(e, p);
    if( !server_sock )
        return EVM_UNDEFINED;
    close(server_sock->sockfd);
    return EVM_UNDEFINED;
}

//server.listen(port[, host][, backlog])
//server.listen(options)
static evm_val_t evm_module_net_server_listen(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 1 || !evm_is_integer(e, v[0]) ) {
        return EVM_UNDEFINED;
    }

    net_socket_t *server_sock = evm_object_get_user_data(e, p);
    if( !server_sock )
        return EVM_UNDEFINED;

    server_sock->addr.sin_family = AF_INET;
    server_sock->addr.sin_port = htons(evm_2_integer(e, v[0]));
    server_sock->addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(server_sock->sockfd, (struct sockaddr*)&server_sock->addr, sizeof(struct sockaddr_in)) < 0 )
    {
        printf("Failed to bind server socket\r\n");
        close(server_sock->sockfd);
        return EVM_UNDEFINED;
    }

    if( listen(server_sock->sockfd, 1) < 0 ) {
        printf("Failed to listen\r\n");
        close(server_sock->sockfd);
    }

    return EVM_UNDEFINED;
}

//socket.connect(options)
//socket.connect(port[, host])
static evm_val_t evm_module_net_socket_connect(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock = evm_object_get_user_data(e, p);
    if( !sock )
        return EVM_UNDEFINED;

    if( argc > 2 && evm_is_integer(e, v[0]) && evm_is_string(e, v[1]) ) {
        sock->addr.sin_family = AF_INET;
        sock->addr.sin_port = htons(evm_2_integer(e, v[0]));
        sock->addr.sin_addr.s_addr = inet_addr(evm_2_string(e, v[1]));
        memset(&(sock->addr.sin_zero), 0, sizeof(sock->addr.sin_zero));
    } else {
        return evm_mk_boolean(e, 0);
    }

    if ((sock->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return evm_mk_boolean(e, 0);
    }

    if ( connect(sock->sockfd, (struct sockaddr *)&(sock->addr), sizeof(struct sockaddr)) == -1 ) {
        close(sock->sockfd);
        return evm_mk_boolean(e, 0);
    }

    return evm_mk_boolean(e, 1);
}

//socket.destroy()
static evm_val_t evm_module_net_socket_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock = evm_object_get_user_data(e, p);
    if( !sock )
        return EVM_UNDEFINED;
    close(sock->sockfd);
    free(sock);
    return EVM_UNDEFINED;
}

//socket.end([data][, callback])
static evm_val_t evm_module_net_socket_end(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock = evm_object_get_user_data(e, p);
    if( !sock )
        return EVM_UNDEFINED;
    if( argc > 0 ) {
        if( evm_is_string(e, v[0]) ) {
            send(sock->sockfd, evm_2_string(e, v[0]), evm_string_len(e, v[0]), 0);
        } else if( evm_is_buffer(e, v[0]) ) {
            send(sock->sockfd, evm_buffer_addr(e, v[0]), evm_buffer_len(e, v[0]), 0);
        }
    }

    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_call(e, v[2], EVM_UNDEFINED, 0, NULL);
    }

    shutdown(sock->sockfd, SHUT_WR);
    return EVM_UNDEFINED;
}

//socket.setKeepAlive([enable][, initialDelay])
static evm_val_t evm_module_net_socket_setKeepAlive(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock = evm_object_get_user_data(e, p);
    if( !sock )
        return EVM_UNDEFINED;
    if( argc > 0 && evm_is_boolean(e, v[0]) ) {
        if( evm_2_boolean(e, v[0]) ) {
            int keepAlive = 1;
            setsockopt(sock->sockfd, SOL_SOCKET, SO_KEEPALIVE, (void*)&keepAlive, sizeof(keepAlive));
        } else {
            int keepAlive = 0;
            setsockopt(sock->sockfd, SOL_SOCKET, SO_KEEPALIVE, (void*)&keepAlive, sizeof(keepAlive));
        }
    }
    return EVM_UNDEFINED;
}

//socket.write(data)
static evm_val_t evm_module_net_socket_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock = evm_object_get_user_data(e, p);
    if( !sock )
        return EVM_UNDEFINED;
    if( argc > 0 ) {
        if( evm_is_string(e, v[0]) ) {
            send(sock->sockfd, evm_2_string(e, v[0]), evm_string_len(e, v[0]), 0);
        } else if( evm_is_buffer(e, v[0]) ) {
            send(sock->sockfd, evm_buffer_addr(e, v[0]), evm_buffer_len(e, v[0]), 0);
        }
    }
    return EVM_UNDEFINED;
}

//socket.read(size)
static evm_val_t evm_module_net_socket_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock = (net_socket_t *)evm_object_get_user_data(e, p);
    if( !sock )
        return EVM_UNDEFINED;
    int len = evm_2_integer(e, v[0]);
    evm_val_t buf_obj = evm_buffer_create(e, NULL, len);
    uint8_t *buf = evm_buffer_addr(e, buf_obj);
    recv(sock->sockfd, buf, len, 0);
    return buf_obj;
}

//net.createConnection(options[, connectListener])
//net.createConnection(port[, host][, connectListener])
static evm_val_t evm_module_net_createConnection(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    net_socket_t *sock;
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_net_socket_connect, "", 0));
    evm_prop_set(e, obj, "destroy", evm_mk_native(e, evm_module_net_socket_destroy, "", 0));
    evm_prop_set(e, obj, "end", evm_mk_native(e, evm_module_net_socket_end, "", 0));
    evm_prop_set(e, obj, "setKeepAlive", evm_mk_native(e, evm_module_net_socket_setKeepAlive, "", 0));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_net_socket_write, "", 0));
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_net_socket_read, "", 0));
    sock = malloc(sizeof(net_socket_t));
    EVM_ASSERT(sock);
    evm_object_set_user_data(e, obj, sock);
    evm_module_net_socket_connect(e, obj, argc, v);
    return obj;
}

//net.connect(options)
//net.connect(port[, host])
static evm_val_t evm_module_net_connect(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return evm_module_net_createConnection(e, p, argc, v);
}

//net.createServer([options])
static evm_val_t evm_module_net_createServer(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t server_obj;
    net_socket_t *server_sock;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if( sockfd < 0 ) {
        return EVM_UNDEFINED;
    }
    
    server_obj = evm_object_create(e);
    evm_prop_set(e, server_obj, "close", evm_mk_native(e, evm_module_net_server_close, "", 0));
    evm_prop_set(e, server_obj, "listen", evm_mk_native(e, evm_module_net_server_listen, "", 0));

    server_sock = malloc(sizeof(net_socket_t));
    EVM_ASSERT(server_sock);
    server_sock->sockfd = sockfd;
    evm_object_set_user_data(e, server_obj, server_sock);
    return server_obj;
}

//new net.Socket([options])
static evm_val_t evm_module_net_socket(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_net_socket_connect, "", 0));
    evm_prop_set(e, obj, "destroy", evm_mk_native(e, evm_module_net_socket_destroy, "", 0));
    evm_prop_set(e, obj, "end", evm_mk_native(e, evm_module_net_socket_end, "", 0));
    evm_prop_set(e, obj, "setKeepAlive", evm_mk_native(e, evm_module_net_socket_setKeepAlive, "", 0));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_net_socket_write, "", 0));
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_net_socket_read, "", 0));

    net_socket_t *sock = malloc(sizeof(net_socket_t));
    EVM_ASSERT(sock);
    evm_object_set_user_data(e, obj, sock);
    return obj;
}

evm_err_t evm_module_net(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_net_connect, "connect", 0));
    evm_prop_set(e, obj, "createConnection", evm_mk_native(e, evm_module_net_createConnection, "createConnection", 0));
    evm_prop_set(e, obj, "createServer", evm_mk_native(e, evm_module_net_createServer, "createServer", 0));
    evm_prop_set(e, obj, "socket", evm_mk_native(e, evm_module_net_socket, "socket", 0));
    evm_module_add(e, "net", obj);
    return ec_ok;
}
#endif
