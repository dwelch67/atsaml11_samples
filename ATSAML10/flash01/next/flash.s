
.thumb

.thumb_func
.global _start
_start:
stacktop: .word 0x20001000
.word reset
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang

.thumb_func
hang:
    b hang

.thumb_func
reset:
    ldr r0,=0x20000100
    mov r1,#0
top:
    str r1,[r0]
    add r1,#1
    b top

