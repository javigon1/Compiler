#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <seq.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include <assert.h>

/* memory struct declared here */
typedef struct Memory *Memory;

Memory new_memory();
void free_memory(Memory memory);
uint32_t segment_map(Memory memory, uint32_t size);
void segment_unmap(Memory memory, uint32_t segmentID);
uint32_t get_register(Memory memory, uint32_t register_index);
void set_register(Memory memory, uint register_index, uint32_t value);
Seq_T get_segments(Memory memory);
void set_segments(Memory memory, int index, Seq_T segments);
void set_program_counter(Memory memory, uint32_t value);

#endif