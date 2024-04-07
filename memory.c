#include "memory.h"

struct Memory {
        Seq_T segments;
        Seq_T unmappedIDs;
        uint32_t program_counter;
};


Memory segment_new()
{
        Memory memory;
        NEW(memory);
        memory->segments = Seq_new(1);
        memory->unmappedIDs = Seq_new(0);
        memory->program_counter = 0;

        return memory;
}

void segment_free(Memory memory)
{
        Seq_free(&memory->segments);
        Seq_free(&memory->unmappedIDs);
        FREE(memory);
}


uint32_t segment_map(Memory memory, uint32_t size)
{
        assert(memory->segments);
        /* check if there is an unmapped ID so we don't have to create another */
        if (Seq_length(memory->unmappedIDs) > 0) {
                /* empty the information in that segment */
                Seq_T unmapped_segment = Seq_remhi(memory->unmappedIDs);
                Seq_free(&unmapped_segment);
                /* add a new segment with given size */
                Seq_addlo(memory->segments, Seq_new(size));
                return (memory->program_counter)++;
        } 

        Seq_addlo(memory->segments, Seq_new(size));
        return (memory->program_counter)++;
}