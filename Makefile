#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))
IMG_NAME = floppy.img
MNT_PATH = /mnt

CC = gcc
LD = ld
ASM = nasm

KERNEL_NAME = wos

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o $(KERNEL_NAME)

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) $(KERNEL_NAME)

.PHONY:update_image
update_image:
	mount $(IMG_NAME) $(MNT_PATH)
	cp $(KERNEL_NAME) $(MNT_PATH)/$(KERNEL_NAME)
	sleep 1
	umount $(MNT_PATH)

.PHONY:mount_image
mount_image:
	mount $(IMG_NAME) $(MNT_PATH)

.PHONY:umount_image
umount_image:
	umount $(MNT_PATH)

.PHONY:qemu
qemu:
	qemu-system-i386 -fda $(IMG_NAME) -boot a -nographic

.PHONY:bochs
bochs:
	bochs -f tools/bochsrc.txt

.PHONY:debug
debug:
	qemu-system-i386 -S -s -fda $(IMG_NAME) -boot a &
	sleep 1
	cgdb -x tools/gdbinit
