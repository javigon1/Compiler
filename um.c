#include "um.h"

typedef uint32_t Um_instruction;

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

/* should we do this a void or a Um_instruction like in lab??? */
static inline void conditional_move(/*  containing info */);
static inline void segmented_load(/*  containing info */);
static inline void segemnted_store(/*  containing info */);
static inline void addition(/*  containing info */);
static inline void multiplication(/*  containing info */);
static inline void division(/*  containing info */);
static inline void nand(/*  containing info */);
static inline void halt(/*  containing info */);
static inline void map_segment(/*  containing info */);
static inline void unmap_segment(/*  containing info */);
static inline void output(/*  containing info */);
static inline void input(/*  containing info */);
static inline void load_program(/*  containing info */);
static inline void load_value(/*  containing info */);