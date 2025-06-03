//
// Created by sophia on 5/22/25.
//

#ifndef MEMORY_H
#define MEMORY_H

struct meminfo {
  // all of these field in kB unit
  unsigned long total_mem;
  unsigned long mem_free;
  unsigned long buffers;
  unsigned long cached;
  unsigned long s_reclaimable;
  unsigned long shmem;
};

typedef struct meminfo meminfo_t;

void          initialize_mem_info( meminfo_t *info );
unsigned long calculate_free_mem_blocks( const meminfo_t *info );
void          get_readable_mem_blocks( char *buf, unsigned long blocks );

#endif  //MEMORY_H
