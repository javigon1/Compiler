#include "instructions.h"
#include "memory.h"


// Um_instruction three_register(uint8_t op, uint32_t ra, uint32_t rb, uint32_t rc) 
// {
//         /* generate a bitpacked UM instruction using provided opcode and
//         three register identifies */
//         Um_instruction bitpacked = 0x0;
//         bitpacked = Bitpack_newu(bitpacked, 4, 28, op);
//         bitpacked = Bitpack_newu(bitpacked, 3, 0, rc);
//         bitpacked = Bitpack_newu(bitpacked, 3, 3, rb);
//         bitpacked = Bitpack_newu(bitpacked, 3, 6, ra);

//         return bitpacked;
// }


// /* load val function */ 
// Um_instruction loadval(uint32_t ra, uint32_t val) 
// { 
//         /* generate a bitpacked Load Value UM instruction. Recall that this 
//         is the only UM instruction that has a different encoding format */ 
//         Um_instruction newVal = 0x0;
//         newVal = Bitpack_newu(newVal, 13, 28, 13);
//         newVal = Bitpack_newu(newVal, 3, 25, ra);
//         newVal = Bitpack_newu(newVal, 13, 0, val);
        
//         return newVal;
// }


void execute_instruction(Memory memory, uint32_t instruction)
{
        uint32_t opcode = Bitpack_getu(instruction, 4, 28);
        uint32_t ra = Bitpack_getu(instruction, 3, 6);
        uint32_t rb = Bitpack_getu(instruction, 3, 3);
        uint32_t rc = Bitpack_getu(instruction, 3, 0);
        uint32_t value = Bitpack_getu(instruction, 25, 0);
        
        switch(opcode) {
                case 0:
                        conditional_move(memory, ra, rb, rc);
                        break; 
                case 1:
                        segmented_load(memory, ra, rb, rc);
                        break;
                case 2:
                        segmented_store(memory, ra, rb, rc);
                        break;
                case 3:
                        addition(memory, ra, rb, rc);
                        break;
                case 4:
                        multiplication(memory, ra, rb, rc);
                        break;
                case 5:
                        division(memory, ra, rb, rc);
                        break;
                case 6:
                        nand(memory, ra, rb, rc);
                        break;
                case 7:
                        halt(memory);
                        break;
                case 8:
                        map_segment(memory, rb, rc);
                        break;
                case 9:
                        unmap_segment(memory, rc);
                        break;
                case 10:
                        output(memory, rc);
                        break;
                case 11:
                        input(memory, rc);
                        break;
                case 12:
                        load_program(memory, rb, rc);
                        break;
                case 13:
                        load_value(memory, ra, value);
                        break;
                default:
                        fprintf(stderr, "Please input a valid instruction\n");
                        halt(memory);
        }
}


void addition(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc) {

        assert(memory);
        /* get what is in register b and c */
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);

        /* arithmetic for addition */
        uint32_t result = (b + c) % UINT32_MAX;

        /* put the result of the addition in register a */
        set_register(memory, ra, result);
}


void multiplication(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
        uint32_t result = (b * c) % UINT32_MAX;

        set_register(memory, ra, result);
}


void division(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
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
        
        uint32_t result = b & c;
        uint32_t new_result = ~result;

        set_register(memory, ra, new_result);
}


void halt(Memory memory)
{
        assert(memory);
        free_memory(memory);
        exit(0);
}


void output(Memory memory, uint32_t rc)
{
        assert(memory);
        putchar(get_register(memory, rc));
}


void input(Memory memory, uint32_t rc)
{
        assert(memory);
        int in = getchar();
        if (in >= 0 && in < 256 && in != EOF) {
                set_register(memory, rc, in);
        } else {
                set_register(memory, rc, UINT32_MAX);
        }
}


void segmented_load(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t segmentID = get_register(memory, rb);
        uint32_t offset = get_register(memory, rc);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        uint32_t value = *((uint32_t*)Seq_get(segment, offset));
        set_register(memory, ra, value);
}


void segmented_store(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t value = get_register(memory, rc);
        uint32_t segmentID = get_register(memory, ra);
        uint32_t offset = get_register(memory, rb);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        *((uint32_t *)Seq_get(segment, offset)) = value;    
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
        assert(memory);
        uint32_t segmentID = get_register(memory, rb);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);

        Seq_T duplicate_segment = Seq_new(Seq_length(segment));
        for (int i = 0; i < Seq_length(segment); i++) {
                uint32_t *element = (uint32_t *)Seq_get(segment, i);
                Seq_addhi(duplicate_segment, (void *)(uintptr_t)(*element));
        }

        segment_unmap(memory, 0);
        set_segments(memory, 0, duplicate_segment);

        set_program_counter(memory, get_register(memory, rc));
}

void load_value(Memory memory, uint32_t ra, uint32_t value)
{
        assert(memory);
        set_register(memory, ra, value);
}