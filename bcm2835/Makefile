ARMGNU ?= arm-none-eabi

AOPS = --warn --fatal-warnings -mcpu=arm1176jzf-s -march=armv6 -mfpu=vfp 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

LIB = -L /opt/gnuarm/arm-none-eabi/lib/ -L/Applications/yagarto-4.7.2/lib/gcc/arm-none-eabi/4.7.2

NOTMAIN = scheduler

gcc : $(NOTMAIN).hex $(NOTMAIN).bin

all : clean gcc clang 

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

custom.o : custom.c
	$(ARMGNU)-gcc $(COPS) -c custom.c -o custom.o

button_control.o : button_control.c
	$(ARMGNU)-gcc $(COPS) -c button_control.c -o button_control.o

relay.o : relay.c
	$(ARMGNU)-gcc $(COPS) -c relay.c -o relay.o

temp_lcd.o : temp_lcd.c
	$(ARMGNU)-gcc $(COPS) -c temp_lcd.c -o temp_lcd.o

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

bcm2835.o : bcm2835.c
	$(ARMGNU)-gcc $(COPS) -c bcm2835.c -o bcm2835.o

rpi_hd44780.o : rpi_hd44780.c
	$(ARMGNU)-gcc $(COPS) -c rpi_hd44780.c -o rpi_hd44780.o

mcp3202.o : mcp3202.c
	$(ARMGNU)-gcc $(COPS) -c mcp3202.c -o mcp3202.o

bcm2835_asm.o : bcm2835_asm.S
	$(ARMGNU)-gcc $(COPS) bcm2835_asm.S -D__ASSEMBLY__ -c -o bcm2835_asm.o

$(NOTMAIN).o : $(NOTMAIN).c
	$(ARMGNU)-gcc $(COPS) -c  $(NOTMAIN).c -o $(NOTMAIN).o

$(NOTMAIN).elf : memmap vectors.o button_control.o bcm2835.o bcm2835_asm.o mcp3202.o $(NOTMAIN).o rpi_hd44780.o custom.o relay.o temp_lcd.o
	$(ARMGNU)-ld vectors.o mcp3202.o custom.o button_control.o bcm2835.o bcm2835_asm.o temp_lcd.o rpi_hd44780.o relay.o $(NOTMAIN).o -T memmap -o $(NOTMAIN).elf $(LIB) -lc -lgcc 
	$(ARMGNU)-objdump -D $(NOTMAIN).elf > $(NOTMAIN).list

$(NOTMAIN).bin : $(NOTMAIN).elf
	$(ARMGNU)-objcopy $(NOTMAIN).elf -O binary $(NOTMAIN).bin

$(NOTMAIN).hex : $(NOTMAIN).elf
	$(ARMGNU)-objcopy $(NOTMAIN).elf -O ihex $(NOTMAIN).hex


LOPS = -Wall -m32 -emit-llvm
LLCOPS = -march=arm -mcpu=arm1176jzf-s
LLCOPS0 = -march=arm 
LLCOPS1 = -march=arm -mcpu=arm1176jzf-s
COPS = -Wall  -O2 -nostdlib -nostartfiles -ffreestanding
OOPS = -std-compile-opts

clang : $(NOTMAIN).clang.hex $(NOTMAIN).clang.bin

$(NOTMAIN).clang.bc : $(NOTMAIN).c
	clang $(LOPS) -c $(NOTMAIN).c -o $(NOTMAIN).clang.bc

$(NOTMAIN).clang.opt.elf : memmap vectors.o $(NOTMAIN).clang.bc
	opt $(OOPS) $(NOTMAIN).clang.bc -o $(NOTMAIN).clang.opt.bc
	llc $(LLCOPS) $(NOTMAIN).clang.opt.bc -o $(NOTMAIN).clang.opt.s
	$(ARMGNU)-as $(NOTMAIN).clang.opt.s -o $(NOTMAIN).clang.opt.o
	$(ARMGNU)-ld -o $(NOTMAIN).clang.opt.elf -T memmap vectors.o $(NOTMAIN).clang.opt.o
	$(ARMGNU)-objdump -D $(NOTMAIN).clang.opt.elf > $(NOTMAIN).clang.opt.list

$(NOTMAIN).clang.hex : $(NOTMAIN).clang.opt.elf
	$(ARMGNU)-objcopy $(NOTMAIN).clang.opt.elf $(NOTMAIN).clang.hex -O ihex

$(NOTMAIN).clang.bin : $(NOTMAIN).clang.opt.elf
	$(ARMGNU)-objcopy $(NOTMAIN).clang.opt.elf $(NOTMAIN).clang.bin -O binary
