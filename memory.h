#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <seq.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include <assert.h>

typedef struct Memory *Memory;

Memory segment_new();
void segment_free(Memory memory);
uint32_t segment_map(Memory memory, uint32_t size);
void segment_unmap(Memory memory);

#endif