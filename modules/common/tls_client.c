/*
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tls_client.h"
#include "tls_certificate.h"
#include "evm.h"


static int mbedtls_ssl_certificate_verify(MbedTLSSession *session)
{
    int ret = 0;
    ret = mbedtls_ssl_get_verify_result(&session->ssl);
    if (ret != 0)
    {
        evm_print("verify peer certificate fail....\r\n");
        memset(session->buffer, 0x00, session->buffer_len);
        mbedtls_x509_crt_verify_info((char *)session->buffer, session->buffer_len, "  ! ", ret);
        evm_print("verification info: %s\r\n", session->buffer);
        return 0;
    }
    return 1;
}

int mbedtls_client_init(MbedTLSSession *session, void *entropy, size_t entropyLen)
{
    int ret = 0;
    mbedtls_net_init(&session->server_fd);
    mbedtls_ssl_init(&session->ssl);
    mbedtls_ssl_config_init(&session->conf);
    mbedtls_ctr_drbg_init(&session->ctr_drbg);
    mbedtls_entropy_init(&session->entropy);
    mbedtls_x509_crt_init(&session->cacert);

    ret = mbedtls_ctr_drbg_seed(&session->ctr_drbg, mbedtls_entropy_func, &session->entropy,
                                     (unsigned char *)entropy, entropyLen);
    if (ret != 0)
    {
        evm_print("mbedtls_ctr_drbg_seed error, return -0x%x\r\n", -ret);
        return ret;
    }
    evm_print("mbedtls client struct init success...\r\n");

    return 1;
}

int mbedtls_client_close(MbedTLSSession *session)
{
    mbedtls_ssl_close_notify(&session->ssl);
    mbedtls_net_free(&session->server_fd);
    mbedtls_x509_crt_free(&session->cacert);
    mbedtls_entropy_free(&session->entropy);
    mbedtls_ctr_drbg_free(&session->ctr_drbg);
    mbedtls_ssl_config_free(&session->conf);
    mbedtls_ssl_free(&session->ssl);

    if (session->buffer)
    {
        evm_free(session->buffer);
    }

    if (session->host)
    {
        evm_free(session->host);
    }

    if(session->port)
    {
        evm_free(session->port);
    }

    if (session)
    {
        evm_free(session);
    }

    return 1;
}

int mbedtls_client_context(MbedTLSSession *session)
{
    int ret = 0;

    ret = mbedtls_x509_crt_parse(&session->cacert, (const unsigned char *)mbedtls_root_certificate,
                                 mbedtls_root_certificate_len);
    if (ret < 0)
    {
        evm_print("mbedtls_x509_crt_parse error,  return -0x%x\r\n", -ret);
        return ret;
    }

    evm_print("Loading the CA root certificate success...");

    /* Hostname set here should match CN in server certificate */
    if (session->host)
    {
        ret = mbedtls_ssl_set_hostname(&session->ssl, session->host);
        if (ret != 0)
        {
            evm_print("mbedtls_ssl_set_hostname error, return -0x%x\r\n", -ret);
            return ret;
        }
    }

    ret = mbedtls_ssl_config_defaults(&session->conf,
                                          MBEDTLS_SSL_IS_CLIENT,
                                          MBEDTLS_SSL_TRANSPORT_STREAM,
                                          MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret != 0)
    {
        evm_print("mbedtls_ssl_config_defaults error, return -0x%x\r\n", -ret);
        return ret;
    }

    mbedtls_ssl_conf_authmode(&session->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
    mbedtls_ssl_conf_ca_chain(&session->conf, &session->cacert, NULL);
    mbedtls_ssl_conf_rng(&session->conf, mbedtls_ctr_drbg_random, &session->ctr_drbg);

    ret = mbedtls_ssl_setup(&session->ssl, &session->conf);
    if (ret != 0)
    {
        evm_print("mbedtls_ssl_setup error, return -0x%x\n\r\n", -ret);
        return ret;
    }
    evm_print("mbedtls client context init success...\r\n");

    return 1;
}

int mbedtls_client_connect(MbedTLSSession *session)
{
    int ret = 0;

    ret = mbedtls_net_connect(&session->server_fd, session->host,
                                session->port, MBEDTLS_NET_PROTO_TCP);
    if (ret != 0)
    {
        evm_print("mbedtls_net_connect error, return -0x%x\r\n", -ret);
        return ret;
    }

    evm_print("Connected %s:%s success...\r\n", session->host, session->port);

    mbedtls_ssl_set_bio(&session->ssl, &session->server_fd, mbedtls_net_send, mbedtls_net_recv, NULL);

    while ((ret = mbedtls_ssl_handshake(&session->ssl)) != 0)
    {
        if (1 != mbedtls_ssl_certificate_verify(session))
        {
            return 0;
        }
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            evm_print("mbedtls_ssl_handshake error, return -0x%x\r\n", -ret);
            return ret;
        }
    }

    if (1 != mbedtls_ssl_certificate_verify(session))
    {
        return 0;
    }

    evm_print("Certificate verified success...");

    return 1;
}

int mbedtls_client_read(MbedTLSSession *session, unsigned char *buf , size_t len)
{
    int ret = 0;

    if (session == NULL || buf == NULL)
    {
        return 0;
    }

    ret = mbedtls_ssl_read(&session->ssl, (unsigned char *)buf, len);
    if (ret < 0 && ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
    {
        evm_print("mbedtls_client_read data error, return -0x%x", -ret);
    }

    return ret;
}

int mbedtls_client_write(MbedTLSSession *session, const unsigned char *buf , size_t len)
{
    int ret = 0;

    if (session == NULL || buf == NULL)
    {
        return 0;
    }

    ret = mbedtls_ssl_write(&session->ssl, (unsigned char *)buf, len);
    if (ret < 0 && ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
    {
        evm_print("mbedtls_client_write data error, return -0x%x", -ret);
    }

    return ret;
}
