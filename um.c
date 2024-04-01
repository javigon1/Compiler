#include "um.h"

#define REG_WIDTH 3

typedef uint32_t Um_register;

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

typedef struct Instruction {
        uint8_t opcode;
        Um_register rA, rB, rC;
} Instruction;

typedef struct Universal_machine {
        uint32_t registers[8];
        uint32_t program_counter;
} Universal_machine;


static Instruction extract(uint32_t word, Instruction instruction);


/* should we do this a void or a Um_instruction like in lab??? */
static inline void conditional_move(/*  containing info */);
static inline void segmented_load(/*  containing info */);
static inline void segemnted_store(/*  containing info */);
static inline void addition(Um_register ra, Um_register b, Um_register c);
static inline void multiplication(/*  containing info */);
static inline void division(/*  containing info */);
static inline void nand(/*  containing info */);
static inline void halt(/*  containing info */);
static inline void map_segment(/*  containing info */);
static inline void unmap_segment(/*  containing info */);
static inline void output(/*  containing info */);
static inline void input(/*  containing info */);
static inline void load_program(/*  containing info */);
static inline void load_value(/*  containing info */);


static Instruction extract(uint32_t word, Instruction instruction)
{
        instruction.opcode = Bitpack_getu(word, 4, 28);

        if (instruction.opcode != LV) {
                instruction.rA = Bitpack_getu(word, REG_WIDTH, (REG_WIDTH * 2));
                instruction.rB = Bitpack_getu(word, REG_WIDTH, REG_WIDTH);
                instruction.rC = Bitpack_getu(word, REG_WIDTH, 0);
        } else {
                instruction.rA = Bitpack_getu(word, REG_WIDTH, 25);
        }

        return instruction;
}