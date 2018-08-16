
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

xMCPU = -mcpu=cortex-m22
AOPS = --warn --fatal-warnings $(MCPU)
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding $(MCPU)

all : flash01.sram.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.bc
	rm -f *.opt.s
	rm -f *.norm.s
	rm -f *.hex
	rm -f bintoh

#---------------------------------

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

flash01.o : flash01.c flash-bin.h
	$(ARMGNU)-gcc $(COPS) -mthumb -c flash01.c -o flash01.o

flash01.sram.bin : sram.ld sram.o flash01.o
	$(ARMGNU)-ld -o flash01.sram.elf -T sram.ld sram.o flash01.o
	$(ARMGNU)-objdump -D flash01.sram.elf > flash01.sram.list
	$(ARMGNU)-objcopy flash01.sram.elf flash01.sram.hex -O ihex
	$(ARMGNU)-objcopy flash01.sram.elf flash01.sram.bin -O binary

bintoh : bintoh.c
	gcc -O2 bintoh.c -o bintoh

flash-bin.h : bintoh flash-bin
	./bintoh flash-bin flash-bin.h
	
