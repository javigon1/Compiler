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
        memory->segments = Seq_new(0);
        memory->unmappedIDs = Seq_new(0);
        memory->program_counter = 0;

        return memory;
}

// doubt this works
uint32_t segment_map(Memory memory)
{
    uint32_t segmentID;
    if (Seq_length(memory->unmappedIDs) > 0) {
        segmentID = (uint32_t)(uintptr_t)Seq_remlo(memory->unmappedIDs);
    } else {
        segmentID = Seq_length(memory->segments);
        Seq_addhi(memory->segments, NULL);
    }
    return segmentID;
}