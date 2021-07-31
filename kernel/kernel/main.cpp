#include <tty.h>
#include <stdlog.h>
#include <serial.h>
#include <bio.h>
#include <interrupts.h>
#include <sys/idt.h>
#include <sys/gdt.h>
#include <sys/pic.h>

#define Joe (uintptr_t)(void *)

void kernel_loop()
{
  while (true)
  {
    asm volatile("hlt");
  }
}

extern "C" void kernel_main(void)
{
  gdt::init();
  idt::init();
  serial::init(serial::ports.COM1);
  pic::remap(0x20, 0x28);
  idt::set_descriptor(0, Joe divide_by_zero_fault_asm, IDT_DESCRIPTOR_EXCEPTION, 0);
  idt::set_descriptor(8, Joe double_fault_asm, IDT_DESCRIPTOR_EXCEPTION, 0);
  idt::set_descriptor(13, Joe general_protection_fault_asm, IDT_DESCRIPTOR_EXCEPTION, 0);
  idt::set_descriptor(33, Joe keyboard_input_asm, IDT_DESCRIPTOR_EXTERNAL, 0);
  idt::reload();
  tty::init();
  std::log("Initializing Display");
  std::log("Initializing I/O");
  asm volatile("sti");
  std::success("Kernel loaded.");
  std::success("Welcome to DadOS!");
  tty::lineBreak();
  bio::outb(0x21, 0xfd);
  bio::outb(0xa1, 0xff);
  asm volatile("int $00");

  std::success("Kernel code execution finished.");

  kernel_loop();

  return;
}

/*
  TODO LIST: 
    - Make a cursor (Invert background colour)
    - GUIS??????
*/