; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:18
; int read_write_packet_start(struct xdp_md* ctx)
       0:	r0 = 1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:20
;     void *data_end = (void *)(long)ctx->data_end;
       1:	r2 = *(u32 *)(r1 + 4)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:21
;     void *data = (void *)(long)ctx->data;
       2:	r1 = *(u32 *)(r1 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:22
;     if (data + sizeof(int) > data_end)
       3:	r3 = r1
       4:	r3 += 4
       5:	if r3 > r2 goto +4 <10>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:24
;     int value = *(int*)data;
       6:	r2 = *(u32 *)(r1 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:25
;     *(int*)data = value + 1;
       7:	r2 += 1
       8:	*(u32 *)(r1 + 0) = r2
       9:	r0 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_start_ok.c:27
; }
      10:	exit
