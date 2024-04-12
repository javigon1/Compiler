#include "memory.h"

void test_map_segment();

int main()
{
       test_map_segment();
}

void test_map_segment()
{
    Memory memory = new_memory();
    uint32_t segmentID = map_segment(memory, 10);
    assert(segmentID == 0);
    Seq_T segments = get_segments(memory);
    assert(Seq_length(segments) == 1);
    Seq_T segment = Seq_get(segments, 0);
    assert(Seq_length(segment) == 10);
    free_memory(memory);
}