%macro pushagrd 0
push rax
push rbx
push rcx
push rdx
push rsi
push rdi
%endmacro

%macro popagrd 0
pop rdi
pop rsi
pop rdx
pop rcx
pop rbx
pop rax
%endmacro

%macro pushacrd 0
mov rax, cr0
push rax
mov rax, cr2
push rax
mov rax, cr3
push rax
mov rax, cr4
push rax
%endmacro

%macro popacrd 0
pop rax
mov cr4, rax
pop rax
mov cr3, rax
pop rax
mov cr2, rax
pop rax
mov cr0, rax
%endmacro

%macro err_code 1
push %1
%endmacro

%macro no_err_code 1
push 0
push %1
%endmacro

%macro construct_frame 0
push rbp
mov rbp, rsp
pushagrd
pushacrd
mov ax, ds
push rax
push qword 0
mov ax, 0x10
mov ds, ax
mov es, ax
mov ss, ax

lea rdi, [rsp + 0x10]
%endmacro

%macro destruct_frame 0
pop rax
pop rax
mov ds, ax
mov es, ax
popacrd
popagrd
pop rbp
add rsp, 0x10
%endmacro

global divide_by_zero_fault_asm
extern divide_by_zero_fault
divide_by_zero_fault_asm:
    no_err_code 0
    construct_frame
    call divide_by_zero_fault
    destruct_frame
    iretq

global keyboard_input_asm
extern keyboard_input
keyboard_input_asm:
    no_err_code 33
    construct_frame
    call keyboard_input
    destruct_frame
    iretq

global double_fault_asm
extern double_fault
double_fault_asm:
    err_code 8
    construct_frame
    call double_fault
    destruct_frame
    iretq