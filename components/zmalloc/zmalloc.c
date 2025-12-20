/* zmalloc - total amount of allocated memory aware version of malloc()
 *
 * Copyright (c) 2009-2010, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evm.h"

#if defined (__WIN32) || defined (_WIN64) || defined (__linux)
#include <pthread.h>
#define LOCK(x) pthread_mutex_lock(x)
#define UNLOCK(x) pthread_mutex_unlock(x)
pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;
#else
#define LOCK(x) (void)x
#define UNLOCK(x) (void)x
static int used_memory_mutex = 0;
#endif


#define ZMALLOC malloc
#define ZREALLOC realloc
#define ZFREE free

#define PREFIX_SIZE sizeof(size_t)

#define increment_used_memory(__n) do { \
    size_t _n = (__n); \
    if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \
    if (zmalloc_thread_safe) { \
        LOCK(&used_memory_mutex);  \
        used_memory += _n; \
        UNLOCK(&used_memory_mutex); \
    } else { \
        used_memory += _n; \
    } \
} while(0)

#define decrement_used_memory(__n) do { \
    size_t _n = (__n); \
    if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \
    if (zmalloc_thread_safe) { \
        LOCK(&used_memory_mutex);  \
        used_memory -= _n; \
        UNLOCK(&used_memory_mutex); \
    } else { \
        used_memory -= _n; \
    } \
} while(0)

static size_t used_memory = 0;
static int zmalloc_thread_safe = 0;
static size_t max_used_memory = 0;

static void zmalloc_oom(size_t size) {
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
        size);
    fflush(stderr);
    abort();
}

void *zmalloc(size_t size) {
    void *ptr = ZMALLOC(size+PREFIX_SIZE);

    if (!ptr) zmalloc_oom(size);

    *((size_t*)ptr) = size;
    increment_used_memory(size+PREFIX_SIZE);
    if( used_memory > max_used_memory )
        max_used_memory = used_memory;
    return (char*)ptr+PREFIX_SIZE;
}

void *zrealloc(void *ptr, size_t size) {
    void *realptr;
    size_t oldsize;
    void *newptr;

    if (ptr == NULL) return zmalloc(size);

    realptr = (char*)ptr-PREFIX_SIZE;
    oldsize = *((size_t*)realptr);
    newptr = ZREALLOC(realptr,size+PREFIX_SIZE);
    if (!newptr) zmalloc_oom(size);
    if( used_memory > max_used_memory )
        max_used_memory = used_memory;
    *((size_t*)newptr) = size;
    decrement_used_memory(oldsize);
    increment_used_memory(size);
    if( used_memory > max_used_memory )
        max_used_memory = used_memory;
    return (char*)newptr+PREFIX_SIZE;
}

void * zqcalloc(size_t num, size_t size){
    size_t total = num * size;
    void *ptr = zmalloc(total);
    memset(ptr, 0, total);
    if( used_memory > max_used_memory )
        max_used_memory = used_memory;
    return ptr;
}

void zfree(void *ptr) {
    void *realptr;
    size_t oldsize;
    if (ptr == NULL) return;

    realptr = (char*)ptr-PREFIX_SIZE;
    oldsize = *((size_t*)realptr);
    decrement_used_memory(oldsize+PREFIX_SIZE);
    ZFREE(realptr);
}

char *zstrdup(const char *s) {
    size_t l = strlen(s)+1;
    char *p = zmalloc(l);
    memcpy(p,s,l);
    return p;
}

char *zstrndup(const char *s, size_t size) {
    char *ret = NULL;
    size_t l = strlen(s);
    if (size >= l){
        size = l;
    }
    ret = zmalloc(size + 1);
    if (ret){
        memcpy(ret, s, size);
        ret[size] = 0;
    }
    return ret;
}

size_t zmalloc_used_memory(void) {
    size_t um;

    if (zmalloc_thread_safe) LOCK(&used_memory_mutex);
    um = used_memory;
    if (zmalloc_thread_safe) UNLOCK(&used_memory_mutex);
    return um;
}

size_t zmalloc_max_used_memory(void) {
    size_t um;

    if (zmalloc_thread_safe) LOCK(&used_memory_mutex);
    um = max_used_memory;
    if (zmalloc_thread_safe) UNLOCK(&used_memory_mutex);
    return um;
}

void zmalloc_enable_thread_safeness(void) {
    zmalloc_thread_safe = 1;
}
