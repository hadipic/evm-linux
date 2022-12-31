#ifdef CONFIG_EVM_MODULE_TLS

#include "evm_module_tls.h"

EVM_FUNCTION(evm_module_tls_connect) {
    EVM_EPCV;
    iot_tls_t *tls_data = evm_object_get_user_data(e, p);
    if (tls_data->state == TLS_HANDSHAKE_READY) {
        const char *server_name = evm_2_string(e, v[0]);
        mbedtls_ssl_set_hostname(&tls_data->ssl, server_name);
    }

    EVM_RETURN( EVM_UNDEFINED );
}

static size_t iot_bio_pending(iot_bio_t *bio) {
    if (bio->read_index <= bio->write_index) {
        return bio->write_index - bio->read_index;
    }

    return bio->write_index + bio->size - bio->read_index;
}

static size_t iot_bio_remaining(iot_bio_t *bio) {
    if (bio->write_index < bio->read_index) {
        return bio->read_index - bio->write_index - 1;
    }

    return bio->read_index + bio->size - bio->write_index - 1;
}

static void iot_bio_read(iot_bio_t *bio, char *buf, size_t size) {
    EVM_ASSERT(size <= iot_bio_pending(bio));

    if (bio->read_index + size > bio->size) {
    size_t copy_size = bio->size - bio->read_index;

    memcpy(buf, bio->mem + bio->read_index, copy_size);
        size -= copy_size;
        buf += copy_size;
        bio->read_index = 0;
    }

    memcpy(buf, bio->mem + bio->read_index, size);
    bio->read_index += size;
}

static void iot_bio_write(iot_bio_t *bio, const char *buf, size_t size) {
    EVM_ASSERT(size <= iot_bio_remaining(bio));

    if (bio->write_index + size > bio->size) {
        size_t copy_size = bio->size - bio->write_index;

        memcpy(bio->mem + bio->write_index, buf, copy_size);
        size -= copy_size;
        buf += copy_size;
        bio->write_index = 0;
    }

    memcpy(bio->mem + bio->write_index, buf, size);
    bio->write_index += size;
}

static int iot_bio_net_send(void *ctx, const unsigned char *buf, size_t len) {
    iot_bio_t *send_bio = &(((iot_bio_pair_t *)ctx)->send_bio);

    size_t remaining = iot_bio_remaining(send_bio);

    if (remaining == 0) {
        return MBEDTLS_ERR_SSL_WANT_WRITE;
    }

    if (len > remaining) {
        len = remaining;
    }

    iot_bio_write(send_bio, (const char *)buf, len);
    return (int)len;
}

static int iot_bio_net_receive(void *ctx, unsigned char *buf, size_t len) {
    iot_bio_t *receive_bio = &(((iot_bio_pair_t *)ctx)->receive_bio);

    size_t pending = iot_bio_pending(receive_bio);

    if (pending == 0) {
        return MBEDTLS_ERR_SSL_WANT_READ;
    }

    if (len > pending) {
        len = pending;
    }

    iot_bio_read(receive_bio, (char *)buf, len);
    return (int)len;
}

static void iot_tls_send_pending(iot_tls_t *tls_data) {
    evm_t *e = evm_runtime();
    iot_bio_t *send_bio = &(tls_data->bio.send_bio);
    size_t pending = iot_bio_pending(send_bio);

    if (pending == 0) {
        return;
    }
    uint8_t *buf = evm_malloc(pending);
    iot_bio_read(send_bio, buf, pending);

    evm_val_t jbuffer = evm_buffer_create(e, buf, pending);
    evm_free(buf);

    evm_val_t jthis = tls_data->jobject;
    evm_val_t fn = evm_prop_get(e, jthis, "onwrite");

    evm_call_free(e, fn, jthis, 1, &jbuffer);
    evm_val_free(e, fn);
    evm_val_free(e, jbuffer);
}

static void iot_bio_init(iot_bio_t *bio, size_t size) {
    bio->mem = (char *)evm_malloc(size);
    bio->size = size;
    bio->read_index = 0;
    bio->write_index = 0;
}

static void iot_tls_notify_error(iot_tls_t *tls_data) {
    evm_t *e = evm_runtime();
    evm_val_t jerror = evm_mk_string(e, "error");
    evm_val_t jmessage = evm_mk_string(e, "TLS error");

    evm_val_t jthis = tls_data->jobject;
    evm_val_t fn = evm_prop_get(e, jthis, "emit");

    evm_val_t jargv[2] = { jerror, jmessage };
    evm_call_free(e, fn, jthis, 2, jargv);

    evm_val_free(e, fn);
    evm_val_free(e, jargv[0]);
    evm_val_free(e, jargv[1]);
}

static void tls_handshake(iot_tls_t *tls_data, evm_val_t jthis) {
    evm_t *e = evm_runtime();
    tls_data->state = TLS_HANDSHAKE_IN_PROGRESS;
    // Continue handshaking process
    int ret_val = mbedtls_ssl_handshake(&tls_data->ssl);

    iot_tls_send_pending(tls_data);

    bool error;
    bool authorized;

    // Check whether handshake completed
    if (ret_val == 0) {
        tls_data->state = TLS_CONNECTED;
        error = false;
        authorized = mbedtls_ssl_get_verify_result(&tls_data->ssl) == 0;
    } else {
        if (ret_val == MBEDTLS_ERR_SSL_WANT_READ ||
            ret_val == MBEDTLS_ERR_SSL_WANT_WRITE) {
          return;
        }

        tls_data->state = TLS_CLOSED;
        error = true;
        authorized = false;
    }

    // Result of certificate verification
    evm_val_t jargv[2] = { evm_mk_boolean(e, error),
                             evm_mk_boolean(e, authorized) };

    evm_val_t fn = evm_prop_get(e, jthis, "onhandshakedone");
    evm_call_free(e, fn, jthis, 2, jargv);

    evm_val_free(e, fn);
    evm_val_free(e, jargv[0]);
    evm_val_free(e, jargv[1]);
}

EVM_FUNCTION(evm_module_tls_read) {
    EVM_EPCV;
    iot_tls_t *tls_data = evm_object_get_user_data(e, p);
    if (tls_data->state == TLS_CLOSED) {
        EVM_RETURN( EVM_UNDEFINED);
    }

    iot_bio_t *receive_bio = &(tls_data->bio.receive_bio);
    const char *data = NULL;
    size_t length = 0;

    if (argc >= 1 && evm_2_boolean(e, v[0])) {
        evm_val_t jbuffer = v[0];

        data = evm_buffer_addr(e, jbuffer);
        length = evm_buffer_len(e, jbuffer);
    }

    do {
        size_t copy_size = iot_bio_remaining(receive_bio);

        if (copy_size > length) {
            copy_size = length;
        }

        iot_bio_write(receive_bio, data, copy_size);
        data += copy_size;
        length -= copy_size;

        if (tls_data->state != TLS_CONNECTED) {
            EVM_ASSERT(tls_data->state == TLS_HANDSHAKE_READY ||
            tls_data->state == TLS_HANDSHAKE_IN_PROGRESS);
            tls_handshake(tls_data, p);

            if (tls_data->state != TLS_CONNECTED) {
                EVM_ASSERT(tls_data->state == TLS_HANDSHAKE_IN_PROGRESS ||
                tls_data->state == TLS_CLOSED);

                if (length > 0 && tls_data->state == TLS_HANDSHAKE_IN_PROGRESS) {
                    continue;
                }

                bool result = (tls_data->state != TLS_CLOSED);
                EVM_RETURN(evm_mk_boolean(e, result));
            }
        }

        while (true) {
            int ret_val = mbedtls_ssl_read(&tls_data->ssl, NULL, 0);
            iot_tls_send_pending(tls_data);

            if (ret_val == 0) {
                size_t pending = mbedtls_ssl_get_bytes_avail(&tls_data->ssl);

                if (pending == 0) {
                    continue;
                }
                uint8_t *buf = evm_malloc(pending);

                ret_val = mbedtls_ssl_read(&tls_data->ssl, (unsigned char *)buf,
                       pending);

                evm_val_t jbuffer = evm_buffer_create(e, buf, pending);
                evm_free(buf);

                EVM_ASSERT(ret_val == (int)pending);
                EVM_UNUSED(ret_val);

                evm_val_t fn = evm_prop_get(e, p, "onread");
                evm_call_free(e, fn, p, 1, &jbuffer);

                evm_val_free(e, jbuffer);
                evm_val_free(e, fn);
                continue;
            }

            if (ret_val == MBEDTLS_ERR_SSL_WANT_READ) {
                break;
            }

            if (ret_val == MBEDTLS_ERR_SSL_WANT_WRITE) {
                continue;
            }

            tls_data->state = TLS_CLOSED;

            if (ret_val == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
                EVM_RETURN(evm_mk_boolean(e, true));
            }

            iot_tls_notify_error(tls_data);
            EVM_RETURN(evm_mk_boolean(e, false));
        }
    } while (length > 0);

    EVM_RETURN(evm_mk_boolean(e, true));
}

EVM_FUNCTION(evm_module_tls_write) {
    EVM_EPCV;
    iot_tls_t *tls_data = evm_object_get_user_data(e, p);
    if (tls_data->state != TLS_CONNECTED) {
        EVM_RETURN(evm_mk_null(e));
    }

    const unsigned char *data = NULL;
    size_t length = 0;
    bool is_end = false;

    if (argc >= 1 && evm_2_boolean(e, v[0])) {
        evm_val_t jbuffer = v[0];

        data = (const unsigned char *)evm_buffer_addr(e, jbuffer);
        length = evm_buffer_len(e, jbuffer);
    }

    if (argc >= 2 && evm_2_boolean(e, v[1])) {
        is_end = true;
    }

    while (true) {
        int ret_val = mbedtls_ssl_write(&tls_data->ssl, data, length);

        if ((int)length == ret_val) {
            break;
        }

        iot_tls_send_pending(tls_data);

        if (ret_val > 0) {
            data += ret_val;
            length -= (size_t)ret_val;
        } else if (ret_val != MBEDTLS_ERR_SSL_WANT_WRITE) {
            tls_data->state = TLS_CLOSED;
            EVM_RETURN(evm_mk_null(e));
        }
    }

    if (is_end) {
        while (true) {
            int ret_val = mbedtls_ssl_close_notify(&tls_data->ssl);
            if (ret_val == 0) {
                tls_data->state = TLS_CLOSED;
                break;
            }

            iot_tls_send_pending(tls_data);

            if (ret_val != MBEDTLS_ERR_SSL_WANT_WRITE) {
                iot_tls_notify_error(tls_data);
                tls_data->state = TLS_CLOSED;
                EVM_RETURN(evm_mk_null(e));
            }
        }
    }

    /* Last package is returned as a buffer. */
    iot_bio_t *send_bio = &(tls_data->bio.send_bio);
    size_t pending = iot_bio_pending(send_bio);

    uint8_t *buf = evm_malloc(pending);
    iot_bio_read(send_bio, buf, pending);
    evm_val_t jbuffer = evm_buffer_create(e, buf, pending);
    evm_free(buf);
    EVM_RETURN(jbuffer);
}

static iot_tls_context_t *iot_tls_context_create(evm_val_t jobject) {
    evm_t *e = evm_runtime();
    iot_tls_context_t *tls_context = evm_malloc(sizeof(iot_tls_context_t));

    tls_context->ref_count = 1;
    tls_context->context_flags = 0;
    mbedtls_entropy_init(&tls_context->entropy);
    mbedtls_ctr_drbg_init(&tls_context->ctr_drbg);
    mbedtls_pk_init(&tls_context->pkey);
    mbedtls_x509_crt_init(&tls_context->own_cert);
    mbedtls_x509_crt_init(&tls_context->cert_auth);

    evm_object_set_user_data(e, jobject, tls_context);

    return tls_context;
}

EVM_FUNCTION(evm_module_tls_tlscontext) {
    EVM_EPCV;
    evm_val_t jtls = p;
    iot_tls_context_t *tls_context = iot_tls_context_create(jtls);

    evm_val_t joptions = v[0];

    // Set deterministic random bit generator
    if (mbedtls_ctr_drbg_seed(&tls_context->ctr_drbg, mbedtls_entropy_func,
                &tls_context->entropy, NULL, 0) != 0) {
        evm_throw(e, evm_mk_string(e, "drbg seeding failed"));
    }

    // User provided certificate
    int ret = 0;

    evm_val_t jcert = evm_prop_get(e, joptions, "cert");
    evm_val_t jkey = evm_prop_get(e, joptions, "key");

    const char *cert_chars = evm_2_string(e, jcert);

    ret = mbedtls_x509_crt_parse(&tls_context->own_cert, (const unsigned char *)cert_chars, (size_t)evm_string_len(e, jcert) + 1);

    const char *key_chars = evm_2_string(e, jkey);

    ret = mbedtls_pk_parse_key(&tls_context->pkey,
                     (const unsigned char *)key_chars,
                     (size_t)evm_string_len(e, jkey) + 1,
                     NULL, 0);

    if (ret == 0) {
        // Both own_cert and pkey must be valid for setting this flag.
        tls_context->context_flags |= SSL_CONTEXT_HAS_KEY;
    }

    evm_val_free(e, jcert);
    evm_val_free(e, jkey);

    if (ret != 0) {
        evm_throw(e, evm_mk_string(e, "key or certificate parsing failed"));
    }

    // User provided trusted certificates
    evm_val_t jcert_auth = evm_prop_get(e, joptions, "ca");

    if (!evm_is_undefined(e, jcert_auth)) {
        const char *cert_auth_chars = evm_2_string(e, jcert_auth);

        ret = mbedtls_x509_crt_parse(&tls_context->cert_auth,
                         (const unsigned char *)cert_auth_chars,
                         (size_t)evm_string_len(e, jcert_auth) +
                             1);

    } else {
        // Parse the default certificate authority
        ret = mbedtls_x509_crt_parse(&tls_context->cert_auth,
                         (const unsigned char *)SSL_CA_PEM,
                         sizeof(SSL_CA_PEM));
    }

    evm_val_free(e, jcert_auth);

    if (ret) {
        evm_throw(e, evm_mk_string(e, "certificate authority (CA) parsing failed"));
    }

    EVM_RETURN(EVM_UNDEFINED);
}

static iot_tls_t *iot_tls_create(evm_val_t jobject, iot_tls_context_t *tls_context) {
    evm_t *e = evm_runtime();
    iot_tls_t *tls_data = evm_malloc(sizeof(iot_tls_t));

    tls_context->ref_count++;

    tls_data->tls_context = tls_context;
    mbedtls_ssl_config_init(&tls_data->conf);
    mbedtls_ssl_init(&tls_data->ssl);
    tls_data->state = TLS_HANDSHAKE_READY;

    tls_data->jobject = jobject;
    evm_object_set_user_data(e, jobject, tls_data);

    return tls_data;
}

EVM_FUNCTION(evm_module_tls_init) {
    EVM_EPCV;
    evm_val_t jtls_socket = v[0];
    evm_val_t joptions = v[1];

    // Get context
    evm_val_t jtls_context = v[2];
    iot_tls_context_t *tls_context = evm_object_get_user_data(e, jtls_context);
    if (!tls_context) {
        evm_throw(e, evm_mk_string(e, "secure context not available"));
    }

    iot_tls_t *tls_data = iot_tls_create(jtls_socket, tls_context);

    // Check server
    evm_val_t jis_server = evm_prop_get(e, joptions, "isServer");
    bool is_server = evm_2_boolean(e, jis_server);
    evm_val_free(e, jis_server);

    if (tls_context->context_flags & SSL_CONTEXT_HAS_KEY) {
        if (mbedtls_ssl_conf_own_cert(&tls_data->conf, &tls_context->own_cert,
                                  &tls_context->pkey) != 0) {
            evm_throw(e, evm_mk_string(e, "certificate/private key cannot be set"));
        }
    }

    mbedtls_ssl_conf_ca_chain(&tls_data->conf, &tls_context->cert_auth, NULL);

    mbedtls_ssl_conf_rng(&tls_data->conf, mbedtls_ctr_drbg_random,
                   &tls_context->ctr_drbg);

    int endpoint = is_server ? MBEDTLS_SSL_IS_SERVER : MBEDTLS_SSL_IS_CLIENT;

    if (mbedtls_ssl_config_defaults(&tls_data->conf, endpoint,
                              MBEDTLS_SSL_TRANSPORT_STREAM,
                              MBEDTLS_SSL_PRESET_DEFAULT)) {
        evm_throw(e, evm_mk_string(e, "SSL Configuration failed"));
    }

    // if true, verifies CAs, must emit error if fails
    int auth_mode =
    is_server ? MBEDTLS_SSL_VERIFY_NONE : MBEDTLS_SSL_VERIFY_REQUIRED;

    evm_val_t jauth_mode = evm_prop_get(e, joptions, "rejectUnauthorized");

    if (!evm_is_undefined(e, jauth_mode)) {
        if (evm_2_boolean(e, jauth_mode)) {
            auth_mode = MBEDTLS_SSL_VERIFY_REQUIRED;
        } else {
            auth_mode = MBEDTLS_SSL_VERIFY_OPTIONAL;
        }
    }

    evm_val_free(e, jauth_mode);

    mbedtls_ssl_conf_authmode(&tls_data->conf, auth_mode);

    if (mbedtls_ssl_setup(&tls_data->ssl, &tls_data->conf)) {
        evm_throw(e, evm_mk_string(e, "SSL setup failed"));
    }

    // Connect mbedtls with iotjs_net_send and iotjs_net_recv functions
    iot_bio_init(&(tls_data->bio.receive_bio), SSL_BIO_SIZE);
    iot_bio_init(&(tls_data->bio.send_bio), SSL_BIO_SIZE);
    mbedtls_ssl_set_bio(&tls_data->ssl, &(tls_data->bio), iot_bio_net_send,
                  iot_bio_net_receive, NULL);

    EVM_RETURN(EVM_UNDEFINED);
}


void evm_module_tls(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_tls_connect, "connect", 0));
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_tls_read, "read", 0));
    evm_prop_set(e, obj, "TlsContext", evm_mk_native(e, evm_module_tls_tlscontext, "TlsContext", 0));
    evm_prop_set(e, obj, "TlsInit", evm_mk_native(e, evm_module_tls_init, "TlsInit", 0));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_tls_write, "write", 0));
    evm_module_add(e, "tls", obj);
}
#endif
