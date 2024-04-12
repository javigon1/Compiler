#include "um.h"


int main(int argc, char *argv[])
{
        (void)argc;
        /* get the size of the file as segments have to be initialized on a
        known size */
        struct stat st;
        if (stat(argv[1], &st) != 0) {
                fprintf(stderr, "Error getting file size");
                return EXIT_FAILURE;
        } 
        /* contain the size of the file in bytes and divide by 4 to get the 
        total number of 32bit instructions */
        unsigned numInstructions = st.st_size / 4;

        Memory memory = new_memory();
        assert(memory);

        FILE *fp = fopen(argv[1], "r");
        assert(fp);
        /* populate the 0 sequence with the instructions in the file given */
        Seq_T program = loadProgram(fp, numInstructions);

        // fprintf(stderr, "what is program len: %u\n", Seq_length(Seq_get(program,0)));

        // for (int i = 0; i < Seq_length(program); i++) {
        //         uint32_t instruction = (uint32_t)(uintptr_t)(Seq_get(program, i));
        //         // fprintf(stderr, "%u\n", instruction);
        // }
        assert(program);
        fclose(fp);
        /* set the segment at index 0 to the sequence of instructions */
        set_segments(memory, 0, program);

        /* iterate until program_length / numInstructions -> should be the same */
        // int instruction_counter = 0;
        // int seq_load_counter = 0;
        // for (set_pc(memory, 0); 
        // (int)get_pc(memory) < Seq_length(Seq_get(get_segments(memory), 0));
        //      set_pc(memory, get_pc(memory) + 1)) {
        //         uint32_t instruction = (uint32_t)(uintptr_t)Seq_get(Seq_get(get_segments(memory), 0), get_pc(memory));
        //         uint32_t check = Bitpack_getu(instruction, 4, 28);
        //         // if (check == 1) {
        //         //         seq_load_counter++;
        //         // }
        //         execute_instruction(memory, instruction); 
        //         // instruction_counter++;
        //         fprintf(stderr, "pc %u\n", get_pc(memory));
        //         // fprintf(stderr, "Segmented load %u being executed\n", seq_load_counter);
        // }      

        while ((int)get_pc(memory) < Seq_length(Seq_get(get_segments(memory), 0))) {
                uint32_t instruction = (uint32_t)(uintptr_t)Seq_get(Seq_get(get_segments(memory), 0), get_pc(memory));
                // fprintf(stderr, "value of instruction: %u\n", instruction);
                // fprintf(stderr, "pc %u\n", get_pc(memory));
                execute_instruction(memory, instruction); 
                uint32_t instr = Bitpack_getu(instruction, 4, 28);
                if (instr != 12) {
                        set_pc(memory, get_pc(memory) + 1);
                }
        }
        /* last instruction had to be a halt so in case the user forgets */
        halt(memory);

        return EXIT_SUCCESS; 
}