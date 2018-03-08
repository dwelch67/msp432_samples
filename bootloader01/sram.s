
.cpu cortex-m4
.thumb

.thumb_func
.global _start
_start:
    ldr r0,stacktop
    mov sp,r0
    bl notmain
    b hang
.thumb_func
hang:   b .

.align
stacktop: .word 0x20008000

.thumb_func
.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.thumb_func
.globl GET8
GET8:
    ldrb r0,[r0]
    bx lr

.thumb_func
.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.thumb_func
.globl GET16
GET16:
    ldrh r0,[r0]
    bx lr

.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.thumb_func
.globl GETPC
GETPC:
    mov r0,pc
    bx lr

.thumb_func
.globl dummy
dummy:
    bx lr

.thumb_func
.globl zap
zap:
    mov r3,r2
zap_top:
    stmia r0!,{r2,r3}
    sub r1,#1
    bne zap_top
    bx lr

/*
-------------------------------------------------------------------------
Copyright (c) 2018 David Welch dwelch@dwelch.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------
*/
