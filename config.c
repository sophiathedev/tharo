//
// Created by sophia on 5/22/25.
//

#include "config.h"

#include "macros.h"

void initialize_config(config_t *config) {
  config->verbosity    = 0;
  config->memory_limit = MEM_LIM_UNLIMITED;  // set into unlimited memory
}
