ARMGNU ?= arm-none-eabi

AOPS = --warn --fatal-warnings -mcpu=arm1176jzf-s -march=armv6 -mfpu=vfp 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

LIB = -L /opt/gnuarm/arm-none-eabi/lib/ -L/Applications/yagarto-4.7.2/lib/gcc/arm-none-eabi/4.7.2

gcc : bcm2835.hex bcm2835.bin

all : gcc clang

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

bcm2835.o : bcm2835.c
	$(ARMGNU)-gcc $(COPS) -c bcm2835.c -o bcm2835.o

bcm2835_asm.o : bcm2835_asm.S
	$(ARMGNU)-gcc $(COPS) bcm2835_asm.S -D__ASSEMBLY__ -c -o bcm2835_asm.o

bcm2835.elf : memmap vectors.o bcm2835.o bcm2835_asm.o
	$(ARMGNU)-ld vectors.o bcm2835.o bcm2835_asm.o -T memmap -o bcm2835.elf $(LIB) -lc -lgcc
	$(ARMGNU)-objdump -D bcm2835.elf > bcm2835.list

bcm2835.bin : bcm2835.elf
	$(ARMGNU)-objcopy bcm2835.elf -O binary bcm2835.bin

bcm2835.hex : bcm2835.elf
	$(ARMGNU)-objcopy bcm2835.elf -O ihex bcm2835.hex


LOPS = -Wall -m32 -emit-llvm
LLCOPS = -march=arm -mcpu=arm1176jzf-s
LLCOPS0 = -march=arm 
LLCOPS1 = -march=arm -mcpu=arm1176jzf-s
COPS = -Wall  -O2 -nostdlib -nostartfiles -ffreestanding
OOPS = -std-compile-opts

clang : bcm2835.clang.hex bcm2835.clang.bin

bcm2835.clang.bc : bcm2835.c
	clang $(LOPS) -c bcm2835.c -o bcm2835.clang.bc

bcm2835.clang.opt.elf : memmap vectors.o bcm2835.clang.bc
	opt $(OOPS) bcm2835.clang.bc -o bcm2835.clang.opt.bc
	llc $(LLCOPS) bcm2835.clang.opt.bc -o bcm2835.clang.opt.s
	$(ARMGNU)-as bcm2835.clang.opt.s -o bcm2835.clang.opt.o
	$(ARMGNU)-ld -o bcm2835.clang.opt.elf -T memmap vectors.o bcm2835.clang.opt.o
	$(ARMGNU)-objdump -D bcm2835.clang.opt.elf > bcm2835.clang.opt.list

bcm2835.clang.hex : bcm2835.clang.opt.elf
	$(ARMGNU)-objcopy bcm2835.clang.opt.elf bcm2835.clang.hex -O ihex

bcm2835.clang.bin : bcm2835.clang.opt.elf
	$(ARMGNU)-objcopy bcm2835.clang.opt.elf bcm2835.clang.bin -O binary
