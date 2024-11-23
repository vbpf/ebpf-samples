// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

#define ARRAY_SIZE 16

__attribute__ ((optnone))
int add1(int* x) {
    // Force using stack space in this function.
    int inner_array[ARRAY_SIZE];
    inner_array[1] = 1;

    // Modify the caller's stack.
    int result = *x + inner_array[1];

    *x = result;
    return result;
}

__attribute__ ((optnone))
int add2(int* x) {
    // Force using stack space in this function.
    int inner_array[ARRAY_SIZE];
    inner_array[1] = 13;

    add1(x);
    return add1(x);
}

#define CALLER_VALUE 3

// This program is intended to return 3 + 2 + 2 = 7.
// If there is any error in execution (say due to a bug in
// a JIT compiler or interpreter) it will instead return -1.
__attribute__((section("test"), used))
__attribute__((optnone))
int func(void* ctx) {
    // Initialize stack space in the caller.
    int outer_array[ARRAY_SIZE];
    outer_array[0] = CALLER_VALUE;
    outer_array[1] = CALLER_VALUE;

    // Ask callee to modify part of the caller's stack.
    add2(&outer_array[0]);
    int result = add2(&outer_array[0]);

    // Verify that the caller's stack was modified as requested.
    if (result != outer_array[0]) {
       return -1;
    }

    // Verify that the rest of the caller's stack is unmodified.
    if (outer_array[1] != CALLER_VALUE) {
        return -1;
    }

    return result;
}
