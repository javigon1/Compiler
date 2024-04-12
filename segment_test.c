#include "memory.h"

void test_map_segment();
void test_unmap_segment();

int main()
{
        test_map_segment();
        test_unmap_segment();
}

void test_map_segment()
{
        Memory memory = new_memory();
        uint32_t segmentID = segment_map(memory, 10);
        assert(segmentID == 0);
        Seq_T segments = get_segments(memory);
        assert(Seq_length(segments) == 1);
        Seq_T segment = Seq_get(segments, 0);
        assert(Seq_length(segment) == 10);
        free_memory(memory);
}

void test_unmap_segment()
{   
        Memory memory = new_memory();
        uint32_t segmentID = segment_map(memory, 10);
        assert(segmentID == 0);
        Seq_T segments = get_segments(memory);
        assert(Seq_length(segments) == 1);
        Seq_T segment = Seq_get(segments, 0);
        assert(Seq_length(segment) == 10);
        segment_unmap(memory, 0);
        assert(Seq_length(segments) == 1);
        free_memory(memory);
}