#include <serial.h>

#include <stdint.h>
#include <bio.h>

namespace serial
{
  int init(uint16_t com)
  {
    bio::outb(com + 1, 0x00); // Disable all interrupts
    bio::outb(com + 3, 0x80); // Enable DLAB (set baud rate divisor)
    bio::outb(com + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    bio::outb(com + 1, 0x00); //                  (hi byte)
    bio::outb(com + 3, 0x03); // 8 bits, no parity, one stop bit
    bio::outb(com + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    bio::outb(com + 4, 0x0B); // IRQs enabled, RTS/DSR set
    bio::outb(com + 4, 0x1E); // Set in loopback mode, test the serial chip
    bio::outb(com + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    if (bio::inb(com + 0) != 0xAE)
    {
      return 1;
    }

    bio::outb(com + 4, 0x0F);
    return 0;
  }

  int received(uint16_t com)
  {
    return bio::inb(com + 5) & 1;
  }

  char read(uint16_t com)
  {
    while (received(com) == 0)
      ;
    return bio::inb(com);
  }

  int transmit_empty(uint16_t com)
  {
    return bio::inb(com + 5) & 0x20;
  }

  void write(uint16_t com, char a)
  {
    while (transmit_empty(com) == 0)
      ;
    bio::outb(com, a);
  }
}