//
// Created by sophia on 5/22/25.
//

#include "logger.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static char *verbose_lbl[5]   = {"", "INFO", "DEBUG", "WARN", "ERROR"};
static char *verbose_color[5] = {
  ANSI_COLOR_RESET,   // DEFAULT
  ANSI_COLOR_RESET,   // INFO
  ANSI_COLOR_GREEN,   // DEBUG
  ANSI_COLOR_YELLOW,  // WARN
  ANSI_COLOR_RED,     // ERROR
};

void verbose_msg(const int required_verbose, const int current_verbose, const char *format, ...) {
  if (current_verbose < required_verbose && required_verbose != 0)
    return;

  const time_t     time_now   = time(NULLPTR);
  const struct tm *local_time = localtime(&time_now);

  char buf[80];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", local_time);
  const char *color = verbose_color[required_verbose];

  printf("[%s] %s%s: ", buf, color, verbose_lbl[required_verbose]);

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);

  printf("%s", ANSI_COLOR_RESET);
}
