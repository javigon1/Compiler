#include "um.h"

#define REG_WIDTH 3
#define OPCODE_WIDTH 4
#define REG_NUM 8
#define INST_SIZE 32

typedef uint32_t Um_register;

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

typedef struct Instruction {
        uint8_t opcode;
        Um_register rA, rB, rC;
} Instruction;

typedef struct Registers {
        uint32_t registers[REG_NUM];
} Registers;


static Instruction extract(uint32_t word, Instruction instruction);


/* should we do this a void or a Um_instruction like in lab??? */
static inline void conditional_move(Instruction instruction, Registers registers);
static inline void segmented_load(Instruction instruction, Registers registers);
static inline void segemnted_store(Instruction instruction, Registers registers);
static inline void addition(Instruction instruction, Registers registers);
static inline void multiplication(Instruction instruction, Registers registers);
static inline void division(Instruction instruction, Registers registers);
static inline void nand(Instruction instruction, Registers registers);
static inline void halt(Instruction instruction, Registers registers);
static inline void map_segment(Instruction instruction, Registers registers);
static inline void unmap_segment(Instruction instruction, Registers registers);
static inline void output(Instruction instruction, Registers registers);
static inline void input(Instruction instruction, Registers registers);
static inline void load_program(Instruction instruction, Registers registers);
static inline void load_value(Instruction instruction, Registers registers);


static Instruction extract(uint32_t word, Instruction instruction)
{
        instruction.opcode = Bitpack_getu(word, OPCODE_WIDTH, INST_SIZE - OPCODE_WIDTH);

        if (instruction.opcode != LV) {
                instruction.rA = Bitpack_getu(word, REG_WIDTH, (REG_WIDTH * 2));
                instruction.rB = Bitpack_getu(word, REG_WIDTH, REG_WIDTH);
                instruction.rC = Bitpack_getu(word, REG_WIDTH, 0);
        } else {
                instruction.rA = Bitpack_getu(word, REG_WIDTH, INST_SIZE - OPCODE_WIDTH - REG_WIDTH);
        }

        return instruction;
}


static inline void conditional_move(Instruction instruction, Registers registers)
{
   
}

static inline void segmented_load(Instruction instruction, Registers registers)
{
    
}

static inline void segemnted_store(Instruction instruction, Registers registers)
{
   
}

static inline void addition(Instruction instruction, Registers registers)
{

}

static inline void multiplication(Instruction instruction, Registers registers)
{
   
}

static inline void division(Instruction instruction, Registers registers)
{
   
}

static inline void nand(Instruction instruction, Registers registers)
{
    
}

static inline void halt(Instruction instruction, Registers registers)
{
    
}

static inline void map_segment(Instruction instruction, Registers registers)
{
   
}

static inline void unmap_segment(Instruction instruction, Registers registers)
{
   
}

static inline void output(Instruction instruction, Registers registers)
{
   
}

static inline void input(Instruction instruction, Registers registers)
{
   
}

static inline void load_program(Instruction instruction, Registers registers)
{
   
}

static inline void load_value(Instruction instruction, Registers registers)
{

}