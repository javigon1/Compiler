/*
 * umlab.c
 *
 * Functions to generate UM unit tests. Once complete, this module
 * should be augmented and then linked against umlabwrite.c to produce
 * a unit test writing program.
 *  
 * A unit test is a stream of UM instructions, represented as a Hanson
 * Seq_T of 32-bit words adhering to the UM's instruction format.  
 * 
 * Any additional functions and unit tests written for the lab go
 * here. 
 *  
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include <bitpack.h>


typedef uint32_t Um_instruction;

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */


/* three_register function implementation */
Um_instruction three_register(Um_opcode op, int ra, int rb, int rc) 
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
Um_instruction loadval(unsigned ra, unsigned val) 
{ 
        /* generate a bitpacked Load Value UM instruction. Recall that this 
        is the only UM instruction that has a different encoding format */ 
        Um_instruction newVal = 0x0;
        newVal = Bitpack_newu(newVal, 13, 28, LV);
        newVal = Bitpack_newu(newVal, 3, 25, ra);
        newVal = Bitpack_newu(newVal, 13, 0, val);
        
        return newVal;
}


/* Wrapper functions for each of the instructions */
static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

static inline Um_instruction add(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}


/* output wrapper function */
static inline Um_instruction output(Um_register c) 
{
        return three_register(OUT, 0, 0, c);
}


/* Functions for working with streams */
static inline void append(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

const uint32_t Um_word_width = 32;

void Um_write_sequence(FILE *output, Seq_T stream)
{
        assert(output != NULL && stream != NULL);
        int stream_length = Seq_length(stream);
        for (int i = 0; i < stream_length; i++) {
                Um_instruction inst = (uintptr_t)Seq_remlo(stream);
                for (int lsb = Um_word_width - 8; lsb >= 0; lsb -= 8) {
                        fputc(Bitpack_getu(inst, 8, lsb), output);
                }
        }
}

void build_halt_test(Seq_T stream)
{
        append(stream, halt());
}

void build_conditional_test(Seq_T stream)
{
        append(stream, halt());
}

void build_output_test(Seq_T stream) 
{
        append(stream, output(r2));
        append(stream, halt());
}

void build_load_value_test(Seq_T stream) 
{
        append(stream, loadval(r2, 48));
        append(stream, output(r2));
        append(stream, halt());
}