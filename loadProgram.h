/*
 *     loadProgram.h
 *     Javier Gonzalez (jgonza20) and Jordan Pittignano (jpitti01)
 *     4/11/24
 *     um
 *
 *     TODO: summary
 */

#ifndef LOADPROGRAM_H_INCLUDED
#define LOADPROGRAM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"
#include <bitpack.h>

// CHANGE THIS TO MEMORY
Seq_T loadProgram(FILE *fp, uint64_t program_size);

#endif