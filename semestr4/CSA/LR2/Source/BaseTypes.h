
#ifndef RISCV_SIM_BASETYPES_H
#define RISCV_SIM_BASETYPES_H

using Reg32 = uint32_t;
using RId = uint16_t;
using Word = uint32_t;
using SignedWord = int32_t;

enum class CpuToHostType : uint16_t
{
    ExitCode = 0,
    PrintChar = 1,
    PrintIntLow = 2,
    PrintIntHigh = 3
};

union CpuToHostData
{
    Word payload;
    struct {
        uint16_t data;
        CpuToHostType type;
    } unpacked;
};

#endif //RISCV_SIM_BASETYPES_H
