
#ifndef RISCV_SIM_INSTRUCTION_H
#define RISCV_SIM_INSTRUCTION_H

#include <optional>
#include <memory>

#include "BaseTypes.h"
#include "PoolAllocator.h"


enum class Opcode : uint8_t
{
    Load    = 0b0000011,
    MiscMem = 0b0001111,
    OpImm   = 0b0010011,
    Auipc   = 0b0010111,
    Store   = 0b0100011,
    Amo     = 0b0101111,
    Op      = 0b0110011,
    Lui     = 0b0110111,
    Branch  = 0b1100011,
    Jalr    = 0b1100111,
    Jal     = 0b1101111,
    System  = 0b1110011,
};

enum class CsrIdx : RId
{
    Instret = 0xc02,
    Cycle   = 0xc00,
    Mhartid = 0xf10,
    Mtohost = 0x780,
    None    = 0xfff,
};

// LR, SC, FENCE not implemented
// LB(U), LH(U), SB, SH not implemented

// For CSR, only following two are implemented
// CSRR rd csr (i.e. CSRRS rd csr x0)
// CSRW csr rs1 (i.e. CSRRW x0 csr rs1)

// SCALL, SBREAK not implemented

enum class IType
{
    Unsupported,
    Alu,
    Ld,
    St,
    J,
    Jr,
    Br,
    Csrr,
    Csrw,
    Auipc
};

enum class BrFunc : uint8_t
{
    Eq  = 0b000,
    Neq = 0b001,
    Lt  = 0b100,
    Ltu = 0b110,
    Ge  = 0b101,
    Geu = 0b111,
    AT,
    NT,
};

enum class AluFunc
{
    Add  = 0b000,
    Sll  = 0b001,
    Slt  = 0b010,
    Sltu = 0b011,
    Xor  = 0b100,
    And  = 0b111,
    Or   = 0b110,
    Sr   = 0b101,
    Sub  = 0b1000,
    Sra,
    Srl,
    None,
};

struct Instruction : public PoolAllocated<Instruction>
{
    IType _type = IType::Unsupported;
    BrFunc _brFunc = BrFunc::NT;
    AluFunc _aluFunc;
    std::optional<RId> _dst;
    std::optional<RId> _src1;
    std::optional<RId> _src2;
    std::optional<CsrIdx> _csr;
    std::optional<Word> _imm;

    Word _src1Val;
    Word _src2Val;
    Word _csrVal;
    Word _data = 0xdeadbeaf;
    Word _addr = 0xdeadbeaf;
    Word _nextIp = 0xdeadbeaf;
};

using InstructionPtr = std::unique_ptr<Instruction>;

// Load
constexpr uint8_t fnLW    = 0b010;
//constexpr uint8_t fnLB    = 0b000;
//constexpr uint8_t fnLH    = 0b001;
//constexpr uint8_t fnLBU   = 0b100;
//constexpr uint8_t fnLHU   = 0b101;
// Store
constexpr uint8_t fnSW    = 0b010;
//constexpr uint8_t fnSB    = 0b000;
//constexpr uint8_t fnSH    = 0b001;
// Amo
constexpr uint8_t fnLR    = 0b00010;
constexpr uint8_t fnSC    = 0b00011;
//MiscMem
constexpr uint8_t fnFENCE  = 0b000;
//constexpr uint8_t fnFENCEI = 0b001;
// System
constexpr uint8_t fnCSRRW  = 0b001;
constexpr uint8_t fnCSRRS  = 0b010;
//constexpr uint8_t fnCSRRC  = 0b011;
//constexpr uint8_t fnCSRRWI = 0b101;
//constexpr uint8_t fnCSRRSI = 0b110;
//constexpr uint8_t fnCSRRCI = 0b111;
constexpr uint8_t fnPRIV   = 0b000;
constexpr uint8_t privSCALL    = 0b000;


#endif //RISCV_SIM_INSTRUCTION_H
