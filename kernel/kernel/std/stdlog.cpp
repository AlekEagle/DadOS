#include <stdlog.h>
#include <printf.h>
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
    printf("[ ");
    tty::setColor(vga::entryColor(vga::color.GREEN, vga::color.BLACK));
    printf("#");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf(" ] ");
    vprintf(format, parameters);
    printf("\n");
  }

  void info(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    printf("[ ");
    tty::setColor(vga::entryColor(vga::color.DARK_GREY, vga::color.BLACK));
    printf("?");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf(" ] ");
    vprintf(format, parameters);
    printf("\n");
  }

  void success(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    printf("[ ");
    tty::setColor(vga::entryColor(vga::color.LIGHT_GREEN, vga::color.BLACK));
    printf("/");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf(" ] ");
    vprintf(format, parameters);
    printf("\n");
  }

  void debug(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    printf("[ ");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf("-");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf(" ] ");
    vprintf(format, parameters);
    printf("\n");
  }

  void warn(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    printf("[ ");
    tty::setColor(vga::entryColor(vga::color.LIGHT_RED, vga::color.BLACK));
    printf("\x1E");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf(" ] ");
    vprintf(format, parameters);
    printf("\n");
  }

  void error(const char *format, ...)
  {
    va_list parameters;
    va_start(parameters, format);
    printf("[ ");
    tty::setColor(vga::entryColor(vga::color.RED, vga::color.BLACK));
    printf("!");
    tty::setColor(vga::entryColor(vga::color.WHITE, vga::color.BLACK));
    printf(" ] ");
    vprintf(format, parameters);
    printf("\n");
  }
}