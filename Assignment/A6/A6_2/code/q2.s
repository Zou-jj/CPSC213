.pos 0x100
                 ld   $0x0, r0            # r0 = temp_i = 0
                 ld   $n, r1              # r1 = address of n
                 ld   (r1), r1            # r1 = n
                 ld   $0x0, r2            # r2 = temp_c = 0
                 ld   $a, r3              # r3 = address of a[0]
                 ld   $b, r4              # r4 = address of b[0]
loop:            mov  r1, r5              # r5 = temp_n
                 not  r5                  # r5 = ~temp_n
                 inc  r5                  # r5 = -temp_n
                 add  r0, r5              # r5 = temp_i-temp_n
                 bgt  r5, end_loop        # if temp_i>temp_n goto end_loop
                 beq  r5, end_loop        # if temp_i=temp_n goto end_loop
                 ld   (r3, r0, 4), r6     # r6 = temp_a[i]
                 ld   (r4, r0, 4), r7     # r7 = temp_b[i]
                 not  r7                  # r7 = ~temp_b[i]
                 inc  r7                  # r7 = -temp_b[i]
                 add  r6, r7              # r7 = temp_a[i]-temp_b[i]
                 bgt  r7, then            # if temp_a[i]>temp_b[i] goto then
                 inc  r0                  # r0 = temp_i++
                 br   loop                # goto loop
then:
                 inc  r0                  # r0 = tmep_i++
                 inc  r2                  # temp_c++
                 br   loop                # goto loop
end_loop:        ld   $c, r7              # r4 = address of c
                 st   r2, 0x0(r7)         # c = temp_c
                 ld   $i, r7              # r5 = address of i
                 st   r0, 0x0(r7)         # i = temp_i
                 halt 

.pos 0x1000
i:               .long 0xffffffff         # i
n:               .long 0x00000005         # n
a:               .long 0x0000000a         # a[0]
                 .long 0x00000014         # a[1]
                 .long 0x0000001e         # a[2]
                 .long 0x00000028         # a[3]
                 .long 0x00000032         # a[4]
b:               .long 0x0000000b         # b[0]
                 .long 0x00000014         # b[1]
                 .long 0x0000001c         # b[2]
                 .long 0x0000002c         # b[3]
                 .long 0x00000030         # b[4]
c:               .long 0x00000000         # c