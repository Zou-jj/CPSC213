.pos 0x1000
shl:  ld  $0x12345678, r1
      shr $12, r1            # r1 <= 0x1234567 << 17 == 0xacf0000
      halt

.pos 0x2000
data: .long 1
      .long 2