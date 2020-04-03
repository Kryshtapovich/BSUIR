
#ifndef RISCV_SIM_DECODER_H
#define RISCV_SIM_DECODER_H

#include "Instruction.h"

// This decoder implementation is stateless, so it could be a function as well
class Decoder
{

public:
    InstructionPtr Decode(Word data)
    {
        DecodedInstr decoded{data};

        InstructionPtr instr = std::make_unique<Instruction>();
        Imm immI = SignExtend(decoded.i.imm11_0, 11);
        Imm immS = SignExtend(decoded.s.imm11_5 << 5u | decoded.s.imm4_0, 11);
        Word immU = decoded.u.imm31_12 << 12u;
        Imm immB = SignExtend((decoded.b.imm12 << 12u) | (decoded.b.imm11 << 11u) |
                              (decoded.b.imm10_5 << 5u) | (decoded.b.imm4_1 << 1u),
                              12);
        Imm immJ = SignExtend((decoded.j.imm20 << 20u) | (decoded.j.imm19_12 << 12u) |
                              (decoded.j.imm11 << 11u) | (decoded.j.imm10_1 << 1u),
                              20);

        switch (static_cast<Opcode>(decoded.i.opcode))
        {
            case Opcode::OpImm:
            {
                instr->_imm = immI;
                instr->_type = IType::Alu;
                instr->_aluFunc = static_cast<AluFunc>(decoded.i.funct3);
                if (instr->_aluFunc == AluFunc::Sr)
                {
                    instr->_aluFunc = decoded.r.aluSel ? AluFunc::Sra : AluFunc::Srl;
                    instr->_imm.value() &= 31u;
                }
                instr->_dst = RId(decoded.i.rd);
                instr->_src1 = RId(decoded.i.rs1);
                break;
            }
            case Opcode::Op:
            {
                instr->_type = IType::Alu;
                auto funct3 = AluFunc(decoded.r.funct3);
                if (funct3 == AluFunc::Add)
                {
                    instr->_aluFunc = decoded.r.aluSel == 0 ? AluFunc::Add : AluFunc::Sub;
                }
                else if (funct3 == AluFunc::Sr)
                {
                    instr->_aluFunc = decoded.r.aluSel ? AluFunc::Sra : AluFunc::Srl;
                }
                else
                {
                    instr->_aluFunc = funct3;
                }
                instr->_dst = RId(decoded.r.rd);
                instr->_src1 = RId(decoded.r.rs1);
                instr->_src2 = RId(decoded.r.rs2);
                break;
            }
            case Opcode::Lui:
            {
                instr->_type = IType::Alu;
                instr->_aluFunc = AluFunc::Add;
                instr->_dst = RId(decoded.u.rd);
                instr->_src1 = 0;
                instr->_imm = immU;
                break;
            }
            case Opcode::Auipc:
            {
                instr->_type = IType::Auipc;
                instr->_dst = RId(decoded.u.rd);
                instr->_imm = immU;
                break;
            }
            case Opcode::Jal:
            {
                instr->_type = IType::J;
                instr->_brFunc = BrFunc::AT;
                instr->_dst = RId(decoded.j.rd);
                instr->_imm = immJ;
                break;
            }
            case Opcode::Jalr:
            {
                instr->_type = IType::Jr;
                instr->_brFunc = BrFunc::AT;
                instr->_dst = RId(decoded.i.rd);
                instr->_src1 = RId(decoded.i.rs1);
                instr->_imm = immI;
                break;
            }
            case Opcode::Branch:
            {
                instr->_type = IType::Br;
                instr->_brFunc = static_cast<BrFunc>(decoded.b.funct3);
                instr->_src1 = RId(decoded.b.rs1);
                instr->_src2 = RId(decoded.b.rs2);
                instr->_imm = immB;
                break;
            }
            case Opcode::Load:
            {
                instr->_type = decoded.i.funct3 == fnLW ? IType::Ld : IType::Unsupported;
                instr->_aluFunc = AluFunc::Add;
                instr->_dst = RId(decoded.i.rd);
                instr->_src1 = RId(decoded.i.rs1);
                instr->_imm = immI;
                break;
            }
            case Opcode::Store:
            {
                instr->_type = decoded.i.funct3 == fnSW ? IType::St : IType::Unsupported;
                instr->_aluFunc = AluFunc::Add;
                instr->_src1 = RId(decoded.s.rs1);
                instr->_src2 = RId(decoded.s.rs2);
                instr->_imm = immS;
                break;
            }
            case Opcode::System:
            {
                if (decoded.i.funct3 == fnCSRRW && decoded.i.rd == 0)
                {
                    instr->_type = IType::Csrw;
                }
                else if (decoded.i.funct3 == fnCSRRS && decoded.i.rs1 == 0)
                {
                    instr->_type = IType::Csrr;
                }
                instr->_dst = RId(decoded.i.rd);
                instr->_src1 = RId(decoded.i.rs1);
                instr->_csr = static_cast<CsrIdx>(immI & 0xfff);
                break;
            }
            // LR SC FENCE AMO not implemented
            case Opcode::MiscMem:
            case Opcode::Amo:
            default:
            {
                instr->_type = IType::Unsupported;
                instr->_aluFunc = AluFunc::None;
                instr->_brFunc = BrFunc::NT;
            }
        }

        if (instr->_dst.value_or(0) == 0)
            instr->_dst.reset();

        return instr;
    }

private:
    using Imm = int32_t;

    Imm SignExtend(Imm i, unsigned sbit)
    {
        return i + ((0xffffffff << (sbit + 1)) * ((i & (1u << sbit)) >> sbit));
    }
    union DecodedInstr
    {
        Word instr;
        struct rType
        {
            uint32_t opcode : 7;
            uint32_t rd : 5;
            uint32_t funct3 : 3;
            uint32_t rs1 : 5;
            uint32_t rs2 : 5;
            uint32_t reserved1 : 5;
            uint32_t aluSel : 1;
            uint32_t reserved2 : 1;
        } r;
        struct iType
        {
            uint32_t opcode : 7;
            uint32_t rd : 5;
            uint32_t funct3 : 3;
            uint32_t rs1 : 5;
            uint32_t imm11_0 : 12;
        } i;
        struct sType
        {
            uint32_t opcode : 7;
            uint32_t imm4_0 : 5;
            uint32_t funct3 : 3;
            uint32_t rs1 : 5;
            uint32_t rs2 : 5;
            uint32_t imm11_5 : 7;
        } s;
        struct bType
        {
            uint32_t opcode : 7;
            uint32_t imm11 : 1;
            uint32_t imm4_1 : 4;
            uint32_t funct3 : 3;
            uint32_t rs1 : 5;
            uint32_t rs2 : 5;
            uint32_t imm10_5 : 6;
            uint32_t imm12 : 1;
        } b;
        struct uType
        {
            uint32_t opcode : 7;
            uint32_t rd : 5;
            uint32_t imm31_12 : 20;
        } u;
        struct jType
        {
            uint32_t opcode : 7;
            uint32_t rd : 5;
            uint32_t imm19_12 : 8;
            uint32_t imm11 : 1;
            uint32_t imm10_1 : 10;
            uint32_t imm20 : 1;
        } j;

    };
};

#endif //RISCV_SIM_DECODER_H
