#include <stdlog.h>
#include <stdio.h>
#include <tty.h>
#include <stdarg.h>
#include <vga.h>

/* 
  void log(const char *__restrict, ...); [ ADDED ]
  void warn(const char *__restrict, ...); [ ADDED ]
  void error(const char *__restrict, ...); [ ADDED ]
  void info(const char *__restrict, ...); [ ADDED ]
  void debug(const char *__restrict, ...); [ ADDED ]
  void success(const char *__restrict, ...); [ ADDED ]
*/

namespace std
{
  void log(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    std::printf("[ ");
    tty::setColor(vga::entryColor(vga::color.GREEN, vga::color.BLACK));
    std::printf("#");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf(" ] ");
    std::println(format, parameters);
  }

  void info(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    std::printf("[ ");
    tty::setColor(vga::entryColor(vga::color.DARK_GREY, vga::color.BLACK));
    std::printf("?");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf(" ] ");
    std::println(format, parameters);
  }

  void success(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    std::printf("[ ");
    tty::setColor(vga::entryColor(vga::color.LIGHT_GREEN, vga::color.BLACK));
    std::printf("/");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf(" ] ");
    std::println(format, parameters);
  }

  void debug(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    std::printf("[ ");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf("-");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf(" ] ");
    std::println(format, parameters);
  }

  void warn(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    std::printf("[ ");
    tty::setColor(vga::entryColor(vga::color.LIGHT_RED, vga::color.BLACK));
    std::printf("\x1E");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf(" ] ");
    std::println(format, parameters);
  }

  void error(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    std::printf("[ ");
    tty::setColor(vga::entryColor(vga::color.RED, vga::color.BLACK));
    std::printf("!");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    std::printf(" ] ");
    std::println(format, parameters);
  }
}