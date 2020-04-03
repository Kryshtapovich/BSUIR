
#ifndef RISCV_SIM_REGISTERFILE_H
#define RISCV_SIM_REGISTERFILE_H

#include "Instruction.h"

class RegisterFile
{
public:
    RegisterFile()
    {
        _r.fill(0);
    }

    void Read(InstructionPtr& instr)
    {
        if (instr->_src1)
            instr->_src1Val = _r.at(instr->_src1.value());

        if (instr->_src2)
            instr->_src2Val = _r.at(instr->_src2.value());
    }
    void Write(InstructionPtr& instr)
    {
        if (instr->_dst)
            _r.at(instr->_dst.value()) = instr->_data;
    }
private:
    std::array<Word, 32> _r;
};


#endif //RISCV_SIM_REGISTERFILE_H
