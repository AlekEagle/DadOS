#ifndef _STDLOG_H
#define _STDLOG_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" namespace std
{
#endif

  void log(const char *__restrict, ...);
  void warn(const char *__restrict, ...);
  void error(const char *__restrict, ...);
  void info(const char *__restrict, ...);
  void debug(const char *__restrict, ...);
  void success(const char *__restrict, ...);

#ifdef __cplusplus
}
#endif

#endif
