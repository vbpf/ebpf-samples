       0:	*(u64 *)(r10 - 8) = r1
       1:	r1 = 0
       2:	*(u32 *)(r10 - 12) = r1
       3:	r2 = r10
       4:	r2 += -8
       5:	r3 = r10
       6:	r3 += -12
       7:	r1 = map_fd 1
       9:	r4 = 0
      10:	r0 = map_update_elem:2(map_fd r1, map_key r2, map_value r3, uint64_t r4)
      11:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 4, key_size = 8)
