
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

ARCH = -mcpu=cortex-m0
xAOPS = --warn --fatal-warnings $(ARCH)
AOPS = --warn $(ARCH)
xCOPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding $(ARCH)
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding $(ARCH)

gcc : uart02.bin uart02.sram.bin

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

uart02.o : uart02.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c uart02.c -o uart02.o

uart02.bin :     flash.ld flash.o uart02.o
	$(ARMGNU)-ld -T flash.ld flash.o uart02.o -o uart02.elf 
	$(ARMGNU)-objdump -D uart02.elf > uart02.list
	$(ARMGNU)-objcopy uart02.elf uart02.bin -O binary

uart02.sram.bin : sram.ld sram.o uart02.o
	$(ARMGNU)-ld  -T sram.ld sram.o uart02.o -o uart02.sram.elf
	$(ARMGNU)-objdump -D uart02.sram.elf > uart02.sram.list
	$(ARMGNU)-objcopy uart02.sram.elf uart02.sram.hex -O ihex
	$(ARMGNU)-objcopy uart02.sram.elf uart02.sram.bin -O binary

#---------------------------------

