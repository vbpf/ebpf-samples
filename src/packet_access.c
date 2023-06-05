// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section("xdp"), used))
int test_packet_access(struct xdp_md* ctx)
{
    uint32_t rand32 = bpf_get_prandom_u32();
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    int offset = (rand32 & 0x0F) * 4;
    int* ptr;

    // We now do two code paths that should have identical results.
    if (rand32 & 1) {
        if (data + offset + sizeof(int) > data_end)
            return 1;
        ptr = offset + data;
        return *(int*)ptr;
        /* The above code results in the following assembly:
         *            r0 <<= 2
         *            r0 &= 60
         *            r1 = *(u32 *)(r6 + 0)
         *            r1 += r0    // In the ELSE clause below, this becomes
         *                        // "r0 += r1" then "r1 = r0".
         *            r0 = 1
         *            r2 = r1
         *            r2 += 4
         *            r3 = *(u32 *)(r6 + 4)
         *            if r2 > r3 goto +13
         *            r0 = *(u32 *)(r1 + 0)
         */
    } else {
        asm volatile("r0 <<= 2\n"
                     "r0 &= 60\n"
                     "r1 = *(u32 *)(r6 + 0)\n"
                     "r0 += r1\n" // In the IF clause above, these two instructions
                     "r1 = r0\n"  // are "r1 += r0".
                     "r0 = 1\n"
                     "r2 = r1\n"
                     "r2 += 4\n"
                     "r3 = *(u32 *)(r6 + 4)\n"
                     "if r2 > r3 goto +1\n"
                     "r0 = *(u32 *)(r1 + 0)\n");
    }
}
