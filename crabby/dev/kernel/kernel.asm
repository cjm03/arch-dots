;;kernel.asm
bits 32                     ;nasm directive - 32bit
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002               ;magic number
        dd 0x00                     ;flags
        dd - (0x1BADB002 + 0x00)    ;checksum. m+f+c should = 0

global start
extern kmain                ;kmain: defined in c file

start:
    cli                     ;block interrupts
    mov esp, stack_space    ;set stack pointer
    call kmain
    hlt                     ;halt

section .bss
resb 8192                   ;8KB for stack
stack_space:
