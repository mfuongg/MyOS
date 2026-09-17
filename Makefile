AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld
OBJCOPY = i686-elf-objcopy

CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS = -T linker.ld -m elf_i386

BOOTLOADER = loader.bin
KERNEL_ELF = kernel.elf
KERNEL_BIN = kernel.bin
IMG = os-image.img
ISO = mykernel.iso

all: $(IMG)

$(BOOTLOADER): loader.s
	$(AS) -f bin loader.s -o $(BOOTLOADER)

kernel.o: kernel.cpp
	$(CC) $(CFLAGS) -c kernel.cpp -o kernel.o

keyboard.o: keyboard.cpp
	$(CC) $(CFLAGS) -c keyboard.cpp -o keyboard.o

shell.o: shell.cpp
	$(CC) $(CFLAGS) -c shell.cpp -o shell.o

$(KERNEL_ELF): kernel.o keyboard.o shell.o linker.ld
	$(LD) $(LDFLAGS) kernel.o keyboard.o shell.o -o $(KERNEL_ELF)

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $(KERNEL_ELF) $(KERNEL_BIN)

$(IMG): $(BOOTLOADER) $(KERNEL_BIN)
	dd if=/dev/zero of=$(IMG) bs=512 count=2880 2>/dev/null
	dd if=$(BOOTLOADER) of=$(IMG) conv=notrunc 2>/dev/null
	dd if=$(KERNEL_BIN) of=$(IMG) bs=512 seek=1 conv=notrunc 2>/dev/null

$(ISO): $(IMG)
	mkdir -p iso/boot
	cp $(IMG) iso/boot/os-image.img
	hdiutil makehybrid -iso -joliet -o $(ISO) iso >/dev/null

run: $(IMG)
	qemu-system-i386 -fda $(IMG) -boot a -m 64M

clean:
	rm -f *.o *.elf *.bin $(IMG) $(ISO)
	rm -rf iso