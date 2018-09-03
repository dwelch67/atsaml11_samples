
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

ARCH = -mcpu=cortex-m0
xAOPS = --warn --fatal-warnings $(ARCH)
AOPS = --warn $(ARCH)
xCOPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding $(ARCH)
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding $(ARCH)

gcc : blinker02.bin blinker02.sram.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.bc
	rm -f *.opt.s
	rm -f *.norm.s
	rm -f *.hex

#---------------------------------

flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

blinker02.o : blinker02.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker02.c -o blinker02.o

blinker02.bin :     flash.ld flash.o blinker02.o
	$(ARMGNU)-ld -T flash.ld flash.o blinker02.o -o blinker02.elf 
	$(ARMGNU)-objdump -D blinker02.elf > blinker02.list
	$(ARMGNU)-objcopy blinker02.elf blinker02.bin -O binary

blinker02.sram.bin : sram.ld sram.o blinker02.o
	$(ARMGNU)-ld  -T sram.ld sram.o blinker02.o -o blinker02.sram.elf
	$(ARMGNU)-objdump -D blinker02.sram.elf > blinker02.sram.list
	$(ARMGNU)-objcopy blinker02.sram.elf blinker02.sram.hex -O ihex
	$(ARMGNU)-objcopy blinker02.sram.elf blinker02.sram.bin -O binary

#---------------------------------

