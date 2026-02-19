// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_QUEUE);
    __type(value, uint32_t);
    __uint(max_entries, 16);
} queue_map;

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_STACK);
    __type(value, uint32_t);
    __uint(max_entries, 16);
} stack_map;

int func(void* ctx)
{
    uint32_t val = 0;

    /* Pop from queue (FIFO). */
    if (bpf_map_lookup_elem(&queue_map, &val) == 0)
        return (int)val;

    /* Pop from stack (LIFO). */
    if (bpf_map_lookup_elem(&stack_map, &val) == 0)
        return (int)val;

    /* Push to queue. */
    val = 42;
    bpf_map_push_elem(&queue_map, &val, 0);

    /* Push to stack. */
    bpf_map_push_elem(&stack_map, &val, 0);

    return 0;
}
