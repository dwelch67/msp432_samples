
ARMGNU ?= arm-none-eabi

AOPS = --warn
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-m4 -mthumb

all : flash02.sram.bin

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

flash02.o : flash02.c
	$(ARMGNU)-gcc $(COPS) -c flash02.c -o flash02.o

flash02.flash.bin : flash.ld flash.o flash02.o
	$(ARMGNU)-ld -o flash02.flash.elf -T flash.ld flash.o flash02.o
	$(ARMGNU)-objdump -D flash02.flash.elf > flash02.flash.list
	$(ARMGNU)-objcopy flash02.flash.elf flash02.flash.bin -O binary

flash02.sram.bin : sram.ld sram.o flash02.o blinker.bin.o
	$(ARMGNU)-ld -o flash02.sram.elf -T sram.ld sram.o flash02.o blinker.bin.o
	$(ARMGNU)-objdump -D flash02.sram.elf > flash02.sram.list
	$(ARMGNU)-objcopy flash02.sram.elf flash02.sram.bin -O binary

blinker.o : blinker.c
	$(ARMGNU)-gcc $(COPS) -c blinker.c -o blinker.o

blinker.flash.bin : flash.ld flash.o blinker.o
	$(ARMGNU)-ld -o blinker.flash.elf -T flash.ld flash.o blinker.o
	$(ARMGNU)-objdump -D blinker.flash.elf > blinker.flash.list
	$(ARMGNU)-objcopy blinker.flash.elf blinker.flash.bin -O binary

blinker.sram.bin : sram.ld sram.o blinker.o
	$(ARMGNU)-ld -o blinker.sram.elf -T sram.ld sram.o blinker.o
	$(ARMGNU)-objdump -D blinker.sram.elf > blinker.sram.list
	$(ARMGNU)-objcopy blinker.sram.elf blinker.sram.bin -O binary

blinker.bin.o : bintoc blinker.flash.bin
	./bintoc blinker.flash.bin blinker.bin.c
	$(ARMGNU)-gcc $(COPS) -c blinker.bin.c -o blinker.bin.o

