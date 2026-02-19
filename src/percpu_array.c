// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
    __type(key, uint32_t);
    __type(value, uint64_t);
    __uint(max_entries, 8);
} percpu_array;

__attribute__((section("xdp"), used))
int test_percpu_array(struct xdp_md* ctx)
{
    uint32_t key = 0;
    uint64_t* value = bpf_map_lookup_elem(&percpu_array, &key);
    if (value) {
        *value += 1;
        return (int)*value;
    }
    return 0;
}
