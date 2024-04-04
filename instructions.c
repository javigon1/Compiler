#include "instructions.h"


typedef uint32_t Um_register;

typedef struct Instruction {
        uint8_t opcode;
        uint32_t word;
} Instruction;

typedef struct Registers {
        Um_register registers[REG_NUM];
} Registers;

void conditional_move(Instruction instruction, Registers registers)
{
   
}

void segmented_load(Instruction instruction, Registers registers)
{
    
}

void segemnted_store(Instruction instruction, Registers registers)
{
   
}

void addition(Instruction instruction, Registers registers)
{

}

void multiplication(Instruction instruction, Registers registers)
{
   
}

void division(Instruction instruction, Registers registers)
{
   
}

void nand(Instruction instruction, Registers registers)
{
    
}

void halt(Instruction instruction, Registers registers)
{
    
}

void map_segment(Instruction instruction, Registers registers)
{
   
}

void unmap_segment(Instruction instruction, Registers registers)
{
   
}

void output(Instruction instruction, Registers registers)
{
   
}

void input(Instruction instruction, Registers registers)
{
   
}

void load_program(Instruction instruction, Registers registers)
{
   
}

void load_value(Instruction instruction, Registers registers)
{

}