/*
 *     memory.c
 *     Javier Gonzalez (jgonza20) and Jordan Pittignano (jpitti01)
 *     4/11/24
 *     um
 *
 *     TODO: summary
 */

#include "memory.h"

/* constant for number of registers */
#define NUM_REGISTERS 8

struct Memory {
        /* sequence of sequence of unint32_ts */
        Seq_T segments;
        /* sequence of uint32_t values that correspond to unmapped IDs */
        Seq_T unmappedIDs;
        /* counts what instruction we are on */
        uint32_t program_counter;
        /* array of registers of particular size */
        uint32_t registers[NUM_REGISTERS];
};


Memory new_memory()
{
        Memory memory;
        NEW(memory);
        assert(memory);
        /* the initial memory has to have only segment 0 mapped */
        memory->segments = Seq_new(1);
        /* initialize the rest of variables to 0 */
        memory->unmappedIDs = Seq_new(0);
        memory->program_counter = 0;
        for (int i = 0; i < NUM_REGISTERS; i++) {
                memory->registers[i] = 0;
        }
        return memory;
}

void free_memory(Memory memory)
{
        assert(memory);
        /* free the sequences in the memory struct and then the struct itself */
        Seq_free(&memory->segments);
        Seq_free(&memory->unmappedIDs);
        FREE(memory);
}                                                                              


uint32_t segment_map(Memory memory, uint32_t size)
{
        assert(memory);
        assert(memory->segments);
        /* check if there unmapped ID so we don't have to create another */
        if (Seq_length(memory->unmappedIDs) > 0) {
                uint32_t segmentID = (uint32_t)(uintptr_t)Seq_remlo(memory->unmappedIDs);
                Seq_T segment = Seq_new(size);
                for (uint32_t i = 0; i < size; i++) {
                Seq_addhi(segment, (void *)(uintptr_t)0);
                }
                /* put the initialized segment in the ID it corresponds to in the "mapped" sequence */
                Seq_put(memory->segments, segmentID, segment);
                return segmentID;
        } 

        Seq_T segment = Seq_new(size);
        for (uint32_t i = 0; i < size; i++) {
                Seq_addhi(segment, (void *)(uintptr_t)0);
        }
        Seq_addhi(memory->segments, segment);
        
        /* return the index of the new segment */
        return Seq_length(memory->segments) - 1;
}


void segment_unmap(Memory memory, uint32_t segmentID)
{
        assert(memory);
        assert(memory->segments);
        assert(memory->unmappedIDs);

        if (segmentID != 0) {
                /* set the unmapped segment to NULL and place its ID into unmappedIDs */
                // Seq_T segment = Seq_put(memory->segments, segmentID, NULL);
                // Seq_free(&segment);
                Seq_put(memory->segments, segmentID, NULL);
                Seq_addhi(memory->unmappedIDs, (void *)(uintptr_t)segmentID);
        }                 
}


uint32_t get_register(Memory memory, uint32_t register_index)
{
        assert(memory);
        assert(register_index < 8);
        return memory->registers[register_index];
}


void set_register(Memory memory, uint register_index, uint32_t value)
{
        assert(memory);
        assert(register_index < 8);
        memory->registers[register_index] = value;
}


Seq_T get_segments(Memory memory) 
{
        assert(memory);
        assert(memory->segments);
        return memory->segments;
}


void set_segments(Memory memory, int index, Seq_T segments) 
{
        assert(memory);
        assert(memory->segments);
        assert(segments);
        if (index == Seq_length(memory->segments)) {
                Seq_addhi(memory->segments, segments);
        } else {
                Seq_put(memory->segments, index, segments);
        }
}


uint32_t get_pc(Memory memory)
{
        return memory->program_counter;
}


void set_pc(Memory memory, uint32_t value)
{
        assert(memory);
        memory->program_counter = value;
}