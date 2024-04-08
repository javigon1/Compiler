#ifndef LOADPROGRAM_H_INCLUDED
#define LOADPROGRAM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"

// CHANGE THIS TO MEMORY
void loadProgram(FILE *fp, Memory memory, uint32_t program_size);

#endif