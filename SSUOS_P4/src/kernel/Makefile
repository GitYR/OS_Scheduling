DIR := ${CURDIR}

arch = ./arch
archx86 = ./arch/i386
lib = ./lib
device = ./device
mem = ./mem
proc = ./proc
BUILD_PATH = ./build
CFLAGS = -O0 -g -I./include -ffreestanding -m32 -nostdlib -nostdinc -static -fno-stack-protector
AFLAGS = -f elf32
ENTRY = ssuos_main
CC = gcc
NASM = nasm
BUILD_COMMAND = -o $(BUILD_PATH)/$@
COMMON_COMMAND = $(BUILD_COMMAND) -c $^ $(CFLAGS)

all: Main.bin

# SRCS=$(filter-out $(arch)/Main.c, $(wildcard *.c))
OBJS = $(BUILD_PATH)/Main.o $(BUILD_PATH)/io.o $(BUILD_PATH)/pit.o $(BUILD_PATH)/interrupt.o $(BUILD_PATH)/kbd.o $(BUILD_PATH)/crset.o $(BUILD_PATH)/paging.o \
		 $(BUILD_PATH)/vsprintk.o $(BUILD_PATH)/list.o $(BUILD_PATH)/sched.o $(BUILD_PATH)/switch.o $(BUILD_PATH)/proc.o $(BUILD_PATH)/console.o \
		  $(BUILD_PATH)/ssulib.o $(BUILD_PATH)/malloc.o $(BUILD_PATH)/mem.o $(BUILD_PATH)/mm.o $(BUILD_PATH)/device.o $(BUILD_PATH)/do_syscall.o \
		  $(BUILD_PATH)/syscall.o $(BUILD_PATH)/synch.o $(BUILD_PATH)/bitmap.o $(BUILD_PATH)/palloc.o $(BUILD_PATH)/intr-stubs.o \
		 $(BUILD_PATH)/string.o 
# OBJS = 
dummy:

#Main
Main.o: Main.s
	$(CC) -c $(BUILD_PATH)/$^ $(CFLAGS) -o $(BUILD_PATH)/Main.o
Main.s: $(arch)/Main.c
	$(CC) -c -S $^ $(CFLAGS) -o $(BUILD_PATH)/Main.s

#not belongs to any folder
%.o: %.c
	$(CC) $(COMMON_COMMAND)

#arch c files
%.o: $(arch)/%.c
	$(CC) $(COMMON_COMMAND)

#device
%.o: $(device)/%.c
	$(CC) $(COMMON_COMMAND)

#memory
%.o: $(mem)/%.c
	$(CC) $(COMMON_COMMAND)

#process
%.o: $(proc)/%.c
	$(CC) $(COMMON_COMMAND)


#arch assembly
io.o: $(archx86)/io.asm
	$(NASM) $(AFLAGS) $(archx86)/io.asm -o $(BUILD_PATH)/$@
crset.o: $(archx86)/crset.asm
	$(NASM) $(AFLAGS) $^ -o $(BUILD_PATH)/$@
mem.o: $(archx86)/mem.asm
	$(NASM) $(AFLAGS) $^ -o $(BUILD_PATH)/$@
switch.o: $(archx86)/switch.S
	$(CC) -c $^ $(CFLAGS) -o $(BUILD_PATH)/$@
intr-stubs.o: $(archx86)/intr-stubs.S
	$(CC) -c $^ $(CFLAGS) -o $(BUILD_PATH)/$@



# Main.elf: $(BUILD_PATH)/%.o
	# ld -Ttext 0x10000 $^ -o $(BUILD_PATH)/$@ -I./include --entry $(ENTRY)

Main.elf: Main.o io.o pit.o interrupt.o kbd.o crset.o paging.o vsprintk.o list.o \
	        sched.o switch.o proc.o console.o ssulib.o malloc.o mem.o mm.o device.o\
	    	do_syscall.o syscall.o synch.o bitmap.o palloc.o intr-stubs.o\
	    	string.o
	ld -Ttext 0x10000 $(OBJS) -o $(BUILD_PATH)/$@ -I./include --entry $(ENTRY)

Main.bin: Main.elf 
	objcopy -j .text -j .data -j .rodata -j .bss -S -O binary $(BUILD_PATH)/Main.elf $(BUILD_PATH)/Main.bin
	cp $(BUILD_PATH)/Main.bin ../

clean:
	# echo "asdfasdfasdf $(DIR)"
	rm -rf $(BUILD_PATH)/*.o
	rm -rf $(BUILD_PATH)/*.s
	rm -rf $(BUILD_PATH)/Main.elf
	rm -rf $(BUILD_PATH)/Main.bin

reset: clean all
