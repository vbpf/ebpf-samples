// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#define BPF_MAP_TYPE_ARRAY 2

#define __uint(name, val) int (*name)[val]
#define __type(name, val) typeof(val) *name
#define __array(name, val) typeof(val) *name[]

// Declare maps using new format.

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    // Declare keys and values using __type macro.
    __type(key, int);
    __type(value, uint64_t);
    __uint(max_entries, 1);
} map1;

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    // Declare keys and values using __uint macro.
    __uint(key_size, sizeof(int));
    __uint(value_size, sizeof(uint64_t));
    __uint(max_entries, 2);
} map2;

static void* (*bpf_map_lookup_elem)(struct ebpf_map* map, const void* key) = (void*) 1;
static int (*get_prandom_u32)() = (void*)7;

struct ctx;

int func(struct ctx* ctx)
{
    uint32_t rand32 = get_prandom_u32();
    struct ebpf_map* map = (rand32 & 1) ? &map1 : &map2;

    int key = 10;
    uint64_t* value = (uint64_t*)bpf_map_lookup_elem(map, &key);
    if (value == 0)
        return 0;

    // The following is safe since both maps have the same value size.
    return (int)*value;
}
