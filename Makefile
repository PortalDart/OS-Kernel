TARGET = kernel.bin
ISO = myos.iso

CC = i386-elf-gcc
LD = i386-elf-ld
AS = nasm
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld

BUILD_DIR = build
OBJ_FILES = $(BUILD_DIR)/multiboot_header.o $(BUILD_DIR)/kernel.o

all: $(ISO)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(BUILD_DIR)/multiboot_header.o: multiboot_header.asm | $(BUILD_DIR)
	$(AS) -f elf32 $< -o $@

$(BUILD_DIR)/kernel.o: kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ISO): $(TARGET) grub/grub.cfg
	mkdir -p iso/boot/grub
	cp $(TARGET) iso/boot/kernel.bin
	cp grub/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

clean:
	rm -rf $(BUILD_DIR) *.bin iso $(ISO)
