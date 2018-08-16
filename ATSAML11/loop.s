
.globl _start
_start:
.thumb_func
reset:
    add r0,#1
    sub r1,#1
    nop
    b reset


