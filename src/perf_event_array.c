// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
} perf_map;

struct event {
    uint32_t pid;
    uint64_t timestamp;
};

__attribute__((section("xdp"), used))
int test_perf_event(struct xdp_md* ctx)
{
    struct event e;
    e.pid = bpf_get_prandom_u32();
    e.timestamp = bpf_ktime_get_ns();

    bpf_perf_event_output(ctx, &perf_map, 0, &e, sizeof(e));
    return 0;
}
