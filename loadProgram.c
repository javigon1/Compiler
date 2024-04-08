#include "loadProgram.h"

// CHANGE THIS TO MEMORY
void loadProgram(FILE *fp, Memory memory, uint32_t program_size)
{
        Seq_T program = Seq_new(program_size);
        uint32_t word;

        for (int i = 0; i < program_size; i++) {
                // read in the instruction
                // store it in the 0 index of the sequence segments
        }
}