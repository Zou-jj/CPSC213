.pos 0x100
gpc $6, r6
j end
halt
ld $1, r1
halt

end:
.pos 0x120
j 2(r6)