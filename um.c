#include "um.h"

int main(int argc, char *argv[])
{
        (void)argc;
        /* get the size of the file as segments have to be initialized on a
        known size */
        (void)argc;
        /* get the size of the file as segments have to be initialized on a
        known size */
        struct stat st;
        if (stat(argv[1], &st) != 0) {
        if (stat(argv[1], &st) != 0) {
                fprintf(stderr, "Error getting file size");
                return EXIT_FAILURE;
        } 
        } 

        /* contain the size of the file in bytes and divide by 4 to get the 
        total number of 32bit instructions */
        unsigned numInstructions = st.st_size / 4;

        Memory memory = new_memory();
        FILE *fp = fopen(argv[1], "r");
        /* populate the 0 sequence with the instructions in the file given */
        Seq_T program = loadProgram(fp, numInstructions);
        /* set the segment at index 0 to the sequence of instructions */
        set_segments(memory, 0, program);

        // uint32_t program_length = Seq_length(program);

        /* iterate until program_length / numInstructions -> should be the same */
        for (set_pc(memory, 0); 
        (int)get_pc(memory) < Seq_length(Seq_get(get_segments(memory), 0)); 
             set_pc(memory, (get_pc(memory) + 1))) {
                /* get the instruction at the given index of the sequence */
                uint32_t instruction = (uint32_t)(uintptr_t)Seq_get(Seq_get(get_segments(memory), 0), get_pc(memory));
                /* NEED TO FIND A WAY TO SET i TO THE NEW PROGRAM COUNTER */
                execute_instruction(memory, instruction);
        }       

        /* last instruction had to be a halt so in case the user forgets */
        halt(memory);

        // free the segment
        // free the array of registers

        return EXIT_SUCCESS; 
}