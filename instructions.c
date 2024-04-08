#include "instructions.h"
#include "memory.h"


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


void addition(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc) {
        /* add what is in register b and c and put it into a */

        /* QUESTION: what assert statements do I need here?? */
        // assert(ra < 256);
        // assert(rb < 256);
        // assert(rc < 256);

        /* get what is in register b and c */
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);

        /* arithmetic for addition */
        uint32_t resultOfAddition = (b + c) % UINT32_MAX;

        /* put the result of the addition in register a */
        set_register(memory, ra, resultOfAddition);
}


void multiplication(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
        uint32_t result = (b * c) % UINT32_MAX;

        set_register(memory, ra, result);
}


void division(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
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
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);
        
        uint32_t result = b & c;
        uint32_t new_result = ~result;

        set_register(memory, ra, new_result);
}


void halt(Memory memory)
{
        free_memory(memory);
        exit(0);
}


void output(Memory memory, uint32_t rc)
{
        /* check this assert statement */
        assert(rc < 256);
        putchar(get_register(memory, rc));
}


void input(Memory memory, uint32_t rc)
{
        int in = getchar();
        if (in >= 0 && in < 256 && in != EOF) {
                set_register(memory, rc, in);
        } else {
                set_register(memory, rc, UINT32_MAX);
        }
}


void segmented_load(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        uint32_t segmentID = get_register(memory, rb);
        uint32_t offset = get_register(memory, rc);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        uint32_t value = *((uint32_t*)Seq_get(segment, offset));
        set_register(memory, ra, value);
}


void segmented_store(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        uint32_t value = get_register(memory, rc);
        uint32_t segmentID = get_register(memory, ra);
        uint32_t offset = get_register(memory, rb);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        *((uint32_t *)Seq_get(segment, offset)) = value;    
}

/* CODE A FUNCTION THAT USES THE BITPACK GET AND CALLS THE RESPECTIVE FUNCTION WITH ALL OF THE PARAMETERS NEEDED*/
void conditional_move(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        if (get_register(memory, rc) != 0) {
                set_register(memory, ra, get_register(memory, rb));
        }
}