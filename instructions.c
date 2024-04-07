#include "instructions.h"

// struct Instruction {
//         Um_opcode opcode;
//         Um_instruction word;
// };

Um_instruction three_register(uint8_t op, uint32_t ra, uint32_t rb, uint32_t rc) 
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
Um_instruction loadval(uint32_t ra, uint32_t val) 
{ 
        /* generate a bitpacked Load Value UM instruction. Recall that this 
        is the only UM instruction that has a different encoding format */ 
        Um_instruction newVal = 0x0;
        newVal = Bitpack_newu(newVal, 13, 28, 13);
        newVal = Bitpack_newu(newVal, 3, 25, ra);
        newVal = Bitpack_newu(newVal, 13, 0, val);
        
        return newVal;
}


void halt(Memory memory)
{
        segment_free(memory);
        exit(0);
}

/* CODE A FUNCTION THAT USES THE BITPACK GET AND CALLS THE RESPECTIVE FUNCTION WITH ALL OF THE PARAMETERS NEEDED*/
void conditional_move(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        if (memory->registers[rc] != 0) {
                memory->registers[ra] = memory->registers[rb];
        }
}

// void conditional_move(uint32_t registers[8], Instruction instruction)
// {
//         unsigned ra = Bitpack_getu(instruction.word, 3, 6);
//         unsigned rb = Bitpack_getu(instruction.word, 3, 3);
//         unsigned rc = Bitpack_getu(instruction.word, 3, 0);

//         if (registers[rc] != 0) {
//                 registers[ra] = registers[rb];
//         }   
// }


// void halt()
// {
//        exit(0);
// }

// void output(uint32_t registers[8], Instruction instruction)
// {
//         unsigned rc = Bitpack_getu(instruction.word, 3, 0);
//         uint32_t value = registers[rc];

//         if (value <= 255) {
//                 putchar((char)value);
//         } else {
//                 fprintf(stderr, "Error: Value in register %u is out of"
//                                 "range for output.\n", rc);
//         }
// }

// void load_value(uint32_t registers[8], Instruction instruction)
// {
//         unsigned ra = Bitpack_getu(instruction.word, 3, 28);
//         uint32_t value = Bitpack_getu(instruction.word, 25, 0);
//         registers[ra] = value;
// }