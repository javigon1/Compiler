#ifndef UM_H_INCLUDED
#define UM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "seq.h"
#include <bitpack.h>
#include "instructions.h"
#include "memory.h"

/* run the program */
Instruction extract(uint32_t word, Instruction instruction);
int um();

#endif 