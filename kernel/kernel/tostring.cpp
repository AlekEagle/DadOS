#include <tostring.h>
#include <stdint.h>

static int asciiZero = 0x30;

void __toString(char *c, int num)
{
  bool negative = false;
  if (num < 0)
    negative = true;
  uint8_t len = std::charLength((uint64_t)num, negative);
  int pDividend = num;
  bool done = false;
  char tmp[len - (negative ? 1 : 0)];
  tmp[0] = '\0';

  for (int i = 1; !done; i++)
  {
    int dividend = pDividend / 10;
    int remainder = pDividend % 10;
    if (dividend < 1)
    {
      tmp[i] = (char)(asciiZero + remainder);
      done = true;
    }
    else
    {
      pDividend = dividend;
      tmp[i] = (char)(asciiZero + remainder);
    }
  }

  if (negative)
    c[0] = '-';
  int ind = negative ? 1 : 0;

  for (int i = len - 1; i >= 0; i--)
  {
    c[ind++] = tmp[i];
  }

  return;
}

namespace std
{

  uint8_t charLength(uint64_t num, bool negative)
  {
    uint8_t len = negative ? 3 : 2;
    uint64_t pDividend = num;
    bool done = false;

    for (int i = 0; !done; i++)
    {
      uint64_t dividend = pDividend / 10;
      if (dividend < 1)
      {
        done = true;
      }
      else
      {
        pDividend = dividend;
        len++;
      }
    }
    return len;
  }

  void toString(char *c, uint8_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, uint16_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, uint32_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, uint64_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, int8_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, int16_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, int32_t num)
  {
    return __toString(c, num);
  }
  void toString(char *c, int64_t num)
  {
    return __toString(c, num);
  }
}