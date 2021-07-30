#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

#include <bio.h>
#include <stdint.h>

namespace serial
{

  struct
  {
    enum
    {
      COM1 = 0x3F8,
      COM2 = 0x2F8,
      COM3 = 0x3E8,
      COM4 = 0x2E8
    };
  } ports;
  int init(uint16_t com);
  int received(uint16_t com);
  char read(uint16_t com);
  int transmit_empty(uint16_t com);
  void write(uint16_t com, char a);
}

#endif