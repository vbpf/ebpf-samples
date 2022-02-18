; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:18
; int test_packet_access(struct xdp_md* ctx)
       0:	r6 = r1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:20
;     uint32_t rand32 = get_prandom_u32();
       1:	r0 = get_prandom_u32:7()
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:27
;     if (rand32 & 1) {
       2:	r1 = r0
       3:	r1 &= 1
       4:	if r1 == 0 goto +11 <16>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:23
;     int offset = (rand32 & 0x0F) * 4;
       5:	r0 <<= 2
       6:	r0 &= 60
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:22
;     void *data = (void *)(long)ctx->data;
       7:	r1 = *(u32 *)(r6 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:28
;         if (data + offset + sizeof(int) > data_end)
       8:	r1 += r0
       9:	r0 = 1
      10:	r2 = r1
      11:	r2 += 4
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:21
;     void *data_end = (void *)(long)ctx->data_end;
      12:	r3 = *(u32 *)(r6 + 4)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:28
;         if (data + offset + sizeof(int) > data_end)
      13:	if r2 > r3 goto +13 <27>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:31
;         return *(int*)ptr;
      14:	r0 = *(u32 *)(r1 + 0)
      15:	goto +11 <27>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:46
;         asm volatile("r0 <<= 2\n"
      16:	r0 <<= 2
      17:	r0 &= 60
      18:	r1 = *(u32 *)(r6 + 0)
      19:	r0 += r1
      20:	r1 = r0
      21:	r0 = 1
      22:	r2 = r1
      23:	r2 += 4
      24:	r3 = *(u32 *)(r6 + 4)
      25:	if r2 > r3 goto +1 <27>
      26:	r0 = *(u32 *)(r1 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_access.c:58
; }
      27:	exit
