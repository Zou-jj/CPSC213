.pos 0x100

    # tmp = 0
    ld $tmp, r0         # r0 = address of tmp
    ld $0, r1           # r1 = 0
    st r1, 0(r0)        # tmp = 0

    # tos = 0
    ld $tos, r0         # r0 = address of tos
    ld $0, r1           # r1 = 0
    st r1, 0(r0)        # tos = 0

    # s[tos] = a[0]
    ld $a, r0           # r0 = address of a
    ld 0(r0), r0        # r0 = a[0]
    ld $tos, r1         # r1 = address of tos
    ld 0(r1), r1        # r1 = tos
    ld $s, r2           # r2 = address of s
    st r0, (r2, r1, 4)  # s[tos] = a[0]

    # tos++
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r1        # r1 = tos
    inc r1              # r1 = tos + 1
    st r1, 0(r0)        # tos = tos + 1 

    # s[tos] = a[1]
    ld $a, r0           # r0 = address of a
    ld 4(r0), r0        # r0 = a[1]
    ld $tos, r1         # r1 = address of tos
    ld 0(r1), r1        # r1 = tos
    ld $s, r2           # r2 = address of s
    st r0, (r2, r1, 4)  # s[tos] = a[1]

    # tos++
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r1        # r1 = tos
    inc r1              # r1 = tos + 1
    st r1, 0(r0)        # tos = tos + 1 

    # s[tos] = a[2]
    ld $a, r0           # r0 = address of a
    ld 8(r0), r0        # r0 = a[2]
    ld $tos, r1         # r1 = address of tos
    ld 0(r1), r1        # r1 = tos
    ld $s, r2           # r2 = address of s
    st r0, (r2, r1, 4)  # s[tos] = a[2]

    # tos++
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r1        # r1 = tos
    inc r1              # r1 = tos + 1
    st r1, 0(r0)        # tos = tos + 1 

    # tos--
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r1        # r1 = tos
    dec r1              # r1 = tos - 1
    st r1, 0(r0)        # tos = tos - 1

    # tmp = s[tos]
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r0        # r0 = tos
    ld $s, r1           # r1 = address of s
    ld (r1, r0, 4), r2  # r2 = s[tos]
    ld $tmp, r3         # r3 = address of tmp
    st r2, 0(r3)        # tmp = s[tos]

    # tos--
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r1        # r1 = tos
    dec r1              # r1 = tos - 1
    st r1, 0(r0)        # tos = tos - 1

    # tmp = tmp + s[tos]
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r0        # r0 = tos
    ld $s, r1           # r1 = address of s
    ld (r1, r0, 4), r2  # r2 = s[tos]
    ld $tmp, r3         # r3 = address of tmp
    ld 0(r3), r4        # r4 = tmp
    add r2, r4          # r4 = tmp + s[tos]
    st r4, 0(r3)        # tmp = tmp + s[tos]

    # tos--
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r1        # r1 = tos
    dec r1              # r1 = tos - 1
    st r1, 0(r0)        # tos = tos - 1

    # tmp = tmp + s[tos]
    ld $tos, r0         # r0 = address of tos
    ld 0(r0), r0        # r0 = tos
    ld $s, r1           # r1 = address of s
    ld (r1, r0, 4), r2  # r2 = s[tos]
    ld $tmp, r3         # r3 = address of tmp
    ld 0(r3), r4        # r4 = tmp
    add r2, r4          # r4 = tmp + s[tos]
    st r4, 0(r3)        # tmp = tmp + s[tos]

    halt 

.pos 0x200
# Data area

a:  .long 1             # a[0]
    .long 2             # a[1]
    .long 3             # a[2]
s:  .long 0             # s[0]
    .long 0             # s[1]
    .long 0             # s[2]
    .long 0             # s[3]
    .long 0             # s[4]
tos:.long 0             # tos
tmp:.long 0             # tmp
