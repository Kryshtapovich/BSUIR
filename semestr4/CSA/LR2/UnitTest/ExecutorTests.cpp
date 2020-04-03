#include "doctest.h"

#include "Instructions.h"
#include "Decoder.h"
#include "Executor.h"

constexpr Word IP        = 0x200;
constexpr Word SRCVAL1   = 1;
constexpr Word SRCVAL2   = 2;

void testAlu(InstructionPtr &instruction, Executor &exe);
void testR(InstructionPtr &instruction, Executor &exe);
void testI(InstructionPtr &instruction, Executor &exe);
void testU(InstructionPtr &instruction, Executor &exe);
void testBranch(InstructionPtr &instruction, Executor &exe);
void testUJ(InstructionPtr &instruction, Executor &exe);
void setSLTI(Word &instr);

TEST_SUITE("Executor"){
    Decoder _decoder;
    Executor _exe;
    TEST_CASE("R-Format"){
        SUBCASE("AND"){
            auto instruction = _decoder.Decode(AND);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 & SRCVAL2);
        }

        SUBCASE("ADD"){
            auto instruction = _decoder.Decode(ADD);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 + SRCVAL2);
        }

        SUBCASE("OR"){
            auto instruction = _decoder.Decode(OR);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 | SRCVAL2);
        }

        SUBCASE("SUB"){
            auto instruction = _decoder.Decode(SUB);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 - SRCVAL2);
        }

        SUBCASE("SLL"){
            auto instruction = _decoder.Decode(SLL);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 << (SRCVAL2 % 32));
        }

        SUBCASE("XOR"){
            auto instruction = _decoder.Decode(XOR);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 ^ SRCVAL2);
        }

        SUBCASE("SRL"){
            auto instruction = _decoder.Decode(SRL);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 >> (SRCVAL2 % 32));
        }

        SUBCASE("SRA"){
            auto instruction = _decoder.Decode(SRA);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, Word((int)SRCVAL1 >> (SRCVAL2 % 32)));
        }

        SUBCASE("SLT"){
            auto instruction = _decoder.Decode(SLT);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, (int)SRCVAL1 < (int)SRCVAL2);
        }

        SUBCASE("SLTU"){
            auto instruction = _decoder.Decode(SLTU);
            testR(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 < SRCVAL2);

        }
    }

    TEST_CASE("I-Format"){
        SUBCASE("ANDI"){
            auto instruction = _decoder.Decode(ANDI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 & IMM);
        }

        SUBCASE("ADDI"){
            auto instruction = _decoder.Decode(ADDI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 + IMM);
        }

        SUBCASE("ORI"){
            auto instruction = _decoder.Decode(ORI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 | IMM);
        }

        SUBCASE("SLLI"){
            auto instruction = _decoder.Decode(SLLI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 << (IMM % 32));

        }

        SUBCASE("XORI"){
            auto instruction = _decoder.Decode(XORI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 ^ IMM);

        }

        SUBCASE("SRLI"){
            auto instruction = _decoder.Decode(SRLI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 >> (IMM % 32));

        }

        SUBCASE("SRAI"){
            auto instruction = _decoder.Decode(SRAI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, Word((int)SRCVAL1 >> (IMM % 32)));
        }

        SUBCASE("SLTIU"){
            auto instruction = _decoder.Decode(SLTIU);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, SRCVAL1 < IMM);
        }

        SUBCASE("SLTI"){
            auto instruction = _decoder.Decode(SLTI);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_data, (int)SRCVAL1 < (int)IMM);


        }

        // RV32 Load Instructions are also I-Type
        SUBCASE("LW"){
            auto instruction = _decoder.Decode(LW);
            testI(instruction, _exe);
            CHECK_EQ(instruction->_addr, SRCVAL1 + IMM);
        }
    }

    TEST_CASE("U-Format"){
        SUBCASE("AUIPC"){
            auto instruction = _decoder.Decode(AUIPC);
            testU(instruction, _exe);
            CHECK_EQ(instruction->_data, IP + (IMM_U << 12u));
        }

        SUBCASE("LUI"){
            auto instruction = _decoder.Decode(LUI);
            testU(instruction, _exe);
            CHECK_EQ(instruction->_data, IMM_U << 12u);
        }

    }

    TEST_CASE("S-Format"){
        SUBCASE("SW"){
            auto instruction = _decoder.Decode(SW);
            instruction->_src1Val = SRCVAL1;
            instruction->_src2Val = SRCVAL2;
            _exe.Execute(instruction, IP);

            CHECK_EQ(instruction->_data, SRCVAL2);
            CHECK_EQ(instruction->_addr, SRCVAL1 + IMM_S);
            CHECK_EQ(instruction->_nextIp, IP + 4);

        }
    }

    TEST_CASE("SB-Format"){
        SUBCASE("BEQ"){
            auto instruction = _decoder.Decode(BEQ);
            testBranch(instruction, _exe);
            CHECK_EQ(instruction->_nextIp, (SRCVAL1 == SRCVAL2 )? IP + IMM_SB : IP + 4);
        }

        SUBCASE("BGE"){
            auto instruction = _decoder.Decode(BGE);
            testBranch(instruction, _exe);
            CHECK_EQ(instruction->_nextIp, ((int)SRCVAL1 >= (int)SRCVAL2)? IP + IMM_SB : IP + 4);
        }

        SUBCASE("BGEU"){
            auto instruction = _decoder.Decode(BGEU);
            testBranch(instruction, _exe);
            CHECK_EQ(instruction->_nextIp, (SRCVAL1 >= SRCVAL2 )? IP + IMM_SB : IP + 4);

        }

        SUBCASE("BNE"){
            auto instruction = _decoder.Decode(BNE);
            testBranch(instruction, _exe);
            CHECK_EQ(instruction->_nextIp, (SRCVAL1 != SRCVAL2)? IP + IMM_SB : IP + 4);

        }

        SUBCASE("BLT"){
            auto instruction = _decoder.Decode(BLT);
            testBranch(instruction, _exe);
            CHECK_EQ(instruction->_nextIp, ((int)SRCVAL1 < (int)SRCVAL2 )? IP + IMM_SB : IP + 4);

        }

        SUBCASE("BLTU"){
            auto instruction = _decoder.Decode(BLTU);
            testBranch(instruction, _exe);
            CHECK_EQ(instruction->_nextIp, (SRCVAL1 < SRCVAL2 )? IP + IMM_SB : IP + 4);
        }

    }

    TEST_CASE("UJ-Format"){
        SUBCASE("JAL"){
            auto instruction = _decoder.Decode(JAL);
            testUJ(instruction, _exe);
        }

        SUBCASE("JALR"){
            auto instruction = _decoder.Decode(JALR);
            instruction->_src1Val = SRCVAL1;
            testUJ(instruction, _exe);

            CHECK_EQ(instruction->_nextIp, IMM_UJ + SRCVAL1);

        }
    }
    /* YOUR CODE HERE */
    TEST_CASE("MY_TEST")
    {
        Word instruction = 0;
        setSLTI(instruction);
        instruction->_src1Val = SRCVAL1;
        instruction->_imm.operator = (std::optional<Word>(IMM));

        _exe.Execute(instruction, IP);

        CHECK_EQ(instruction->_nextIp, IP + 4);
        CHECK_EQ(instruction->_data, (int)SRCVAL1 < (int)IMM);
        
    }
}

void setSLTI(Word &instr)
{
    instr += 0b11;
    instr <<= 5;
    instr += 0b1;
    instr <<= 3;
    instr += 0b10;
    instr <<= 5;
    instr += 0b1111;
    instr <<= 7;
    instr += 0b10011;
}

void testAlu(InstructionPtr &instruction, Executor &exe){
    instruction->_src1Val = SRCVAL1;
    exe.Execute(instruction, IP);

    CHECK_EQ(instruction->_nextIp, IP + 4);
}

void testR(InstructionPtr &instruction, Executor &exe){
    instruction->_src2Val = SRCVAL2;
    testAlu(instruction, exe);
}

void testI(InstructionPtr &instruction, Executor &exe){
    testAlu(instruction, exe);
}

void testU(InstructionPtr &instruction, Executor &exe){
    exe.Execute(instruction, IP);
    CHECK_EQ(instruction->_nextIp, IP + 4);
}

void testBranch(InstructionPtr &instruction, Executor &exe){
    instruction->_src1Val = SRCVAL1;
    instruction->_src2Val = SRCVAL2;
    exe.Execute(instruction, IP);
}

void testUJ(InstructionPtr &instruction, Executor &exe){
    exe.Execute(instruction, IP);
    CHECK_EQ(instruction->_data, IP + 4);
}
