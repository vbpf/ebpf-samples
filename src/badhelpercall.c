// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

static int (*ebpf_get_current_comm)(char* buffer, uint32_t buffer_size) = (void*) 16;

int func()
{
    char buffer[1];

    // The following should fail verification since it asks the helper
    // to write past the end of the stack.
    return ebpf_get_current_comm(buffer, 20);
}
