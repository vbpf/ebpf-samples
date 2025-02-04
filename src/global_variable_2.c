// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"


/* This code section is derived from the Cilium code base 
https://github.com/cilium/cilium/blob/66b6a0255249e8f2b8f46efd7fdae01c17209dbe/bpf/lib/static_data.h#L10C1-L41C37
with modifications to fit the current context.
*/

/* Declare a global configuration variable that can be modified at runtime,
 * without needing to recompile the datapath. Access the variable using the
 * CONFIG() macro.
 */
#define DECLARE_CONFIG(type, name, description) \
	__attribute__((section(".rodata.config"), used)) \
	__attribute__((btf_decl_tag(description))) \
	volatile const type __config_##name;

/* Hardcode config values at compile time, e.g. from per-endpoint headers.
 * Can be used only once per config variable within a single compilation unit.
 */
#define ASSIGN_CONFIG(type, name, value) \
	volatile const type __config_##name = value;

/* Access a global configuration variable declared using DECLARE_CONFIG(). All
 * accesses must be done through this macro to ensure the loader's dead code
 * elimination can recognize them.
 */
#define CONFIG(name) __config_##name

DECLARE_CONFIG(int, global_var, "A global variable that can be modified at runtime.")

ASSIGN_CONFIG(int, global_var, 10);

int func(void* ctx) {

    return CONFIG(global_var);
}
