#include "memory.h"

int main()
{
        Memory memory;
        memory.segments = Seq_new(0);
        memory.unmappedIDs = Seq_new(0);

        Seq_addhi(memory.unmappedIDs, (void *)(uintptr_t)1);
        Seq_addhi(memory.unmappedIDs, (void *)(uintptr_t)2);
        Seq_addhi(memory.unmappedIDs, (void *)(uintptr_t)3);

        uint32_t mapped1 = segment_map(memory);
        uint32_t mapped2 = segment_map(memory);
        uint32_t mapped3 = segment_map(memory);

        printf("Mapped Segment IDs: %u, %u, %u\n", mapped1, mapped2, mapped3);

        /* Check if the unmappedIDs sequence is empty */
        printf("Unmapped IDs Length: %d\n", Seq_length(memory.unmappedIDs));

        Seq_free(&memory.segments);
        Seq_free(&memory.unmappedIDs);
        return 0;
}