
ARMGNU ?= arm-none-eabi

AOPS = --warn
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m4 -mthumb

all : notmain.sram.bin

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

notmain.o : notmain.c
	$(ARMGNU)-gcc $(COPS)  -c notmain.c -o notmain.o

notmain.sram.bin :  sram.ld sram.o notmain.o 
	$(ARMGNU)-ld      -T sram.ld sram.o notmain.o -o notmain.sram.elf
	$(ARMGNU)-objdump -D notmain.sram.elf > notmain.sram.list
	$(ARMGNU)-objcopy notmain.sram.elf notmain.sram.bin -O binary

