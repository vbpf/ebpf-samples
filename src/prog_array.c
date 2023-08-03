// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

int func0(void* ctx) {
    return 0;
}

int func1(void* ctx) {
    return 1;
}

int func2(void* ctx) {
    return 2;
}

int func3(void* ctx) {
    return 3;
}

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_PROG_ARRAY);
    __type(key, uint32_t);
    __uint(max_entries, 4);
    __array(values, int (void*));
} prog_array_map = {
    .values = { func0, func1, func2, func3 },
};

int func(void* ctx) {
    uint32_t key = bpf_get_prandom_u32() % 4;

    bpf_tail_call(ctx, &prog_array_map, key);

    return -1;
}
