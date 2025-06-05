//
// Created by sophia on 5/22/25.
//

#include "logger.h"

#include <stdio.h>
#include <time.h>

static char *verbose_lbl[5] = {"", "INFO", "DEBUG", "WARN", "ERROR"};

void verbose_msg(const int required_verbose, const int current_verbose, const char *format, ...) {
  if (current_verbose < required_verbose && required_verbose != 0)
    return;

  const time_t     time_now   = time(nullptr);
  const struct tm *local_time = localtime(&time_now);

  char buf[80];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", local_time);
  printf("[%s] %s: ", buf, verbose_lbl[required_verbose]);

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}
