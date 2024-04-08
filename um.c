#include "um.h"

int main(int argc, char *argv[])
{
        // think about maybe putting the array of registers inside the 
        // memory struct

        struct stat st;
        if (stat(argv[1], &st) == 0) {
                printf("File size: %ld bytes\n", st.st_size);
        } else {
                fprintf(stderr, "Error getting file size");
                return EXIT_FAILURE;
        }

        unsigned numInstructions = st.st_size / 32;

        Memory memory = new_memory();
        FILE *fp = fopen(argv[1], "r"); 
        Seq_T program = loadProgram(fp, numInstructions);
        set_segments(memory, 0, program);

        uint32_t program_length = Seq_length(program);

        for (uint32_t i = 0; i < program_length; i++) {
                uint32_t instruction = (uint32_t)(uintptr_t)Seq_get(program, i);
                execute_instruction(memory, instruction);
        }       
        
        
        //halt()

        //free the segment
        // free the array of registers

        (void)argc;
        return EXIT_SUCCESS; 
}