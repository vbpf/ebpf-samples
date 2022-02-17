; ./ebpf-samples/src/twomaps.c:38
;     uint32_t rand32 = get_prandom_u32();
       0:	r0 = get_prandom_u32:7()
; ./ebpf-samples/src/twomaps.c:39
;     struct ebpf
       1:	r0 &= 1
       2:	r1 = map_fd 2
       4:	if r0 == 0 goto +2 <7>
       5:	r1 = map_fd 1
       7:	r2 = 10
       8:	*(u32 *)(r10 - 4) = r2
       9:	r2 = r10
; ./ebpf-samples/src/twomaps.c:41
;     int key = 10;
      10:	r2 += -4
      11:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
      12:	r1 = r0
; ./ebpf-samples/src/twomaps.c:42
;     uint64_t* value = (uint64_t*)bpf_map_lookup_elem(map, &key);
      13:	r0 = 0
      14:	if r1 == 0 goto +1 <16>
      15:	r0 = *(u64 *)(r1 + 0)
; ./ebpf-samples/src/twomaps.c:43
;     if (value == 0)
      16:	exit
