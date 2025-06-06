//
// Created by sophia on 5/22/25.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <limits.h>
#include <stdbool.h>

struct config {
  unsigned long memory_limit;  // memory limit for the process in kB
  short         verbosity;

  /**
   * This is flag for sandbox mode usage, Tharo provide 2 modes is syscall filter mode and sandbox isolated mode.
   *
   * With syscall filter mode, when process reached a now allowed syscall or reached resource limit, process will be terminated (SIGKILL).
   *
   * With sandbox isolated mode, process will run with fully allowed syscall but doesn't effect to main operating system.
   *
   * Config usage default is seccomp mode.
   */
  bool sandbox;
};

typedef struct config config_t;

void initialize_config(config_t *config);

#endif  //CONFIG_H
