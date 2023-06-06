       0:	r0 = get_prandom_u32:7()
       1:	r6 = r0
       2:	r7 = 0
       3:	*(u8 *)(r10 - 1) = r7
       4:	*(u32 *)(r10 - 8) = r7
       5:	r2 = r10
       6:	r2 += -8
       7:	r1 = map_fd 1
       9:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
      10:	if r0 == 0 goto +11 <22>
      11:	r2 = r6
      12:	r2 &= 1
      13:	r1 = r10
      14:	r1 += -1
      15:	if r2 == 0 goto +1 <17>
      16:	r1 = r0
      17:	r1 = *(u8 *)(r1 + 0)
      18:	r6 &= 255
      19:	r7 = 1
      20:	if r1 == r6 goto +1 <22>
      21:	r7 = 0
      22:	r0 = r7
      23:	exit
map 0:(original_fd = 1, inner_map_fd = 4294967295, type = 2, max_entries = 1, value_size = 4096, key_size = 4)
