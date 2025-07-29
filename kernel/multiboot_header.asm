; multiboot_header.asm
section .multiboot
align 4
multiboot_header:
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002 + 0x00)

section .text
global _start
_start:
    extern kernel_main
    call kernel_main
    cli
.hang:
    hlt
    jmp .hang
