global long_mode_start
global enable_external_interrupts
extern kernel_main

section .text
bits 64
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call kernel_main

    hlt

enable_external_interrupts:
    sti

    iretq