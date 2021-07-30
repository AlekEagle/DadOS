#ifndef _KERNEL_BIO_H
#define _KERNEL_BIO_H

#include <stdint.h>

namespace bio
{
  void outb(uint16_t port, uint8_t value);
  uint8_t inb(uint16_t port);
  uint16_t inw(uint16_t port);
}

#endif