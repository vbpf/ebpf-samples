// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

// Negative test: Loop that the verifier cannot prove terminates.
// Expected error: Could not prove termination (pc[N]=[1, +oo] or similar)
// Pattern: 4.7 - Infinite Loop / Termination Failure

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} test_map;

__attribute__((section("test"), used))
int test_infinite_loop(void* ctx)
{
    uint32_t key = 0;
    uint32_t* bound_ptr = bpf_map_lookup_elem(&test_map, &key);
    
    if (!bound_ptr) {
        return 0;
    }
    
    uint32_t bound = *bound_ptr;
    uint32_t sum = 0;
    
    // Loop bound comes from map value, which is unbounded [0, UINT32_MAX].
    // Verifier cannot prove this loop terminates in bounded iterations.
    for (uint32_t i = 0; i < bound; i++) {
        sum += i;
    }
    
    return sum;
}
