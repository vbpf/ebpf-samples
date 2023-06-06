       0:	r6 = 1
       1:	*(u32 *)(r10 - 4) = r6
       2:	r1 = map_fd 1
       4:	r1 += 32
       5:	r2 = r10
       6:	r2 += -4
       7:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
       8:	if r0 != 0 goto +1 <10>
       9:	r6 = 0
      10:	r0 = r6
      11:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 1, max_entries = 1, value_size = 4, key_size = 4)
