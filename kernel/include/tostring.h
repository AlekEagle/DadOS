#ifndef _KERNEL_TOSTRING_H
#define _KERNEL_TOSTRING_H

#include <stdint.h>

namespace std
{

  uint8_t charLength(uint64_t num, bool negative);
  void toString(char *c, int8_t n);
  void toString(char *c, int16_t n);
  void toString(char *c, int32_t n);
  void toString(char *c, int64_t n);

  void toString(char *c, uint8_t n);
  void toString(char *c, uint16_t n);
  void toString(char *c, uint32_t n);
  void toString(char *c, uint64_t n);
}

#endif