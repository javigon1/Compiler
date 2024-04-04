#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDEDs

#define REG_NUM 8

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <seq.h>


typedef struct Registers *Registers;


void conditional_move(Instruction instruction, Registers registers);
void segmented_load(Instruction instruction, Registers registers);
void segemnted_store(Instruction instruction, Registers registers);
void addition(Instruction instruction, Registers registers);
void multiplication(Instruction instruction, Registers registers);
void division(Instruction instruction, Registers registers);
void nand(Instruction instruction, Registers registers);
void halt(Instruction instruction, Registers registers);
void map_segment(Instruction instruction, Registers registers);
void unmap_segment(Instruction instruction, Registers registers);
void output(Instruction instruction, Registers registers);
void input(Instruction instruction, Registers registers);
void load_program(Instruction instruction, Registers registers);
void load_value(Instruction instruction, Registers registers);


#endif