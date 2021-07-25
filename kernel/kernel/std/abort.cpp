#include <stdio.h>
#include <stdlib.h>

namespace std
{
  __attribute__((__noreturn__)) void abort(void)
  {
    printf("kernel: panic: abort()\n");
    while (1)
    {
    }
    __builtin_unreachable();
  }
}