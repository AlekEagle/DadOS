#include <stdio.h>
#include <tty.h>
#include <vga.h>
#include <stdlog.h>

extern "C" void kernel_main(void)
{
  tty::init();
  std::log("Initialized Display");
  std::info("Loaded into kernel");
  std::error("FATAL: Unable to find 'joe moma'");
  std::println("");
  std::println("Testing of stdlog.cpp: ");

  std::info("Info");
  std::log("Log");
  std::debug("Debug");
  std::success("Success/Done/Completed");
  std::warn("Warn/Warning");
  std::error("Error/Failure");
}
// knots