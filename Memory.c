#include "Memory.h"

typedef struct Memory {
        Seq_T segments;
        Seq_T unmapped_IDs;
        uint32_t program_counter; 
} Memory;
