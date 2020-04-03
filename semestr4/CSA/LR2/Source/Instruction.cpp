
#include "Instruction.h"

constexpr unsigned maxInstructionInFlight = 8;

template <>
PoolAllocator<Instruction> PoolAllocated<Instruction>::allocator{maxInstructionInFlight};