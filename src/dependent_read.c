// Copyright (c) Microsoft Corporation
// SPDX-License-Identifier: MIT

#include "bpf.h"

__attribute__((section("xdp"), used)) void
dependent_read(struct xdp_md* ctx)
{
    // Clear register r5.
    asm volatile ("r5 = 0");
    // Store data pointer and end pointer in registers r2 and r3.
    asm volatile("r2 = %0" : : "r"(ctx->data));
    asm volatile("r3 = %0" : : "r"(ctx->data_end));
    // Save the data pointer in r1 (as r2 will be modified).
    asm volatile ("r1 = r2");
    // Check if the packet is at least 4 bytes long.
    asm volatile ("r2 += 4");
    asm volatile ("if r2 > r3 goto +1");
    // Set the value of r5 to 1 if the packet is at least 4 bytes long.
    asm volatile ("r5 = 1");
    // Skip the next instruction if r5 is 0.
    asm volatile ("if r5 == 0 goto +1");
    // Read 4 bytes from the packet.
    asm volatile ("r0 = *(u32 *)(r1 + 0)");
    // Return 0.
    asm volatile ("r0 = 0");
}
