//
// Created by sophia on 5/22/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

void verbose_msg(int required_verbose, int current_verbose, const char *format, ...);

#define verbose_error(format, ...) verbose_msg(VERBOSE_ERROR, VERBOSE_ERROR, format, __VA_ARGS__)
#define verbose_fatal(format, ...)      \
  {                                     \
    verbose_error(format, __VA_ARGS__); \
    exit(EXIT_FAILURE);                 \
  }

#endif  //LOGGER_H
