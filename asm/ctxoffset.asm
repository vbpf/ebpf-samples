       0:	r2 = 1
       1:	*(u32 *)(r10 - 4) = r2
       2:	r1 += 8
       3:	r3 = r10
       4:	r3 += -4
       5:	r2 = map_fd 1
       7:	r4 = 0
       8:	r0 = sock_map_update:53(ctx r1, map_fd r2, map_key r3, uint64_t r4)
       9:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 4, key_size = 4)
