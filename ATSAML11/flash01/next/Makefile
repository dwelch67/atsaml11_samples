
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

#AOPS = --warn -mcpu=cortex-m23
AOPS = --warn -mcpu=cortex-m0

gcc : notmain.bin 


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

notmain.bin : 	    flash.ld flash.o 
	$(ARMGNU)-ld -T flash.ld flash.o -o notmain.elf
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy notmain.elf notmain.bin -O binary

