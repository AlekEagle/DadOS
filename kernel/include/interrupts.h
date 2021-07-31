#ifndef _KERNEL_INTERRUPTS_H
#define _KERNEL_INTERRUPTS_H

#include <sys/idt.h>

extern "C" void divide_by_zero_fault_asm();
extern "C" void divide_by_zero_fault(idt::xframe_t *frame);

extern "C" void keyboard_input_asm();
extern "C" void keyboard_input(idt::xframe_t *frame);

extern "C" void double_fault_asm();
extern "C" void double_fault(idt::xframe_t *frame);

extern "C" void general_protection_fault_asm();
extern "C" void general_protection_fault(idt::xframe_t *frame);

#endif