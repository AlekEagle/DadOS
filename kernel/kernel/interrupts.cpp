#include <interrupts.h>
#include <stdlog.h>
#include <sys/idt.h>
#include <printf.h>

extern "C" void divide_by_zero_fault(idt::xframe_t *frame)
{
  std::warn("WARN: Divide by zero, code: %llu", frame->base_frame.vector);
  return;
}

extern "C" void keyboard_input(idt::xframe_t *frame)
{
  std::success("mmm tastey keyboard input...");
  return;
}

extern "C" void double_fault(idt::xframe_t *frame)
{
  std::error("FATAL: Unable to find interrupt for vector: %llu", frame->base_frame.vector);
  return;
}