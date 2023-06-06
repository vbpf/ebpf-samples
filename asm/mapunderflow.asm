       0:	r1 = 4294967295 ll
       2:	*(u32 *)(r10 - 4) = r1
       3:	r1 = 0
       4:	*(u64 *)(r10 - 16) = r1
       5:	r2 = r10
       6:	r2 += -4
       7:	r3 = r10
       8:	r3 += -16
       9:	r1 = map_fd 1
      11:	r4 = 0
      12:	r0 = map_update_elem:2(map_fd r1, map_key r2, map_value r3, uint64_t r4)
      13:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 8, key_size = 4)
