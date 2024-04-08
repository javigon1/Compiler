#include "loadProgram.h"


Seq_T loadProgram(FILE *fp, uint64_t program_size)
{
        Seq_T program = Seq_new(0);

        uint32_t word = 0;
        uint64_t words_read = 0;
        while (words_read < program_size) {
                for (int i = 0; i < 4; i++) {
                        uint64_t byte = getc(fp);
                        if ((int)byte == EOF) {
                                return program;
                        }
                        word = Bitpack_newu(word, 8, (3 - i) * 8, byte);
                }
                Seq_addhi(program, (void *)(uintptr_t)word);
                words_read++;
        }
        return program;
}