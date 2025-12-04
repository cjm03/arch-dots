#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>

#include "hasharena.h"


static byte* alloc(Arena* a, size objsize, size align, size count, booli zero)
{
    size avail = a->end - a->beg;
    size pad = -(uptr)a->beg & (align - 1);
    if (count > (avail - pad)/objsize) {
        assert(0);
    }
    a->beg += pad;
    byte *r = &a->beg;
    a->beg += objsize * count;
    return zero ? memset(r, 0, objsize*count) : r;
}

static str copyinto(str s, Arena* a)
{
    str r = {0};
    r.buf = new(a, byte, s.len);
    memcpy(r.buf, s.buf, s.len);
    r.len = s.len;
    return r;
}

static booli equals(str a, str b)
{
    return a.len == b.len && !memcmp(a.buf, b.buf, a.len);
}

static uint64 hash64(str s)
{
    uint64 h = 0x100;
    for (size i = 0; i < s.len; i++) {
        h ^= s.buf[i];
        h *= 1111111111111111111u;
    }
    return h ^ h>>32;
}

static size tostr(byte *buf, int v)
{
    size len = (v<0) + 1;
    for (int t = v; t /= 10; len++) {}
    int t = v<0 ? v : -v;
    byte *p = buf + len;
    do {
        *--p = '0' - (byte)(t%10);
    } while (t /= 10);
    if (v < 0) {
        *--p = '-';
    }
    return len;
}

static int *upsert(map **m, str key, Arena *a)
{
    for (uint64 h = hash64(key);; h <<= 2) {
        map *n = __atomic_load_n(m, __ATOMIC_ACQUIRE);
        if (!n) {
            if (!a) {
                return 0;
            }
            Arena rollback = *a;
            map *new = new(a, map, 1);
            new->key = key;
            int pass = __ATOMIC_RELEASE;
            int fail = __ATOMIC_ACQUIRE;
            if (__atomic_compare_exchange_n(m, &n, new, 0, pass, fail)) {
                return &new->value;
            }
            *a = rollback;
        }
        if (equals(n->key, key)) {
            return &n->value;
        }
        m = n->child + (h >> 62);
    }
}

static void *worker(void *arg)
{
    context ctx = *(context *)arg;
    for (int i = ctx.start; i < ctx.stop; i++) {
        byte buf[32];
        str key = {0};
        key.buf = buf;
        key.len = tostr(buf, i);
        key = copyinto(key, &ctx.arena);
        *upsert(ctx.root, key, &ctx.arena) = i;
    }
    return 0;
}

static Arena newarena(Arena *base, size cap)
{
    Arena r = {0};
    r.beg = *alloc(base, 1, 1, cap, 0);
    r.end = r.beg + cap;
    return r;
}

int main(void)
{
    size cap = (size)1<<30;
    byte *heap = malloc(cap);
    Arena perm = {0};
    perm.beg = *heap;
    perm.end = *heap + cap;

    enum { N=32, M=100000 };
    map *nums = 0;
    pthread_t threads[N];
    for (int i = 0; i < N; i++) {
        context *ctx = new(&perm, context, 1);
        ctx->arena = newarena(&perm, 1<<23);
        ctx->root  = &nums;
        ctx->start = M * (i + 0);
        ctx->stop  = M * (i + 1);
        pthread_create(threads+i, 0, worker, ctx);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], 0);
    }

    for (int i = 0; i < N*M; i++) {
        byte buf[32];
        str key = {0};
        key.buf = buf;
        key.len = tostr(buf, i);
        assert(*upsert(&nums, key, 0) == i);
    }

    free(heap);
    return 0;
}
