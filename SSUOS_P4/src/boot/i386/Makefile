all: bootloader.bin boot1.bin

bootloader.bin: bootloader.asm
	nasm -f bin bootloader.asm -o bootloader.bin -g
	cp bootloader.bin ../../
boot1.bin: boot1.asm
	nasm -f bin boot1.asm -o boot1.bin -g
	cp boot1.bin ../../
clean:
	rm -rf bootloader.bin
	rm -rf boot1.bin
