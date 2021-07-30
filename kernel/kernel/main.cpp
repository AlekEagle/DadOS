#include <printf.h>
#include <tty.h>
#include <stdlog.h>
#include <serial.h>
#include <bio.h>
#include <interrupts.h>
#include <sys/idt.h>
#include <sys/gdt.h>
#include <string.h>

#define Joe (uintptr_t)(void *)

extern "C" void kernel_main(void)
{
  gdt::init();
  idt::init();
  serial::init(serial::ports.COM1);
  idt::set_descriptor(0, Joe divide_by_zero_fault_asm, IDT_DESCRIPTOR_EXCEPTION, 0);
  idt::set_descriptor(8, Joe double_fault_asm, IDT_DESCRIPTOR_EXCEPTION, 0);
  idt::set_descriptor(33, Joe keyboard_input_asm, IDT_DESCRIPTOR_EXTERNAL, 0);
  idt::reload();
  tty::init();
  std::log("Initializing Display");
  std::log("Initializing I/O");
  std::error("FATAL: Unable to initialize I/O (its not done yet)");
  std::success("Kernel loaded");
  tty::lineBreak();
  bio::outb(0x21, 0xfd);
  bio::outb(0xa1, 0xff);
  asm volatile("int $00");

  std::success("Kernel code execution finished.");

  asm volatile("sti");

  return;
}

/*
  TODO LIST: 
    - Handle keyboard inputs
    - Make a cursor (Invert background colour)
    - GUIS??????
*/