#include "cpu.h"

#define ACCUMULATOR(ins) \
    printf(#ins " A\n");

#define IMEDIATE(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " #$%.2X\n", arg);

#define ZERO_PAGE(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " $%.2X\n", arg);

#define ZERO_PAGE_X(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " $%.2X, X\n", arg);

#define ZERO_PAGE_Y(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " $%.2X, Y\n", arg);

#define ABSOLUTE(ins) \
    word arg = loadWordArg(); \
    printf(#ins " $%.4X\n", arg);

#define ABSOLUTE_X(ins) \
    word arg = loadWordArg(); \
    printf(#ins " $%.4X, X\n", arg);

#define ABSOLUTE_Y(ins) \
    word arg = loadWordArg(); \
    printf(#ins " $%.4X, Y\n", arg);

#define INDIRECT_X(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " ($%.2X, X)\n", arg);

#define INDIRECT_Y(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " ($%.2X), Y\n", arg);

word getIndirectIndexedAddress(byte arg) {
    byte addr_low = cpu.mem[arg] + cpu.y;
    byte carry = addr_low < cpu.y ? 1 : 0;
    byte addr_high = cpu.mem[arg + 1] + carry;
    return ((word)addr_high << 8) | (word)addr_low;
}

word getIndexedIndirectAddress(byte arg) {
    byte addr_low = cpu.mem[arg + cpu.x];
    byte addr_high = cpu.mem[arg + cpu.x + 1];
    return ((word)addr_high << 8) | (word)addr_low;
}

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

void LSR_Acc() {
    ACCUMULATOR(LSR);
    cpu.carry = cpu.acc & 1;
    cpu.acc = cpu.acc >> 1;
    cpu.program_counter += 1;
    checkState();
}

void LSR_Zero() {
    ZERO_PAGE(LSR);
    cpu.carry = cpu.mem[arg] & 1;
    cpu.acc = cpu.mem[arg] >> 1;
    cpu.program_counter += 2;
    checkState();
}

void LSR_Zero_X() {
    ZERO_PAGE_X(LSR);
    cpu.carry = cpu.mem[arg + cpu.x] & 1;
    cpu.acc = cpu.mem[arg + cpu.x] >> 1;
    cpu.program_counter += 2;
    checkState();
}

void LSR_Abs() {
    ABSOLUTE(LSR);
    cpu.carry = cpu.mem[arg] & 1;
    cpu.acc = cpu.mem[arg] >> 1;
    cpu.program_counter += 3;
    checkState();
}

void LSR_Abs_X() {
    ABSOLUTE_X(LSR);
    cpu.carry = cpu.mem[arg + cpu.x] & 1;
    cpu.acc = cpu.mem[arg + cpu.x] >> 1;
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
    [0X99] = &STA_Abs_Y,
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
    [0XBC] = &LDY_Abs_X,

    [0X4A] = &LSR_Acc,
    [0X46] = &LSR_Zero,
    [0X56] = &LSR_Zero_X,
    [0X4E] = &LSR_Abs,
    [0X5E] = &LSR_Abs_X
};
