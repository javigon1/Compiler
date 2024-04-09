#include "loadProgram.h"


Seq_T loadProgram(FILE *fp, uint64_t program_size)
{
        /* initialize the 0 segment's sequence */
        Seq_T program = Seq_new(program_size);

        uint32_t word = 0;
        uint64_t instructions_read = 0;
        /* store all of the instructions read in program */
        while (instructions_read < program_size) {
                /* account for the right endianess */
                for (int i = 0; i < 4; i++) {
                        uint64_t byte = getc(fp);
                        /* check in case all instructions have been read */
                        /* DO WE NEED THIS? */
                        if ((int)byte == EOF)  return program;

                        word = Bitpack_newu(word, 8, (3 - i) * 8, byte);
                }
                /* add instruction to sequence */
                Seq_addhi(program, (void *)(uintptr_t)word);
                /* update the number of instructions read*/
                instructions_read++;
        }
        return program;
}