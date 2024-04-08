#include "memory.h"

struct Memory {
        Seq_T segments;
        Seq_T unmappedIDs;
        uint32_t program_counter;
        uint32_t registers[8];
};


Memory new_memory()
{
        Memory memory;
        NEW(memory);
        memory->segments = Seq_new(1);
        memory->unmappedIDs = Seq_new(0);
        memory->program_counter = 0;

        return memory;
}

void free_memory(Memory memory)
{
        Seq_free(&memory->segments);
        Seq_free(&memory->unmappedIDs);
        FREE(memory);
}                                                                               /* check these two functions */


uint32_t segment_map(Memory memory, uint32_t size)
{
        assert(memory->segments);
        /* check if there is an unmapped ID so we don't have to create another */
        if (Seq_length(memory->unmappedIDs) > 0) {
                /* empty the information in that segment */
                // Seq_T unmapped_segment = Seq_remhi(memory->unmappedIDs);
                //                                                                 /* is it okay to free this memory and create another sequence or are they looking for something else? */
                // Seq_free(&unmapped_segment);                                    /* instead o the line 35 and 37 should I just say: uint32_t segmentID = (uint32_t)(uintptr_t)Seq_remlo(memory->unmappedIDs) - avodid the free ?*/
                // /* add a new segment with given size */
                // Seq_addlo(memory->segments, Seq_new(size));
                // return (memory->program_counter)++;
                uint32_t segmentID = (uint32_t)(uintptr_t)Seq_remlo(memory->unmappedIDs);
                Seq_addlo(memory->segments, Seq_new(size));
                return segmentID;
        } 

        Seq_addlo(memory->segments, Seq_new(size));
        return (memory->program_counter)++;
}


void segment_unmap(Memory memory, uint32_t segmentID)
{
        assert(memory->segments);
        assert(memory->unmappedIDs);
                                                                                /* do we need to assert the unmappedIDs too? */
        Seq_addlo(memory->unmappedIDs, (void *)(uintptr_t)segmentID);           /* do we need to remove it from the */

}


uint32_t get_register(Memory memory, uint32_t register_index)
{
        assert(register_index < 8);
        return memory->registers[register_index];
}


void set_register(Memory memory, uint register_index, uint32_t value)
{
        assert(register_index < 8);
        memory->registers[register_index] = value;
}


Seq_T get_segments(Memory memory) {
        assert(memory);
        return memory->segments;
}


void set_segments(Memory memory, Seq_T segments) {
        assert(memory);
        assert(segments);
        memory->segments = segments;
}