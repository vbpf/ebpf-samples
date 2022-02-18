; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:15
;     uint32_t rand32 = get_prandom_u32();
       0:	r0 = get_prandom_u32:7()
       1:	r6 = r0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:16
;     if (rand32 & 1) {
       2:	r1 = r6
       3:	r1 &= 1
       4:	if r1 == 0 goto +29 <34>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:21
;             stack_buffer[i] = get_prandom_u32();
       5:	r0 = get_prandom_u32:7()
       6:	*(u32 *)(r10 - 64) = r0
       7:	r0 = get_prandom_u32:7()
       8:	*(u32 *)(r10 - 60) = r0
       9:	r0 = get_prandom_u32:7()
      10:	*(u32 *)(r10 - 56) = r0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:23
;         int index = rand32 % 8;
      11:	r6 &= 7
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:24
;         ptr = &stack_buffer[index];
      12:	r1 = r6
      13:	r1 <<= 2
      14:	r7 = r10
      15:	r7 += -64
      16:	r7 += r1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:21
;             stack_buffer[i] = get_prandom_u32();
      17:	r0 = get_prandom_u32:7()
      18:	*(u32 *)(r10 - 52) = r0
      19:	r0 = get_prandom_u32:7()
      20:	*(u32 *)(r10 - 48) = r0
      21:	r0 = get_prandom_u32:7()
      22:	*(u32 *)(r10 - 44) = r0
      23:	r0 = get_prandom_u32:7()
      24:	*(u32 *)(r10 - 40) = r0
      25:	r0 = get_prandom_u32:7()
      26:	*(u32 *)(r10 - 36) = r0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:28
;         ptr[index ^ 1] = 0;
      27:	r6 ^= 1
      28:	r6 <<= 2
      29:	r1 = r7
      30:	r1 += r6
      31:	r2 = 0
      32:	*(u32 *)(r1 + 0) = r2
      33:	goto +21 <55>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:35
;             stack_buffer2[i] = get_prandom_u32();
      34:	r0 = get_prandom_u32:7()
      35:	*(u32 *)(r10 - 32) = r0
      36:	r0 = get_prandom_u32:7()
      37:	*(u32 *)(r10 - 28) = r0
      38:	r0 = get_prandom_u32:7()
      39:	*(u32 *)(r10 - 24) = r0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:37
;         ptr = &stack_buffer2[rand32 % 8];
      40:	r6 &= 7
      41:	r6 <<= 2
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:33
;         int* stack_buffer2 = &stack_buffer[8];
      42:	r7 = r10
      43:	r7 += -32
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:37
;         ptr = &stack_buffer2[rand32 % 8];
      44:	r7 += r6
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:35
;             stack_buffer2[i] = get_prandom_u32();
      45:	r0 = get_prandom_u32:7()
      46:	*(u32 *)(r10 - 20) = r0
      47:	r0 = get_prandom_u32:7()
      48:	*(u32 *)(r10 - 16) = r0
      49:	r0 = get_prandom_u32:7()
      50:	*(u32 *)(r10 - 12) = r0
      51:	r0 = get_prandom_u32:7()
      52:	*(u32 *)(r10 - 8) = r0
      53:	r0 = get_prandom_u32:7()
      54:	*(u32 *)(r10 - 4) = r0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/twostackvars.c:45
;     return *ptr;
      55:	r0 = *(u32 *)(r7 + 0)
      56:	exit
