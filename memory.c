#include "memory.h"

#define NUM_REGISTERS 8

struct Memory {
        Seq_T segments;
        Seq_T unmappedIDs;
        uint32_t program_counter;
        uint32_t registers[NUM_REGISTERS];
};


Memory new_memory()
{
        Memory memory;
        NEW(memory);
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
        fprintf(stderr, "SIZE %d\n", size);
        /* check if there is an unmapped ID so we don't have to create another */
        if (Seq_length(memory->unmappedIDs) > 0) {
                uint32_t segmentID = (uint32_t)(uintptr_t)Seq_remlo(memory->unmappedIDs);
                /* put the sequence in the ID it corresponds in the "mapped" sequence */
                Seq_put(memory->segments, segmentID, Seq_new(size));
                return segmentID;
        } 
        /* create a new sequence of the given size and add it to the end of the
        sequence segments */
        Seq_addhi(memory->segments, Seq_new(size));
        /* return the index of the new segment */
        return Seq_length(memory->segments) - 1;
}


void segment_unmap(Memory memory, uint32_t segmentID)
{
        assert(memory);
        assert(memory->segments);
        assert(memory->unmappedIDs);
                     
        /* set the unmapped segment to NULL and place its ID into unmappedIDs */
        Seq_T segment = Seq_put(memory->segments, segmentID, NULL);
        Seq_free(&segment);
        Seq_addhi(memory->unmappedIDs, (void *)(uintptr_t)segmentID);    
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
        return memory->segments;
}


void set_segments(Memory memory, int index, Seq_T segments) 
{
        assert(memory);
        assert(memory->segments);
        assert(segments);
        if (index == 0 || index == Seq_length(memory->segments)) {
                Seq_addhi(memory->segments, segments);
        } else {
                Seq_put(memory->segments, index, segments);
        }
}

void set_program_counter(Memory memory, uint32_t value)
{
        assert(memory);
        memory->program_counter = value;
}