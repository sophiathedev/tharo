//
// Created by sophia on 6/6/25.
//

#ifndef SAFEMEM_H
#define SAFEMEM_H

#include <stdlib.h>

void *safe_malloc(size_t size);
void *safe_realloc(void *ptr, size_t size);

#endif  //SAFEMEM_H
