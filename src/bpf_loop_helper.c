// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint64_t);
    __uint(max_entries, 16);
} array_map;

struct loop_ctx {
    uint64_t sum;
};

static long loop_callback(uint32_t index, void* ctx)
{
    struct loop_ctx* lctx = ctx;
    uint64_t* val = bpf_map_lookup_elem(&array_map, &index);
    if (val)
        lctx->sum += *val;
    return 0;
}

__attribute__((section("xdp"), used))
int test_bpf_loop(struct xdp_md* ctx)
{
    struct loop_ctx lctx = { .sum = 0 };
    bpf_loop(16, loop_callback, &lctx, 0);
    return (int)lctx.sum;
}
