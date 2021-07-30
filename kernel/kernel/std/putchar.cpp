#include <stdio.h>
#include <tty.h>
namespace std
{
  int putchar(int ic)
  {
    char c = (char)ic;
    tty::write(&c, sizeof(c));
    return ic;
  }

  void _putchar(char c)
  {
    tty::write(&c, sizeof(c));
  }
}