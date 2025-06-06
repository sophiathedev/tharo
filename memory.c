//
// Created by sophia on 5/22/25.
//

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "logger.h"
#include "macros.h"

#define MEM_MEMTOTAL     0
#define MEM_MEMFREE      1
#define MEM_BUFFERS      2
#define MEM_CACHED       3
#define MEM_SRECLAIMABLE 4
#define MEM_SHMEM        5

static const char *proc_meminfo_field[6] = {"MemTotal", "MemFree", "Buffers", "Cached", "SReclaimable", "Shmem"};

INLINE REGPARM(1) void initialize_mem_info(meminfo_t *info) {
#ifdef __linux__
  FILE *proc_meminfo = fopen("/proc/meminfo", "r");
  if (proc_meminfo == NULL) {
    verbose_msg(VERBOSE_ERROR, VERBOSE_ALL, "Cannot open /proc/meminfo.");
    exit(EXIT_FAILURE);
  }

  char line[256];
  while (fgets(line, sizeof(line), proc_meminfo)) {
    char *key = strtok(line, ":");
    if (!key)
      continue;

    char *valstr = strtok(NULLPTR, "kB");
    if (!valstr)
      continue;

    const unsigned long value = strtoul(valstr, NULLPTR, 10);
    int idx                   = -1;
    for (int i = 0; i < 6; ++i) {
      if (strcmp(key, proc_meminfo_field[i]) == 0) {
        idx = i;
        break;
      }
    }

    switch (idx) {
      case MEM_MEMTOTAL:
        info->total_mem = value;
        break;
      case MEM_MEMFREE:
        info->mem_free = value;
        break;
      case MEM_BUFFERS:
        info->buffers = value;
        break;
      case MEM_CACHED:
        info->cached = value;
        break;
      case MEM_SRECLAIMABLE:
        info->s_reclaimable = value;
        break;
      case MEM_SHMEM:
        info->shmem = value;
        break;
      default:
        break;
    }
  }

  fclose(proc_meminfo);
#endif
}

/**
 * Get current free memory blocks in system.
 *
 * Free memory calculation based on htop which is the sum of freemem, buffers, cached, reclaimable and shmem information in /proc/meminfo file.
 * Use sysinfo is deprecated because sysinfo does not discriminate buffers, cached, reclaimable and shmem.
 *
 * Currently supported only Linux.
 *
 * @param info Memory allocated information
 * @return Free memory block integers in kB unit
 */
INLINE REGPARM(1) unsigned long calculate_free_mem_blocks(const meminfo_t *info) {
#ifdef __linux__
  return info->mem_free + info->buffers + info->cached + info->s_reclaimable - info->shmem;
#endif
}

static CONSTEXPR long blocks_threshold[] = {0, 1024, 1048576, 1073741824, 1099511627776};
static char *blocks_unit[]               = {"kB", "MB", "GB", "TB", "PB"};

__attribute__((optimize("unroll-loops"))) INLINE REGPARM(2) void get_readable_mem_blocks(char *buf, const unsigned long blocks) {
  if (blocks == MEM_LIM_UNLIMITED) {
    sprintf(buf, "unlimited");
    return;
  }

  long threshold = -1;
  char *buf_unit = "\0";
  for (int i = 0; i < 5; ++i) {
    if (blocks < blocks_threshold[i])
      break;

    threshold = blocks_threshold[i];
    buf_unit  = blocks_unit[i];
  }

  const double converted_blocks = (double)blocks / (double)threshold;
  sprintf(buf, "%.2f %s", converted_blocks, buf_unit);
}
