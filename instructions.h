#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitpack.h"

typedef uint32_t Um_instruction;
typedef uint8_t Um_opcode;

typedef struct Register *Register;
typedef struct Instruction Instruction;

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
Um_instruction loadval(unsigned ra, unsigned val);

void halt();
void output(uint32_t registers[8], Instruction instruction);
void load_value(uint32_t registers[8], Instruction instruction);
void conditional_move(uint32_t registers[8], Instruction instruction);


#endif