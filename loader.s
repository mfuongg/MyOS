[BITS 16]
[ORG 0x7C00]

KERNEL_LOAD_ADDR equ 0x8000
KERNEL_SECTORS   equ 15

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov si, msg_boot
.print:
    lodsb
    or al, al
    jz .after
    mov ah, 0x0E
    int 0x10
    jmp .print
.after:

    ; đọc kernel từ sector 2 trở đi
    mov bx, KERNEL_LOAD_ADDR
    mov dh, 0
    mov ch, 0
    mov cl, 2
    mov ah, 0x02
    mov al, KERNEL_SECTORS
    mov dl, [BOOT_DRIVE]
    int 0x13
    jc disk_error

    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_pm

[BITS 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    ; nhảy vào kernel
    call KERNEL_LOAD_ADDR

.hang:
    hlt
    jmp .hang

disk_error:
    mov si, msg_err
.err_loop:
    lodsb
    or al, al
    jz $
    mov ah, 0x0E
    int 0x10
    jmp .err_loop

msg_boot db "Booting MyOS...", 0
msg_err  db "Disk read error!", 0

gdt_start:
    dq 0
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10
BOOT_DRIVE db 0

times 510 - ($ - $$) db 0
dw 0xAA55