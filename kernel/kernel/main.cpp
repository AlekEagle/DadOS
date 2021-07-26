#include <stdio.h>
#include <tty.h>
#include <vga.h>
#include <stdlog.h>
#include <sys/idt.h>

void load_idt(InterruptDescriptorPointer *idt_r)
{
  __asm__("lidt %0" ::"m"(*idt_r));
}

extern "C" void kernel_main(void)
{

  tty::init();
  std::log("Initialized Display");
  std::success("Loaded into kernel");
  std::log("Initializing I/O");
  std::error("FATAL: Unable to initilize I/O (its not done yet)");
  std::success("Welcome to DadOS");
  std::println("");
  std::println("Testing of stdlog.cpp: ");

  std::info("Info");
  std::log("Log");
  std::debug("Debug");
  std::success("Success/Done/Completed");
  std::warn("Warn/Warning");
  std::error("Error/Failure");
  InterruptDescriptorPointer idk = {1, idt};
  load_idt(&idk);
}

/*
  TODO LIST: 
    - Handle keyboard inputs
    - Make a cursor (Invert background colour)
    - GUIS??????
*/