
#ifndef RISCV_SIM_CSRFILE_H
#define RISCV_SIM_CSRFILE_H

#include <optional>
#include "Instruction.h"

class CsrFile
{
public:
    void Reset()
    {
        numInstr = 0;
        numCycles = 0;
        coreId = 0;
        cpuToHostData.reset();
        startReg = true;
    }
    void Read(InstructionPtr& instr)
    {
        if (!instr->_csr)
            return;

        switch (static_cast<CsrIdx>(instr->_csr.value()))
        {
            case CsrIdx::Instret: instr->_csrVal = numInstr; break;
            case CsrIdx::Cycle  : instr->_csrVal = numCycles; break;
            case CsrIdx::Mhartid: instr->_csrVal = coreId; break;
            default: break;
        }
    }
    void Write(InstructionPtr& instr)
    {
        if (instr->_type == IType::Csrw && instr->_csr.value_or(CsrIdx::None) == CsrIdx::Mtohost)
        {
            cpuToHostData = CpuToHostData{instr->_data};
        }
    }
    void InstructionExecuted()
    {
        numInstr++;
        numCycles++;
    }

    std::optional<CpuToHostData> GetMessage()
    {
        std::optional<CpuToHostData> ret;
        cpuToHostData.swap(ret);
        return ret;
    }
private:
    Word numInstr = 0;
    Word numCycles = 0;
    Word coreId = 0;
    std::optional<CpuToHostData> cpuToHostData;
    bool startReg = false;

};

#endif //RISCV_SIM_CSRFILE_H
