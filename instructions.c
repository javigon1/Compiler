/*
 *     instructions.c
 *     Javier Gonzalez (jgonza20) and Jordan Pittignano (jpitti01)
 *     4/11/24
 *     um
 *
 *     Contains the operator definitions for the 14 UM instructions and
 *     allows us to determine which isntruction should be executed based
 *     on opcode.
 */

#include "instructions.h"
#include "memory.h"


/* 
 * Name: execute_instruction
 * 
 * Description: given a 32-bit int that represents a instruction,
 * determines which instruction it is our of the 14 the UM can perform and 
 * then executes it. Follows the steps of fetching, decoding and executing.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t instruction: 32-bit packed instruction.
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * // deleted: 4581f68cda914e36571c49dc0fffbaa49d63c14d
 * // added:  f2cc1b3bccfa38a08cba19d67c4de8c81f7a9123
 * 
 * Notes: throws c.r.e. if memory struct is NULL. Uses a case switch 
 * function to run the correct instruction.
 */
void execute_instruction(Memory memory, uint32_t instruction)
{e148a8e44ec2aa0063e12ad38f2586b6f390611e
        assert(memory);
        
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
                        load_value(memory, raLV, value);
                        break;
                default:
                        printf("Please input a valid instruction\n");
                        halt(memory);
        }
}


/*
 * Name: addition
 * 
 * Description: adds what is in register b and c and puts the sum in register a
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t rb: index of register b.
 *           uint32_t rc: index of register c.
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL. Changing what 
 * register a is holding.
 */
void addition(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc) 
{
        assert(memory);
        /* get what is in register b and c */
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);

        /* arithmetic for addition - mod 2^32 */
        uint32_t result = (b + c);

        /* put the result of the addition in register a */
        set_register(memory, ra, result);
}


/*
 * Name: multiplication
 * 
 * Description: multiplies what is in register c and b and puts that new
 * value in register a.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t rb: index of register b.
 *           uint32_t rc: index of register c.
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL. Changing what 
 * register a is holding.
 */
void multiplication(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);

        /* get the values in the respective registers */
        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);

        /* multiply them and mod 2^32 */
        uint32_t result = (b * c);

        /* save result in ra */
        set_register(memory, ra, result);
}


/*
 * Name: division
 * 
 * Description: divides what is in register b by what is in register c and 
 * puts it in register a.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t rb: index of register b.
 *           uint32_t rc: index of register c. 
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws c.r.e if memory struct is NULL. Changing what is in 
 * register a.
 */
void division(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);

        uint32_t b = get_register(memory, rb);
        uint32_t c = get_register(memory, rc);

        /* account for whenever they try to divide by 0 */
        uint32_t result = (b / c);

        set_register(memory, ra, result);
}


/*
 * Name: nand
 * 
 * Description: performs bitwise nand operation by adding what is in register
 * b and register c, negating the result and then putting it in register a.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t rb: index of register b.
 *           uint32_t rc: index of register c. 
 *       
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws c.r.e. if memory struct is NULL. Changing what is 
 * register a.
 */
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


/*
 * Name: halt
 * 
 * Description: causes computation to stop in the program.
 *
 * Parameters:
 *           Memory memory: instance of memory struct
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void halt(Memory memory)
{
        assert(memory);

        /* free memory and terminate the program */
        free_memory(memory);
        exit(0);
}


/*
 * Name: output
 * 
 * Description: outputs what is in register c to I/O.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t rc: index of register c.
 *        
 * Returns: nothing.
 * 
 * Expects:  memory struct is not NULL and what is in register c is between
 * 0 and 255.
 * 
 * Notes: throws c.r.e. if memory struct is NULL or what is in register
 * c is not between 0 and 255.
 */
void output(Memory memory, uint32_t rc)
{
        assert(memory);
        int value = (int)get_register(memory, rc);
        assert(value >= 0 && value < 256);
        putchar(get_register(memory, rc));
}


/*
 * Name: input
 * 
 * Description: loads input into register c.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t rc: index of register c.
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL. 
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void input(Memory memory, uint32_t rc)
{
        assert(memory);

        int in = getchar();

        /* if end of characters, store all 1s */
        if (in == EOF) {
                set_register(memory, rc, UINT32_MAX);
        } else if (in >= 0 && in < 256) {
                /* store it in register rc */
                set_register(memory, rc, in);
        }
}


/* 
 * Name: segmented_load
 * 
 * Description: loads a value from a segment and stores it in a register.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t rb: index of register b (segment ID).
 *           uint32_t rc: index of register c (offset within the segment).
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */

void segmented_load(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);

        /* getting segment id for register b */
        uint32_t segmentID = get_register(memory, rb);

        /* distance from first element in sequence */
        uint32_t offset = get_register(memory, rc);

        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        uint32_t value = (uint32_t)(uintptr_t)Seq_get(segment, offset);
        set_register(memory, ra, value);
}


/* 
 * Name: segmented_store
 * 
 * Description: stores a value from a register into a segment.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a (segment ID).
 *           uint32_t rb: index of register b (offset within the segment).
 *           uint32_t rc: index of register c (value to store).
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void segmented_store(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);     
        uint32_t value = get_register(memory, rc);
        uint32_t segmentID = get_register(memory, ra);
        uint32_t offset = get_register(memory, rb);
        Seq_T segment = Seq_get(get_segments(memory), segmentID);
        Seq_put(segment, offset, (void *)(uintptr_t)value);  
}


/* 
 * Name: map_segment
 * 
 * Description: creates a new segment with a specified number of words.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t rb: index of register b (segment ID).
 *           uint32_t rc: index of register c (number of words in the new 
 *                        segment)
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void map_segment(Memory memory, uint32_t rb, uint32_t rc)
{
        assert(memory);
        uint32_t num_words = get_register(memory, rc);
        uint32_t segmentID = segment_map(memory, num_words);

        set_register(memory, rb, segmentID);
}


/* 
 * Name: unmap_segment
 * 
 * Description: deallocates a segment.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t rc: index of register c (segment ID).
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void unmap_segment(Memory memory, uint32_t rc)
{
        assert(memory);
        segment_unmap(memory, get_register(memory, rc));
}


/* 
 * Name: conditional_move
 * 
 * Description: moves the value in register rb to register ra if the value in
 * register rc is not zero.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t rb: index of register b.
 *           uint32_t rc: index of register c.
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void conditional_move(Memory memory, uint32_t ra, uint32_t rb, uint32_t rc)
{
        assert(memory);
        if (get_register(memory, rc) != 0) {
                set_register(memory, ra, get_register(memory, rb));
        }
}


/* 
 * Name: load_program
 * 
 * Description: Loads a program from a segment into memory and sets the program
 * counter to the specified offset.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t rb: index of register b (segment ID).
 *           uint32_t rc: index of register c (offset within the segment).
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void load_program(Memory memory, uint32_t rb, uint32_t rc)
{ 
        assert(memory);
        uint32_t segmentID = get_register(memory, rb);
        set_pc(memory, (get_register(memory, rc)));
        if (segmentID != 0) {
                Seq_T segment = Seq_get(get_segments(memory), segmentID);
                Seq_T duplicate_segment = Seq_new(Seq_length(segment));
                for (int i = 0; i < Seq_length(segment); i++) {
                        uint32_t element = (uint32_t)(uintptr_t)
                                           Seq_get(segment, i);
                        Seq_addhi(duplicate_segment, (void *)
                                                     (uintptr_t)(element));
                }
                set_segments(memory, 0, duplicate_segment);
        } 
}


/* 
 * Name: load_value
 * 
 * Description: Loads a specified value into a register.
 *
 * Parameters:
 *           Memory memory: instance of memory struct.
 *           uint32_t ra: index of register a.
 *           uint32_t value: balue to load into the register.
 *        
 * Returns: nothing.
 * 
 * Expects: memory struct is not NULL.
 * 
 * Notes: throws a c.r.e. if memory struct is NULL.
 */
void load_value(Memory memory, uint32_t ra, uint32_t value)
{
        assert(memory);
        set_register(memory, ra, value);
}