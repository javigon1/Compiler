#include "um.h"


// #define REG_WIDTH 3
// #define OPCODE_WIDTH 4
// #define INST_SIZE 32


typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;


// Instruction extract(uint32_t word, Instruction instruction)
// {
//         instruction.opcode = Bitpack_getu(word, OPCODE_WIDTH, INST_SIZE - OPCODE_WIDTH);

//         if (instruction.opcode != 13) {
//                 instruction.rA = Bitpack_getu(word, REG_WIDTH, (REG_WIDTH * 2));
//                 instruction.rB = Bitpack_getu(word, REG_WIDTH, REG_WIDTH);
//                 instruction.rC = Bitpack_getu(word, REG_WIDTH, 0);
//         } else {
//                 instruction.rA = Bitpack_getu(word, REG_WIDTH, INST_SIZE - OPCODE_WIDTH - REG_WIDTH);
//         }

//         return instruction;
// }