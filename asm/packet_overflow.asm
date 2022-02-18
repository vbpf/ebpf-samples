; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:18
; int read_write_packet_start(struct xdp_md* ctx)
       0:	r0 = 1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:21
;     void *data = (void *)(long)ctx->data;
       1:	r2 = *(u32 *)(r1 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:20
;     void *data_end = (void *)(long)ctx->data_end;
       2:	r1 = *(u32 *)(r1 + 4)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:22
;     if (data > data_end)
       3:	if r2 > r1 goto +4 <8>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:24
;     int value = *(int*)data;
       4:	r1 = *(u32 *)(r2 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:25
;     *(int*)data = value + 1;
       5:	r1 += 1
       6:	*(u32 *)(r2 + 0) = r1
       7:	r0 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_overflow.c:27
; }
       8:	exit
