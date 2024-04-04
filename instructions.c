#include "instructions.h"

struct Instruction {
        Um_opcode opcode;
        Um_instruction word;
};

struct Register {
        uint32_t registers[8];
};


Um_instruction three_register(Um_opcode op, int ra, int rb, int rc) 
{
        /* generate a bitpacked UM instruction using provided opcode and
        three register identifies */
        Um_instruction bitpacked = 0x0;
        bitpacked = Bitpack_newu(bitpacked, 4, 28, op);
        bitpacked = Bitpack_newu(bitpacked, 3, 0, rc);
        bitpacked = Bitpack_newu(bitpacked, 3, 3, rb);
        bitpacked = Bitpack_newu(bitpacked, 3, 6, ra);

        return bitpacked;
}


/* load val function */ 
Um_instruction loadval(unsigned ra, unsigned val) 
{ 
        /* generate a bitpacked Load Value UM instruction. Recall that this 
        is the only UM instruction that has a different encoding format */ 
        Um_instruction newVal = 0x0;
        newVal = Bitpack_newu(newVal, 13, 28, 13);
        newVal = Bitpack_newu(newVal, 3, 25, ra);
        newVal = Bitpack_newu(newVal, 13, 0, val);
        
        return newVal;
}

void conditional_move(Register registers, Instruction instruction)
{
        unsigned ra = Bitpack_getu(instruction.word, 3, 6);
        unsigned rb = Bitpack_getu(instruction.word, 3, 3);
        unsigned rc = Bitpack_getu(instruction.word, 3, 0);

        if (registers->registers[rc] != 0) {
                registers->registers[ra] = registers->registers[rb];
        }
}