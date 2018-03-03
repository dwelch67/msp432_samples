
ARMGNU ?= arm-none-eabi

AOPS = --warn
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m4 -mthumb

all : flash03.sram.bin 

clean:
	rm -f *.bin
	rm -f *.bin.c
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f bintoc


#---------------------------------

bintoc : bintoc.c
	gcc -O2 bintoc.c -o bintoc

flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

flash03.o : flash03.c
	$(ARMGNU)-gcc $(COPS)  -c flash03.c -o flash03.o

flash03.flash.bin : flash.ld flash.o flash03.o
	$(ARMGNU)-ld -o flash03.flash.elf -T flash.ld flash.o flash03.o
	$(ARMGNU)-objdump -D flash03.flash.elf > flash03.flash.list
	$(ARMGNU)-objcopy flash03.flash.elf flash03.flash.bin -O binary

flash03.sram.bin : sram.ld sram.o flash03.o justwdt.bin.o
	$(ARMGNU)-ld -o flash03.sram.elf -T sram.ld sram.o flash03.o justwdt.bin.o
	$(ARMGNU)-objdump -D flash03.sram.elf > flash03.sram.list
	$(ARMGNU)-objcopy flash03.sram.elf flash03.sram.bin -O binary

justwdt.o : justwdt.c
	$(ARMGNU)-gcc $(COPS)  -c justwdt.c -o justwdt.o

justwdt.flash.bin : flash.ld flash.o justwdt.o
	$(ARMGNU)-ld -o justwdt.flash.elf -T flash.ld flash.o justwdt.o
	$(ARMGNU)-objdump -D justwdt.flash.elf > justwdt.flash.list
	$(ARMGNU)-objcopy justwdt.flash.elf justwdt.flash.bin -O binary

justwdt.sram.bin : sram.ld sram.o justwdt.o
	$(ARMGNU)-ld -o justwdt.sram.elf -T sram.ld sram.o justwdt.o
	$(ARMGNU)-objdump -D justwdt.sram.elf > justwdt.sram.list
	$(ARMGNU)-objcopy justwdt.sram.elf justwdt.sram.bin -O binary

justwdt.bin.o : bintoc justwdt.flash.bin
	./bintoc justwdt.flash.bin justwdt.bin.c
	$(ARMGNU)-gcc $(COPS)  -c justwdt.bin.c -o justwdt.bin.o

