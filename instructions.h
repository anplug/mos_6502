#include "cpu.h"

void LDA_Imediate() {
    IMEDIATE(LDA);
    cpu.acc = arg;
    cpu.program_counter += 2;
    checkState();
}

void LDA_Zero() {
    ZERO_PAGE(LDA);
    cpu.acc = cpu.mem[arg];
    cpu.program_counter += 2;
    checkState();
}

void LDA_Zero_X() {
    ZERO_PAGE_X(LDA);
    cpu.acc = cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
    checkState();
}

void LDA_Abs() {
    ABSOLUTE(LDA);
    cpu.acc = cpu.mem[arg];
    cpu.program_counter += 3;
    checkState();
}

void LDA_Abs_X() {
    ABSOLUTE_X(LDA);
    cpu.acc = cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
    checkState();
}
void LDA_Abs_Y() {
    ABSOLUTE_Y(LDA);
    cpu.acc = cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
    checkState();
}

void LDA_Ind_X() {
    INDIRECT_X(LDA);
    cpu.acc = cpu.mem[getIndexedIndirectAddress(arg)];
    cpu.program_counter += 2;
    checkState();
}

void LDA_Ind_Y() {
    INDIRECT_Y(LDA);
    cpu.acc = cpu.mem[getIndirectIndexedAddress(arg)];
    cpu.program_counter += 2;
    checkState();
}

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
    checkState();
}

void STA_Ind_Y() {
    INDIRECT_Y(STA);
    cpu.mem[getIndirectIndexedAddress(arg)] = cpu.acc;
    cpu.program_counter += 2;
    checkState();
}

void LDX_Imediate() {
    IMEDIATE(LDX);
    cpu.x = arg;
    cpu.program_counter += 2;
    checkState();
}

void LDX_Zero() {
    ZERO_PAGE(LDX);
    cpu.x = cpu.mem[arg];
    cpu.program_counter += 2;
    checkState();
}

void LDX_Zero_Y() {
    ZERO_PAGE_Y(LDX);
    cpu.x = cpu.mem[arg + cpu.y];
    cpu.program_counter += 2;
    checkState();
}

void LDX_Abs() {
    ABSOLUTE(LDX);
    cpu.x = cpu.mem[arg];
    cpu.program_counter += 3;
    checkState();
}

void LDX_Abs_Y() {
    ABSOLUTE_Y(LDX);
    cpu.x = cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
    checkState();
}

void LDY_Imediate() {
    IMEDIATE(LDY);
    cpu.y = arg;
    cpu.program_counter += 2;
    checkState();
}

void LDY_Zero() {
    ZERO_PAGE(LDY);
    cpu.y = cpu.mem[arg];
    cpu.program_counter += 2;
    checkState();
}

void  LDY_Zero_Y() {
    ZERO_PAGE_X(LDY);
    cpu.y = cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
    checkState();
}

void LDY_Abs() {
    ABSOLUTE(LDY);
    cpu.y = cpu.mem[arg];
    cpu.program_counter += 3;
    checkState();
}

void LDY_Abs_X() {
    ABSOLUTE_X(LDY);
    cpu.y = cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
    checkState();
}

inst_ptr_t inst_matrix[256] = {
    [0XA9] = &LDA_Imediate,
    [0XA5] = &LDA_Zero,
    [0XB5] = &LDA_Zero_X,
    [0XAD] = &LDA_Abs,
    [0XBD] = &LDA_Abs_X,
    [0XB9] = &LDA_Abs_Y,
    [0XA1] = &LDA_Ind_X,
    [0XB1] = &LDA_Ind_Y,

    [0X85] = &STA_Zero,
    [0X95] = &STA_Zero_X,
    [0X8D] = &STA_Abs,
    [0X9D] = &STA_Abs_X,
    [0X9D] = &STA_Abs_X,
    [0X81] = &STA_Ind_X,
    [0X91] = &STA_Ind_Y,

    [0XA2] = &LDX_Imediate,
    [0XA6] = &LDX_Zero,
    [0XB6] = &LDX_Zero_Y,
    [0XAE] = &LDX_Abs,
    [0XBE] = &LDX_Abs_Y,

    [0XA0] = &LDY_Imediate,
    [0XA4] = &LDY_Zero,
    [0XB4] = &LDY_Zero_Y,
    [0XAC] = &LDY_Abs,
    [0XBC] = &LDY_Abs_X
};
