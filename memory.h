#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <seq.h>


typedef struct Memory *Memory;


Memory Segment_new();
void Segment_free(Segment memory);
uint32_t Segment_map();
void Segment_unmap();



#endif
