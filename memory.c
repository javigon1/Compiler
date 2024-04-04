#include "memory.h"

typedef struct Memory {
        Seq_T segments;
        Seq_T unmappedIDs;
        uint32_t program_counter;
}