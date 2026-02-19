// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_DEVMAP);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 64);
} devmap;

__attribute__((section("xdp"), used))
int test_devmap(struct xdp_md* ctx)
{
    uint32_t ifindex = 1;
    return bpf_redirect_map(&devmap, ifindex, 0);
}
