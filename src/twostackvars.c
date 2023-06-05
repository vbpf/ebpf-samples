// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

struct ctx;

int func(struct ctx* ctx)
{
    int stack_buffer[16];
    int *ptr = (int*)0;

    uint32_t rand32 = bpf_get_prandom_u32();
    if (rand32 & 1) {
        // In this path we want ptr to point to one section
        // of stack space that is known to be a number, and have
        // the rest of the stack be unknown.
        for (int i = 0; i < 8; i++) {
            stack_buffer[i] = bpf_get_prandom_u32();
        }
        int index = rand32 % 8;
        ptr = &stack_buffer[index];

        // Do something with the pointer to force it to be saved in a
        // register before joining the two paths.
        ptr[index ^ 1] = 0;
    } else {
        // In this path we want ptr to point to a different section
        // of stack space that is known to be a number, and have
        // the rest of the stack be unknown.
        int* stack_buffer2 = &stack_buffer[8];
        for (int i = 0; i < 8; i++) {
            stack_buffer2[i] = bpf_get_prandom_u32();
        }
        ptr = &stack_buffer2[rand32 % 8];
    }

    // Here we want to dereference the pointer to get a number.
    // In both paths above, ptr safely points to a number, even
    // though each part of stack_buffer is not necessarily a number
    // at this point.

    return *ptr;
}
