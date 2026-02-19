// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint64_t);
    __uint(max_entries, 4);
} shared_map;

/* Global (non-static) function — generates BTF func_proto info. */
__attribute__((noinline))
int add_and_store(uint32_t key, uint64_t a, uint64_t b)
{
    uint64_t sum = a + b;
    bpf_map_update_elem(&shared_map, &key, &sum, 0);
    return (int)sum;
}

/* Another global function calling the first. */
__attribute__((noinline))
int process_entry(uint32_t key)
{
    uint64_t* val = bpf_map_lookup_elem(&shared_map, &key);
    if (!val)
        return -1;
    return add_and_store(key, *val, 1);
}

__attribute__((section("xdp"), used))
int test_global_func(struct xdp_md* ctx)
{
    return process_entry(0);
}
