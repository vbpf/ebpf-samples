       0:	r0 = get_prandom_u32:7()
       1:	r0 &= 1
       2:	r1 = map_fd 2
       4:	if r0 == 0 goto +2 <7>
       5:	r1 = map_fd 1
       7:	r2 = 10
       8:	*(u32 *)(r10 - 4) = r2
       9:	r2 = r10
      10:	r2 += -4
      11:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
      12:	r1 = r0
      13:	r0 = 0
      14:	if r1 == 0 goto +1 <16>
      15:	r0 = *(u64 *)(r1 + 0)
      16:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 8, key_size = 4)
map 1:(original_fd = 2, inner_map_fd = 4294967295, type = 2, max_entries = 2, value_size = 8, key_size = 4)
