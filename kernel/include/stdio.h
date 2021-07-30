#ifndef _STDIO_H
#define _STDIO_H

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" namespace std
{
#endif

  int putchar(int);
  void _putchar(char);
  int puts(const char *);

#ifdef __cplusplus
}
#endif

#endif
