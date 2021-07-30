#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "tty.h"

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

namespace tty
{

  void init()
  {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga::entryColor(vga::color.WHITE, vga::color.BLACK);
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
      for (size_t x = 0; x < VGA_WIDTH; x++)
      {
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga::entry(' ', terminal_color);
      }
    }
  }

  void setColor(uint8_t color)
  {
    terminal_color = color;
  }

  void entryAt(unsigned char c, uint8_t color, size_t x, size_t y)
  {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga::entry(c, color);
  }

  void putChar(char c)
  {
    if (c == '\n')
    {
      lineBreak();
      return;
    }
    unsigned char uc = c;
    entryAt(uc, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
      terminal_column = 0;
      if (++terminal_row == VGA_HEIGHT)
        terminal_row = 0;
    }
  }

  void write(const char *data, size_t size)
  {
    for (size_t i = 0; i < size; i++)
      putChar(data[i]);
  }

  void writeString(const char *data)
  {
    write(data, std::strlen(data));
  }

  void lineBreak()
  {
    terminal_row++;
    terminal_column = 0;
  }
}