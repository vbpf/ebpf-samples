       0:	r6 = 0
       1:	*(u32 *)(r10 - 4) = r6
       2:	r2 = r10
       3:	r2 += -4
       4:	r1 = map_fd 2
       6:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
       7:	if r0 == 0 goto +11 <19>
       8:	*(u32 *)(r10 - 8) = r6
       9:	r2 = r10
      10:	r2 += -8
      11:	r1 = r0
      12:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
      13:	if r0 != 0 goto +5 <19>
      14:	r2 = r10
      15:	r2 += -8
      16:	r1 = map_fd 1
      18:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
      19:	r0 = 0
      20:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 4, key_size = 4)
map 1:(original_fd = 2, inner_map_fd = 1, type = 12, max_entries = 1, value_size = 4, key_size = 4)
