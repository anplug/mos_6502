#include "_common.h"

// LDA

void LDA_Imediate() {
    IMEDIATE(LDA);
    cpu.acc = arg;
    cpu.program_counter += 2;
    checkNegZero(&cpu.acc);
}

void LDA_Zero() {
    ZERO_PAGE(LDA);
    cpu.acc = cpu.mem[arg];
    cpu.program_counter += 2;
    checkNegZero(&cpu.acc);
}

void LDA_Zero_X() {
    ZERO_PAGE_X(LDA);
    cpu.acc = cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
    checkNegZero(&cpu.acc);
}

void LDA_Abs() {
    ABSOLUTE(LDA);
    cpu.acc = cpu.mem[arg];
    cpu.program_counter += 3;
    checkNegZero(&cpu.acc);
}

void LDA_Abs_X() {
    ABSOLUTE_X(LDA);
    cpu.acc = cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
    checkNegZero(&cpu.acc);
}

void LDA_Abs_Y() {
    ABSOLUTE_Y(LDA);
    cpu.acc = cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
    checkNegZero(&cpu.acc);
}

void LDA_Ind_X() {
    INDIRECT_X(LDA);
    cpu.acc = cpu.mem[getIndexedIndirectAddress(arg)];
    cpu.program_counter += 2;
    checkNegZero(&cpu.acc);
}

void LDA_Ind_Y() {
    INDIRECT_Y(LDA);
    cpu.acc = cpu.mem[getIndirectIndexedAddress(arg)];
    cpu.program_counter += 2;
    checkNegZero(&cpu.acc);
}

// LDX

void LDX_Imediate() {
    IMEDIATE(LDX);
    cpu.x = arg;
    cpu.program_counter += 2;
    checkNegZero(&cpu.x);
}

void LDX_Zero() {
    ZERO_PAGE(LDX);
    cpu.x = cpu.mem[arg];
    cpu.program_counter += 2;
    checkNegZero(&cpu.x);
}

void LDX_Zero_Y() {
    ZERO_PAGE_Y(LDX);
    cpu.x = cpu.mem[arg + cpu.y];
    cpu.program_counter += 2;
    checkNegZero(&cpu.x);
}

void LDX_Abs() {
    ABSOLUTE(LDX);
    cpu.x = cpu.mem[arg];
    cpu.program_counter += 3;
    checkNegZero(&cpu.x);
}

void LDX_Abs_Y() {
    ABSOLUTE_Y(LDX);
    cpu.x = cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
    checkNegZero(&cpu.x);
}

// LDY

void LDY_Imediate() {
    IMEDIATE(LDY);
    cpu.y = arg;
    cpu.program_counter += 2;
    checkNegZero(&cpu.y);
}

void LDY_Zero() {
    ZERO_PAGE(LDY);
    cpu.y = cpu.mem[arg];
    cpu.program_counter += 2;
    checkNegZero(&cpu.y);
}

void LDY_Zero_Y() {
    ZERO_PAGE_X(LDY);
    cpu.y = cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
    checkNegZero(&cpu.y);
}

void LDY_Abs() {
    ABSOLUTE(LDY);
    cpu.y = cpu.mem[arg];
    cpu.program_counter += 3;
    checkNegZero(&cpu.y);
}

void LDY_Abs_X() {
    ABSOLUTE_X(LDY);
    cpu.y = cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
    checkNegZero(&cpu.y);
}

// STA

void STA_Zero() {
    ZERO_PAGE(STA);
    cpu.mem[arg] = cpu.acc;
    cpu.program_counter += 2;
}

void STA_Zero_X() {
    ZERO_PAGE_X(STA);
    cpu.mem[arg + cpu.x] = cpu.acc;
    cpu.program_counter += 2;
}

void STA_Abs() {
    ABSOLUTE(STA);
    cpu.mem[arg] = cpu.acc;
    cpu.program_counter += 3;
}

void STA_Abs_X() {
    ABSOLUTE_X(STA);
    cpu.mem[arg + cpu.x] = cpu.acc;
    cpu.program_counter += 3;
}

void STA_Abs_Y() {
    ABSOLUTE_Y(STA);
    cpu.mem[arg + cpu.y] = cpu.acc;
    cpu.program_counter += 3;
}

void STA_Ind_X() {
    INDIRECT_X(STA);
    cpu.mem[getIndexedIndirectAddress(arg)] = cpu.acc;
    cpu.program_counter += 2;
}

void STA_Ind_Y() {
    INDIRECT_Y(STA);
    cpu.mem[getIndirectIndexedAddress(arg)] = cpu.acc;
    cpu.program_counter += 2;
}

// STX

void STX_Zero() {
    ZERO_PAGE(STA);
    cpu.mem[arg] = cpu.x;
    cpu.program_counter += 2;
}

void STX_Zero_Y() {
    ZERO_PAGE_X(STA);
    cpu.mem[arg + cpu.y] = cpu.x;
    cpu.program_counter += 2;
}

void STX_Abs() {
    ABSOLUTE(STA);
    cpu.mem[arg] = cpu.x;
    cpu.program_counter += 3;
}

// STY

void STY_Zero() {
    ZERO_PAGE(STA);
    cpu.mem[arg] = cpu.y;
    cpu.program_counter += 2;
}

void STY_Zero_X() {
    ZERO_PAGE_X(STA);
    cpu.mem[arg + cpu.x] = cpu.y;
    cpu.program_counter += 2;
}

void STY_Abs() {
    ABSOLUTE(STA);
    cpu.mem[arg] = cpu.y;
    cpu.program_counter += 3;
}
