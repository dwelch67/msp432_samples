
ARMGNU ?= arm-none-eabi

AOPS = --warn
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m4 -mthumb

all : bootloader01.sram.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f bintoc
	rm -f *.bin.c

#---------------------------------

bintoc : bintoc.c
	gcc -Wall bintoc.c -o bintoc

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

bootloader01.o : bootloader01.c
	$(ARMGNU)-gcc $(COPS)  -c bootloader01.c -o bootloader01.o

bootloader01.sram.bin :  sram.ld sram.o bootloader01.o bounce.bin.o justwdt.bin.o
	$(ARMGNU)-ld      -T sram.ld sram.o bootloader01.o bounce.bin.o justwdt.bin.o -o bootloader01.sram.elf
	$(ARMGNU)-objdump -D bootloader01.sram.elf > bootloader01.sram.list
	$(ARMGNU)-objcopy bootloader01.sram.elf bootloader01.sram.bin -O binary

bounce.bin : bounce.s
	$(ARMGNU)-as $(AOPS) bounce.s -o bounce.o
	$(ARMGNU)-ld -Ttext=0 bounce.o -o bounce.elf
	$(ARMGNU)-objdump -D bounce.elf > bounce.list
	$(ARMGNU)-objcopy bounce.elf bounce.bin -O binary

bounce.bin.o : bintoc bounce.bin
	./bintoc bounce.bin bounce.bin.c
	$(ARMGNU)-gcc $(COPS) -c bounce.bin.c -o bounce.bin.o

justwdt.bin : justwdt.s
	$(ARMGNU)-as $(AOPS) justwdt.s -o justwdt.o
	$(ARMGNU)-ld -Ttext=0 justwdt.o -o justwdt.elf
	$(ARMGNU)-objdump -D justwdt.elf > justwdt.list
	$(ARMGNU)-objcopy justwdt.elf justwdt.bin -O binary

justwdt.bin.o : bintoc justwdt.bin
	./bintoc justwdt.bin justwdt.bin.c _wdt
	$(ARMGNU)-gcc $(COPS) -c justwdt.bin.c -o justwdt.bin.o

##-------------------------------------------------------------------------
## Copyright (c) 2018 David Welch dwelch@dwelch.com
## Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
## The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
##-------------------------------------------------------------------------
