
ARMGNU ?= arm-none-eabi

AOPS = --warn 
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m4 -mthumb

all : blinker01.sram.bin blinker01.flash.bin blinker01.bflash.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list

#---------------------------------

flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

blinker01.o : blinker01.c
	$(ARMGNU)-gcc $(COPS) -c blinker01.c -o blinker01.o

blinker01.sram.bin : sram.ld sram.o blinker01.o
	$(ARMGNU)-ld  -T sram.ld sram.o blinker01.o -o blinker01.sram.elf 
	$(ARMGNU)-objdump -D blinker01.sram.elf > blinker01.sram.list
	$(ARMGNU)-objcopy --srec-forceS3 blinker01.sram.elf -O srec blinker01.sram.srec
	$(ARMGNU)-objcopy blinker01.sram.elf blinker01.sram.bin -O binary

blinker01.flash.bin : flash.ld flash.o blinker01.o
	$(ARMGNU)-ld   -T flash.ld flash.o blinker01.o -o blinker01.flash.elf 
	$(ARMGNU)-objdump -D blinker01.flash.elf > blinker01.flash.list
	$(ARMGNU)-objcopy --srec-forceS3 blinker01.flash.elf -O srec blinker01.flash.srec
	$(ARMGNU)-objcopy blinker01.flash.elf blinker01.flash.bin -O binary

blinker01.bflash.bin : bflash.ld flash.o blinker01.o
	$(ARMGNU)-ld    -T bflash.ld flash.o blinker01.o -o blinker01.bflash.elf 
	$(ARMGNU)-objdump -D blinker01.bflash.elf > blinker01.bflash.list
	$(ARMGNU)-objcopy --srec-forceS3 blinker01.bflash.elf -O srec blinker01.bflash.srec
	$(ARMGNU)-objcopy blinker01.bflash.elf blinker01.bflash.bin -O binary

## -------------------------------------------------------------------------
## Copyright (c) 2018 David Welch dwelch@dwelch.com
## Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
## The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
##-------------------------------------------------------------------------

