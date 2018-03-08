
.cpu cortex-m0
.thumb
.globl _start
_start:
.word 0x20010000
.word reset
.word done
.word done
.word done
.word done
.word done
.word done

.word done
.word done
.word done
.word done
.word done
.word done
.word done
.word done

.thumb_func
reset:
ldr r0,wdtctl
ldr r1,wdtdata
strh r1,[r0]
.thumb_func
done:
b .
nop
nop
.align
wdtctl: .word 0x4000480C
wdtdata: .word 0x5A84

/*
-------------------------------------------------------------------------
Copyright (c) 2018 David Welch dwelch@dwelch.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------
*/
