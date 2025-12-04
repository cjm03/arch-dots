; ASSEMBLE; nasm -f elf32 hello.asm -o hello.o LINK: ld -m elf_i386 -s -o hello hello.o
section .data
    msg db 'Hello, world!', 0xA ; Message with newline

section .text
    global _start

_start:
    ; Write to stdout (file desc 1)
    mov eax, 4              ; syscall number for sys_write      load eax register with 4
    mov ebx, 1              ; file desc 1 (stdout)              load ebx register with 1
    mov ecx, msg            ; pointer to the message            load ecx register with address of msg
    mov edx, 14             ; number of bytes                   load edx register with 14, the number of bytes to write
    int 0x80                ; make the system call              trigger interrupt which passes control to kernel to execute the system call

    ; Exit the program
    mov eax, 1              ; syscall number for sys_exit       load eax register with 1
    xor ebx, ebx            ; return code 0                     load ebx register with 0, the result of XORing ebx with itself
    int 0x80                ; make the system call              trigger interrupt, passing control to kernel to terminate the program
