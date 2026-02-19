// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_CPUMAP);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 16);
} cpumap;

__attribute__((section("xdp"), used))
int test_cpumap(struct xdp_md* ctx)
{
    uint32_t cpu = 0;
    return bpf_redirect_map(&cpumap, cpu, 0);
}
