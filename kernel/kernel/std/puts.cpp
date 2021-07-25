#include <stdio.h>

namespace std
{
  int puts(const char *string)
  {
    return printf("%s\n", string);
  }
}