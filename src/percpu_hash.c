// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_HASH);
    __type(key, uint32_t);
    __type(value, uint64_t);
    __uint(max_entries, 128);
} percpu_hash;

__attribute__((section("xdp"), used))
int test_percpu_hash(struct xdp_md* ctx)
{
    uint32_t key = bpf_get_prandom_u32();
    uint64_t* value = bpf_map_lookup_elem(&percpu_hash, &key);
    if (value) {
        *value += 1;
        return (int)*value;
    }

    uint64_t init_val = 1;
    bpf_map_update_elem(&percpu_hash, &key, &init_val, 0);
    return 0;
}
