all: bootloader kernel disk.img

bootloader: dummy
	@echo 
	@echo =============== Start bootloader Build ===============
	@echo  
	make -C boot/i386
	@echo	
	@echo =============== complete bootloader Build ===============
	@echo

dummy:

kernel: dummy
	@echo 
	@echo =============== Start Kernel Build ===============
	@echo 
	make -C kernel
	@echo	
	@echo =============== Complete Kernel Build ===============
	@echo

disk.img: dummy 
	@echo
	@echo =============== Start Disk Image Build ===============
	@echo
	cat bootloader.bin boot1.bin Main.bin > disk.bin
	dd if=disk.bin of=disk.img bs=10240000 seek=0 count=1 conv=notrunc
	cp -f disk.img ../bochs
	@echo
	@echo =============== Complete Disk Image build ================
	@echo
	@echo
	@echo =============== Complete all Build ===============
	@echo

disk:
	bximage

run:
	make -C ../bochs run

debug:
	make -C ../bochs debug

rs:
	make -C ../bochs runSerial

ds:
	make -C ../bochs debugSerial

rt:
	make -C ../bochs runTerm

dt:
	make -C ../bochs debugTerm

re: clean all

gdb:
	gdb kernel/Main.elf -command cmd.gdb

find:
	ps -ef | grep bochs

clean:
	make -C boot/i386 clean
	make -C kernel clean
	make -C ../bochs clean
	rm -rf disk.bin
	rm -rf bootloader.bin
	rm -rf Main.bin
	rm -rf boot1.bin

cleanAll: ca

ca:
	clean unset

set:
	ctags -R
	touch tmp
	mkcscope.sh < tmp
	rm tmp

unset:
	rm -rf tags ../tags
	rm -rf cscope.* ../cscope.*

