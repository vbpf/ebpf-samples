// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section("xdp"), used))
int read_write_packet_start(struct xdp_md* ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    if (data > data_end)
        return 1;
    int value = *(int*)data;
    *(int*)data = value + 1;
    return 0;
}
