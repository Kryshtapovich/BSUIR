
#ifndef RISCV_SIM_CPU_H
#define RISCV_SIM_CPU_H

#include "Memory.h"
#include "Decoder.h"
#include "RegisterFile.h"
#include "CsrFile.h"
#include "Executor.h"

class Cpu
{
public:
    Cpu(Memory& mem)
        : _mem(mem)
    {

    }

    void ProcessInstruction()
    {
        /* YOUR CODE HERE */
        Word instructionWord = _mem.Request(_ip);
        InstructionPtr instruction = _decoder.Decode(instructionWord);

        _rf.Read(instruction);  
        _csrf.Read(instruction);

        _exe.Execute(instruction, _ip);
        _mem.Request(instruction);
        
        _rf.Write(instruction);
        _csrf.Write(instruction);

        _csrf.InstructionExecuted();
        _ip = instruction->_nextIp;
    }

    void Reset(Word ip)
    {
        _csrf.Reset();
        _ip = ip;
    }

    std::optional<CpuToHostData> GetMessage()
    {
        return _csrf.GetMessage();
    }

private:
    Reg32 _ip;
    Decoder _decoder;
    RegisterFile _rf;
    CsrFile _csrf;
    Executor _exe;
    Memory& _mem;
};


#endif //RISCV_SIM_CPU_H
