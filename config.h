//
// Created by sophia on 5/22/25.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <limits.h>

#define MEM_LIM_UNLIMITED ULONG_MAX

struct config {
  unsigned long memory_limit;  // memory limit for the process in kB
  short         verbosity;
};

typedef struct config config_t;

void initialize_config(config_t *config);

#endif  //CONFIG_H
