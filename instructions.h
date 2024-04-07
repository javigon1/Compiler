#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitpack.h"
#include "memory.h"

typedef uint32_t Um_instruction;

typedef struct Register *Register;
// typedef struct Instruction Instruction;

Um_instruction three_register(uint8_t op, uint32_t ra, uint32_t rb, uint32_t rc);
Um_instruction loadval(unsigned ra, unsigned val);

void halt(Memory memory);
void conditional_move(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void load_value(Memory memory, uint32_t segmentID, uint32_t offset, uint32_t reg);
void segmented_load(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void segmented_store(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void addition(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void multiplication(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void division(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void bitwise_nand(Memory memory, uint32_t rA, uint32_t rB, uint32_t rC);
void output(Memory memory, uint32_t rC);
void input(Memory memory, uint32_t rC);


#endif