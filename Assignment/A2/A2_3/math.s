.pos 0x100
                 ld $a, r0       # r0 = &a
                 ld $b, r1       # r1 = &b
                 ld (r1), r2     # r2 = b
                 inc r2          # r2 ++
                 ld $0x4, r3     # r3 = 4
                 add r3, r2      # r2 += r3(4)
                 shr $0x1, r2    # r2 >> 1
                 ld (r1), r4     # r4 = b
                 and r4, r2      # r2 = r2 && r4
                 shl $0x2, r2    # r2 << 2
                 st r2, (r0)     # a = r2
                 halt
.pos 0x1000
a:               .long 0x00000001
.pos 0x2000
b:               .long 0x00000002