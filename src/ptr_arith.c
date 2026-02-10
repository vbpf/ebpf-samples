// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

// Negative test: Pointer arithmetic with a non-number (pointer + pointer).
// Expected error: Invalid type (r<N>.type == number)
// Pattern: 4.6 - Pointer Arithmetic with Non-Number

#include "bpf.h"

__attribute__((section("xdp"), used))
int test_ptr_arith(struct xdp_md* ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    
    // Attempting to add two pointers together.
    // Only pointer + number is allowed, not pointer + pointer.
    void *bad_ptr = (void*)((long)data + (long)data_end);
    
    // Use bad_ptr to prevent optimization
    if (bad_ptr > data_end) {
        return 1;
    }
    
    return 0;
}
