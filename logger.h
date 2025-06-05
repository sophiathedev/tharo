//
// Created by sophia on 5/22/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

void verbose_msg(int required_verbose, int current_verbose, const char *format, ...);

#endif  //LOGGER_H
