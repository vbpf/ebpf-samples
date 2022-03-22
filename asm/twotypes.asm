; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:31
;     uint32_t rand32 = get_prandom_u32();
       0:	r0 = get_prandom_u32:7()
       1:	r6 = r0
       2:	r7 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:32
;     uint8_t stack_buffer[256] = { 0 };
       3:	*(u8 *)(r10 - 1) = r7
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:35
;     int map_key = 0;
       4:	*(u32 *)(r10 - 8) = r7
       5:	r2 = r10
       6:	r2 += -8
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:36
;     uint8_t* map_value = (uint8_t*)bpf_map_lookup_elem(&map, &map_key);
       7:	r1 = map_fd 1
       9:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:37
;     if (map_value == 0)
      10:	if r0 == 0 goto +11 <22>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:41
;     if (rand32 & 1) {
      11:	r2 = r6
      12:	r2 &= 1
      13:	r1 = r10
      14:	r1 += -1
      15:	if r2 == 0 goto +1 <17>
      16:	r1 = r0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:47
;     return (*ptr == stack_buffer[0]) ? 1 : 0;
      17:	r1 = *(u8 *)(r1 + 0)
      18:	r6 &= 255
      19:	r7 = 1
      20:	if r1 == r6 goto +1 <22>
      21:	r7 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twotypes.c:48
; }
      22:	r0 = r7
      23:	exit
