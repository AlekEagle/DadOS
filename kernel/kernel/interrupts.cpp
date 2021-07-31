#include <interrupts.h>
#include <stdlog.h>
#include <sys/idt.h>
#include <printf.h>
#include <sys/pic.h>
#include <bio.h>

extern "C" void divide_by_zero_fault(idt::xframe_t *frame)
{
  std::warn("WARN: Divide by zero.");
  return;
}

extern "C" void double_fault(idt::xframe_t *frame)
{
  std::error("FATAL: Unable to find interrupt!");
  return;
}

extern "C" void general_protection_fault(idt::xframe_t *frame)
{
  std::error("FATAL: General Protection Fault! Code: %llu", frame->base_frame.error_code);
  return;
}

extern "C" void keyboard_input(idt::xframe_t *frame)
{
  std::success("mmm tastey keyboard input... scancode from the keyboard is: %X", bio::inb(0x60));
  pic::handled(1);
  return;
}