#include "instructions.h"
#include "memory.h"


void execute_instruction(Memory memory, uint32_t instruction)
{
        /* get the value of the instruction we have to perform */
        uint32_t opcode = Bitpack_getu(instruction, 4, 28);
        /* get the values stored on every register */
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        /* account for the different packing of words */
        uint32_t raLV = Bitpack_getu(instruction, 3, 25);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);
        uint32_t value = Bitpack_getu(instruction, 25, 0);
        
        /* simple case-switch function to run the specific function */
        switch(opcode) {
                case 0:
                        // fprintf(stderr, "conditional move \n");
                        conditional_move(memory, ra, rb, rc);
                        break; 
                case 1:
                        fprintf(stderr, "segmented load\n");
                        segmented_load(memory, ra, rb, rc);
                        break;
                case 2:
                        segmented_store(memory, ra, rb, rc);
                        break;
                case 3:
                        // fprintf(stderr, "addition\n");
                        addition(memory, ra, rb, rc);
                        break;
                case 4:
                        // fprintf(stderr, "multiplication\n");
                        multiplication(memory, ra, rb, rc);
                        break;
                case 5:
                        // fprintf(stderr, "division\n");
                        division(memory, ra, rb, rc);
                        break;
                case 6:
                        // fprintf(stderr, "nand\n");
                        nand(memory, ra, rb, rc);
                        break;
                case 7:
                        fprintf(stderr, "halt\n");
                        halt(memory);
                        break;
                case 8:
                        fprintf(stderr, "map segment\n");
                        map_segment(memory, rb, rc);
                        break;
                case 9:
                        fprintf(stderr, "unmap segment\n");
                        unmap_segment(memory, rc);
                        break;
                case 10:
                        // fprintf(stderr, "output\n");
                        output(memory, rc);
                        break;
                case 11:
                        // fprintf(stderr, "intput\n");
                        input(memory, rc);
                        break;
                case 12:
                        fprintf(stderr, "load program\n");
                        load_program(memory, rb, rc);
                        break;
                case 13:
                        // fprintf(stderr, "load value\n");
                        load_value(memory, raLV, value);
                        break;
                default:
                        /* unaccounted number given */
                        fprintf(stderr, "Please input a valid instruction\n");
                        halt(memory);
        }
}


void addition(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc) 
{
        
        assert(memory);
        /* get what is in register b and c */
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);

        /* arithmetic for addition - mod 2^32 */
        uint32_t result = (b + c) % UINT32_MAX;

        /* put the result of the addition in register a */
        set_register(memory, ra, result);
}


void multiplication(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        
        assert(memory);
        /* get the values in the respective registers */
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
        /* multiply them and mod 2^32 */
        uint32_t result = (b * c) % UINT32_MAX;
        /* save result in ra */
        set_register(memory, ra, result);
}


void division(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
        /* account for whenever they try to divide by 0 */
        if (c == 0) {
                fprintf(stderr, "Cannot divide by 0\n");
                exit(0);
        }
        uint32_t result = (b / c);

        set_register(memory, ra, result);
}


void nand(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        
        assert(memory);
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
        
        /* and the values at both registers */
        uint32_t result = b & c;
        /* get the complement of the result */
        uint32_t new_result = ~result;

        set_register(memory, ra, new_result);
}


void halt(Memory memory)
{
        assert(memory);
        /* free memory and terminate the program */
        free_memory(memory);
        exit(0);
}


void output(Memory memory, uint32_t rc)
{
        assert(memory);
        /* print to stdout the value stored at register rc */
        putchar(get_register(memory, rc));
}


void input(Memory memory, uint32_t rc)
{
        assert(memory);
        int in = getchar();

        /* if end of characters, store all 1s */
        if (in == EOF) {
                set_register(memory, rc, UINT32_MAX);
        } else if (in >= 0 && in < 256 && in != EOF) {
                /* store it in register rc */
                set_register(memory, rc, in);
        }
}


void segmented_load(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        // fprintf(stderr, "register ra %u\n", ra);
        // fprintf(stderr, "register rb %u\n", rb);
        // fprintf(stderr, "register rc %u\n", rc);
        uint32_t segmentID = get_register(memory, rb);
        uint32_t offset = get_register(memory, rc);
        // fprintf(stderr, "offset %u\n", offset);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        // fprintf(stderr, "length of segment read %d\n", Seq_length(segment));
        // fprintf(stderr, "ID accessed in the sequence %u\n", segmentID);
        uint32_t value = (uint32_t)(uintptr_t)Seq_get(segment, offset);
        // fprintf(stderr, "value we just stored: %d\n", value);
        set_register(memory, ra, value);
}


void segmented_store(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);     
        uint32_t value = get_register(memory, rc);
        uint32_t segmentID = get_register(memory, ra);
        uint32_t offset = get_register(memory, rb);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        Seq_put(segment, offset, (void *)(uintptr_t)value);  
}


void map_segment(Memory memory, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t num_words = get_register(memory, rc);
        uint32_t segmentID = segment_map(memory, num_words);

        set_register(memory, rb, segmentID);
}


void unmap_segment(Memory memory, uint32_t rc)
{
        assert(memory);
        segment_unmap(memory, get_register(memory, rc));
}

/* CODE A FUNCTION THAT USES THE BITPACK GET AND CALLS THE RESPECTIVE FUNCTION WITH ALL OF THE PARAMETERS NEEDED*/
void conditional_move(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        if (get_register(memory, rc) != 0) {
                set_register(memory, ra, get_register(memory, rb));
        }
}


void load_program(Memory memory, uint32_t rb, uint32_t rc)
{ 
        /* FIX THIS FUNCTION */
        /* could be an issue with program counter */
        assert(memory);
        uint32_t segmentID = get_register(memory, rb);
        set_pc(memory, (get_register(memory, rc) - 1));
        if (segmentID != 0) {
                Seq_T segment = Seq_get(get_segments(memory), segmentID);
                Seq_T duplicate_segment = Seq_new(Seq_length(segment));
                for (int i = 0; i < Seq_length(segment); i++) {
                        uint32_t element = (uint32_t)(uintptr_t)Seq_get(segment, i);
                        Seq_addhi(duplicate_segment, (void *)(uintptr_t)(element));
                }
                Seq_free(Seq_get(get_segments(memory), 0));
                set_segments(memory, 0, duplicate_segment);
        } 
}

void load_value(Memory memory, uint32_t ra, uint32_t value)
{
        assert(memory);
        set_register(memory, ra, value);
}