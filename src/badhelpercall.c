// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

int func()
{
    char buffer[1];

    // The following should fail verification since it asks the helper
    // to write past the end of the stack.
    return bpf_get_current_comm(buffer, 20);
}
