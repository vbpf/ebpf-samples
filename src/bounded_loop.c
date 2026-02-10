// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

// Negative test: Bounded loop that clang transforms in a way the verifier can't prove terminates.
// Clang may convert "i < 1000" to "i != 1000", which the verifier cannot prove terminates
// because it can't prove i will ever equal exactly 1000.
// Expected error: Could not prove termination
// Pattern: 4.7 - Infinite Loop / Termination Failure (compiler transformation variant)
// NOTE: Requires --termination flag (termination checking is disabled by default)

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1024);
} counter_map;

__attribute__((section("test"), used))
int test_bounded_loop(void* ctx)
{
    // This loop has a clear bound of 1000 iterations.
    // However, clang may transform "i < 1000" to "i != 1000".
    // The verifier can prove i increases, but cannot prove i will
    // ever equal exactly 1000 (it could theoretically skip over it).
    for (int i = 0; i < 1000; i++) {
        uint32_t key = i;
        uint32_t* slot = bpf_map_lookup_elem(&counter_map, &key);
        if (slot) {
            *slot += 1;
        }
    }
    
    return 0;
}
