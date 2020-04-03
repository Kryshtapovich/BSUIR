
#ifndef RISCV_SIM_EXECUTOR_H
#define RISCV_SIM_EXECUTOR_H

#include "Instruction.h"

class Executor
{
public:
    void Execute(InstructionPtr& instr, Word ip)
    {
        /* YOUR CODE HERE */
        switch (instr->_type)
        {
            case IType::Alu:
            {
                Alu(instr, instr->_data);
                TransitionComputing(instr, instr->_nextIp, ip);
                break;
            }

            case IType::Br:
            {
                Alu(instr, instr->_data);
                Word nextIp = ip + instr->_imm.value();
                TransitionComputing(instr, instr->_nextIp, ip, nextIp);
                break;
            }

            case IType::Ld:
            {
                Alu(instr, instr->_addr);  
                TransitionComputing(instr, instr->_nextIp, ip);
                break;
            }

            case IType::St:
            {
                Alu(instr, instr->_addr);
                instr->_data = instr->_src2Val;  
                TransitionComputing(instr, instr->_nextIp, ip);
                break;
            }

            case IType::Csrr:
            {
                instr->_data = instr->_csrVal; 
                TransitionComputing(instr, instr->_nextIp, ip);
                break;
            }

            case IType::Csrw:
            {
                instr->_data = instr->_src1Val;  
                TransitionComputing(instr, instr->_nextIp, ip);
                break;
            }

            case IType::J:
            {
                Word nextIp = ip + instr->_imm.value();
                TransitionComputing(instr, instr->_nextIp, ip, nextIp);
                instr->_data = ip + 4;
                break;
            }

            case IType::Jr:
            {
                instr->_data = ip + 4;
                Word nextIp = instr->_src1Val + instr->_imm.value(); 
                TransitionComputing(instr, instr->_nextIp, ip, nextIp);
                break;
            }

            case IType::Auipc:
            {
                instr->_data = ip + instr->_imm.value();
                TransitionComputing(instr, instr->_nextIp, ip);
                break;
            }
        }
    }

private:
    /* YOUR CODE HERE */
    void Alu(InstructionPtr& instr, Word& field)
    {
        Word a, b;
        if(instr->_src1 && (instr->_imm || instr->_src2))
        {
            a = instr->_src1Val;
            b = instr->_imm ? instr->_imm.value() : instr->_src2Val;
        }
        else
        {
            return;
        }

        switch (instr->_aluFunc)
        {
            case AluFunc::Add:
            {
                field = a + b;
                break;
            }

            case AluFunc::Sub:
            {
                field = a - b;
                break;
            }

            case AluFunc::And:
            {
                field = a & b;
                break;
            }

            case AluFunc::Or:
            {
                field = a | b;
                break;
            }

            case AluFunc::Xor:
            {
                field =  a ^ b;  
                break;
            }

            case AluFunc::Slt:
            {
                field = (int32_t)a < (int32_t)b;
                break;
            }

            case AluFunc::Sltu:
            {
                field = a < b;
                break;
            }

            case AluFunc::Sll:
            {
                field = a << (b % 32);
                break;
            }

            case AluFunc::Srl:
            {
                field = a >> (b % 32);
                break;
            }

            case AluFunc::Sra:
            {
                field = (int32_t)a >> ((int32_t)b % 32);
                break;
            }
        }
    }

    void TransitionComputing(InstructionPtr& instr, Word& field, Word currIp, std::optional<Word>next = NULL)
    {
        Word a, b, nextIp;
        if(instr->_src1 && instr->_src2)
        {
            a = instr->_src1Val;
            b = instr->_src2Val;
        }
       
        if(next)
        {
            nextIp = next.value();
        }

        switch (instr->_brFunc)
        {
            case BrFunc::Eq:
            {
                field = ((a == b) && nextIp) ? nextIp : currIp + 4;
                break;
            }

            case BrFunc::Neq:
            {
                field = ((a != b) && nextIp) ? nextIp : currIp + 4;
                break;
            }
        
            case BrFunc::Lt:
            {    
                field = (((int32_t)a < (int32_t)b) && nextIp) ? nextIp : currIp + 4;
                break;
            }

            case BrFunc::Ltu:
            {    
                field = ((a < b) && nextIp) ? nextIp : currIp + 4;
                break;
            }

            case BrFunc::Ge:
            {    
                field = (((int32_t)a >= (int32_t)b) && nextIp) ? nextIp : currIp + 4;
                break;
            }

            case BrFunc::Geu:
            {    
                field = ((a >= b) && nextIp) ? nextIp : currIp + 4;
                break;
            }

            case BrFunc::AT:
            {
                field = nextIp;
                break;
            }

            case BrFunc::NT:
            {
                field = currIp + 4;
                break;
            }
        }
    }
};

#endif // RISCV_SIM_EXECUTOR_H
