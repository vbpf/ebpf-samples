       0:	r1 = 1
       1:	*(u32 *)(r10 - 4) = r1
       2:	r2 = r10
       3:	r2 += -4
       4:	r1 = map_fd 1
       6:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
       7:	r1 = r0
       8:	r0 = 0
       9:	if r1 == 0 goto +1 <11>
      10:	r0 = *(u64 *)(r1 + 0)
      11:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 4, key_size = 4)
