#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <seq.h>


typedef struct Segment *Segment;


Segment Segment_new();
void Segment_free(Segment memory);
uint32_t Segment_map();
void Segment_unmap();
int Segment_length();


#endif
