# Makefile
TARGET = kernel.bin
ISO = myos.iso

CC = i386-elf-gcc
LD = i386-elf-ld
AS = nasm
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld

all: $(ISO)

$(TARGET): multiboot_header.o kernel.o
	$(LD) $(LDFLAGS) -o $@ $^

multiboot_header.o: multiboot_header.asm
	$(AS) -f elf32 $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ISO): $(TARGET) grub/grub.cfg
	mkdir -p iso/boot/grub
	cp $(TARGET) iso/boot/kernel.bin
	cp grub/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

clean:
	rm -rf *.o *.bin iso $(ISO)
