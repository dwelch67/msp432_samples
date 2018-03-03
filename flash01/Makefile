
ARMGNU = arm-none-eabi

AOPS = --warn  
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m4

all : flash01.sram.bin

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

flash01.o : flash01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c flash01.c -o flash01.o

flash01.sram.bin : sram.ld sram.o flash01.o
	$(ARMGNU)-ld -o flash01.sram.elf -T sram.ld sram.o flash01.o
	$(ARMGNU)-objdump -D flash01.sram.elf > flash01.sram.list
	$(ARMGNU)-objcopy flash01.sram.elf flash01.sram.bin -O binary

