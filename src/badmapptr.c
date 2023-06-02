// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    // Declare keys and values using __type macro.
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} test_map;

__attribute__((section("test"), used))
int
test_repro(void* ctx)
{
    uint32_t key = 1;

    typeof(test_map)* map = &test_map;

    // Instead of passing in the correct map pointer, pass in a value past it.
    // This should fail verification.
    uint32_t* value = bpf_map_lookup_elem(map + 1, &key);

    return (value != 0);
}
