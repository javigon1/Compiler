#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

#include "memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitpack.h"
#include <assert.h>


typedef uint32_t Um_instruction;

// Um_instruction three_register(uint8_t op, uint32_t ra, uint32_t rb, uint32_t rc);
// Um_instruction loadval(unsigned ra, unsigned val);

void execute_instruction(Memory memory, uint32_t instruction);

void halt(Memory memory);
void conditional_move(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void segmented_load(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void segmented_store(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void addition(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void multiplication(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void division(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void nand(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc);
void output(Memory memory, uint32_t rc);
void input(Memory memory, uint32_t rc);
void load_program(Memory memory, uint32_t rb, uint32_t rc);
void load_value(Memory memory, uint32_t ra, uint32_t value);


#endif