.pos 0x100
                 ld $t, r0
                 ld $array, r1
                 ld 0x0(r1), r2
                 st r2, (r0)     # t = array[0]
                 ld 0x0(r0), r3     # r3 = t
                 ld 0x4(r1), r4
                 st r4, (r1)
                 st r3, 0x4(r1)
                 halt
.pos 0x1000
t:               .long 0xffffffff
.pos 0x2000
array:           .long 0xffffffff
                 .long 0xffffffff