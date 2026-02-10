// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

// Negative test: Division by a value that could be zero.
// Expected error: Division by zero is possible (or similar)
// Pattern: 4.8 - Division by Zero

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} test_map;

__attribute__((section("test"), used))
int test_divzero(void* ctx)
{
    uint32_t key = 1;
    uint32_t* divisor_ptr = bpf_map_lookup_elem(&test_map, &key);
    
    if (!divisor_ptr) {
        return 0;
    }
    
    // divisor is in range [0, UINT32_MAX], which includes 0.
    // Division by zero is possible, so this should fail verification.
    uint32_t result = 100 / *divisor_ptr;
    
    return result;
}
