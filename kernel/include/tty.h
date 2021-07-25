#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

namespace tty
{
  void init();
  void putChar(char c);
  void write(const char *data, size_t size);
  void writeString(const char *data);
  void setColor(uint8_t color);
  void lineBreak();
}

#endif