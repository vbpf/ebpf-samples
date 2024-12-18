// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

// This sample demonstrates how to use global variables in BPF programs.
// Global variables are shared among all threads in the same BPF program and
// can be used to store global states. They must be declared as `volatile`
// to prevent the compiler from optimizing them away and must accessed
// using atomic operations to avoid race conditions.

// Global variables with initial value of 0 are put into .bss section.
static volatile uint32_t global_var = 0;
static volatile uint32_t global_var_2 = 0;
// Global const variables are put into .rodata section.
static volatile const uint32_t global_const_var = 10;
// Global variables with initial value are put into .data section.
static volatile uint32_t global_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int func(void* ctx) {
    __sync_fetch_and_add(&global_var, 1);
    __sync_fetch_and_add(&global_var_2, 2);
    global_array[0] = global_const_var;

    return 0;
}
