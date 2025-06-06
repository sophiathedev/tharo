//
// Created by sophia on 6/6/25.
//

#include "safemem.h"

#include "logger.h"
#include "macros.h"
#include "messages.h"

INLINE void *safe_malloc(const size_t size) {
  void *block = malloc(size);

  if (block == NULLPTR)
    verbose_fatal("%s size %d at address %p\n", SAFEMEM_MALLOC_FAILURE, size, &block);

  return block;
}

INLINE void *safe_realloc(void *ptr, const size_t size) {
  void *block = realloc(ptr, size);

  if (block == NULLPTR)
    verbose_fatal("%s size %d from address %p to address %p\n", SAFEMEM_REALLOC_FAILURE, size, &ptr, &block);

  return block;
}
