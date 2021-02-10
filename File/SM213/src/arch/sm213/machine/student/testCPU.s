.pos 0x100
            ld $5, r1
            ld $27, r2
            add r2, r1
            halt
.pos 0x1000
a:          .long 3
            .long 14
            .long 13
            .long 16
            .long 17