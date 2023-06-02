// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 256 * 1024);
} ring_buffer;

int
test(void* ctx)
{
    uint64_t test;
    // The following call should fail verification as test is not initialized.
    bpf_ringbuf_output(&ring_buffer, &test, sizeof(test), 0);

    return 0;
}
