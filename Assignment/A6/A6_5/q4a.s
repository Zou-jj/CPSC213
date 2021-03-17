.pos 0x0
    ld   $sb, r5         # r5 = address of sb
    inca r5              # r5 = stack bottom
    gpc  $6, r6          # 
    j    0x300           # goto 0x300
    halt                 #

.pos 0x100
    .long 0x00001000     # address of arr

.pos 0x200
    ld   (r5), r0        # r0 = r5 = a0
    ld   4(r5), r1       # r1 = r5 + 4 = a1
    ld   $0x100, r2      # r2 = arr
    ld   (r2), r2        # r2 = arr
    ld   (r2, r1, 4), r3 # r3 = arr[a1]
    add  r3, r0          # r0 = a0 + arr[a1]
    st   r0, (r2, r1, 4) # arr[a1] = a0 + arr[a1]
    j    (r6)            # goto r6

.pos 0x300
    ld   $-12, r0        # r0 = -12
    add  r0, r5          # r5 = stack bottom - 12
    st   r6, 8(r5)       # save ra on stack
    ld   $1, r0          # r0 = 1
    st   r0, (r5)        # l0 = 1
    ld   $2, r0          # r0 = 2
    st   r0, 4(r5)       # l1 = 2
    ld   $-8, r0         # r0 = -8
    add  r0, r5          # r5 = r5 - 8
    ld   $3, r0          # r0 = 3
    st   r0, (r5)        # a0 = 3
    ld   $4, r0          # r0 = 4
    st   r0, 4(r5)       # a0 = 4
    gpc  $6, r6          # get pc
    j    0x200           # goto 200
    ld   $8, r0          # r0 = 8
    add  r0, r5          # r5 = r5 + 8
    ld   (r5), r1        # r1 = l0
    ld   4(r5), r2       # r2 = l1
    ld   $-8, r0         # r0 = -8
    add  r0, r5          # r5 = r5 - 8
    st   r1, (r5)        # a0 = l0
    st   r2, 4(r5)       # r1 = l1
    gpc  $6, r6          # get pc
    j    0x200           # goto 200
    ld   $8, r0          # r0 = 8
    add  r0, r5          # r5 = r5 + 8
    ld   8(r5), r6       # r6 = ra
    ld   $12, r0         # r0 = 12
    add  r0, r5          # r5 = stack bottom
    j    (r6)            # 

.pos 0x1000
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0

.pos 0x8000
    # These are here so you can see (some of) the stack contents
    # while running the code on the simulator.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0
