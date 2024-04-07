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

        FILE *fp = fopen(argv[1], "r"); 
        /* INITIALIZE THE SEGMENT, the sequence[0] has to have size found */
        // set the program counter to 0
        // this is where I have to loop and get instructions one by one
        // for (int i = 0; i < numInstructions; i++) {
                // find opcode
                // call the respective instruction
        // }

        //halt()

        //free the segment
        // free the array of registers

        (void)argc;
        (void)fp;
        (void)numInstructions;
        return EXIT_SUCCESS; 
}