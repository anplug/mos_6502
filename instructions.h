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

#define IS_NEG(val) (val & 128)
#define IS_POS(val) !(val & 128)

byte loadByteArg() {
    return cpu.mem[cpu.program_counter + 1];
}

word loadWordArg() {
    byte arg1 = cpu.mem[cpu.program_counter + 2];
    byte arg2 = cpu.mem[cpu.program_counter + 1];
    return ((word)arg1 << 8) | (word)arg2;
}

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

void checkState() {
    if (cpu.acc == 0) cpu.zero = 1;
    if (cpu.acc & 128) cpu.negative = 1;
}

// ADC

void ADC(byte arg) {
    byte acc_cache = cpu.acc;
    if (cpu.decimal_mode == 0) {
        cpu.acc += arg + cpu.carry;
    } else {
        // TODO: Not implemented yet
    }

    if (cpu.acc <= acc_cache) {
        cpu.carry = 1;
    } else {
        cpu.carry = 0;
    }

    if ((IS_NEG(acc_cache) && IS_NEG(arg) && IS_POS(cpu.acc)) ||
        (IS_POS(acc_cache) && IS_POS(arg) && IS_NEG(cpu.acc))) {
        cpu.overflow = 1;
    } else {
        cpu.overflow = 0;
    }
    checkState();
}

void ADC_Imediate() {
    IMEDIATE(ADC);
    ADC(arg);
    cpu.program_counter += 2;
}

void ADC_Zero() {
    ZERO_PAGE(ADC);
    ADC(cpu.mem[arg]);
    cpu.program_counter += 2;
}

void ADC_Zero_X() {
    ZERO_PAGE_X(ADC);
    ADC(cpu.mem[arg + cpu.x]);
    cpu.program_counter += 2;
}

void ADC_Abs() {
    ABSOLUTE(ADC);
    ADC(cpu.mem[arg]);
    cpu.program_counter += 3;
}

void ADC_Abs_X() {
    ABSOLUTE_X(ADC);
    ADC(cpu.mem[arg + cpu.x]);
    cpu.program_counter += 3;
}

void ADC_Abs_Y() {
    ABSOLUTE_Y(ADC);
    ADC(cpu.mem[arg + cpu.y]);
    cpu.program_counter += 3;
}

void ADC_Ind_X() {
    INDIRECT_X(ADC);
    ADC(cpu.mem[getIndexedIndirectAddress(arg)]);
    cpu.program_counter += 2;
}

void ADC_Ind_Y() {
    INDIRECT_Y(ADC);
    ADC(cpu.mem[getIndirectIndexedAddress(arg)]);
    cpu.program_counter += 2;
}

// AND

void AND_Imediate() {
    IMEDIATE(AND);
    cpu.acc &= arg;
    cpu.program_counter += 2;
}

void AND_Zero() {
    ZERO_PAGE(AND);
    cpu.acc &= cpu.mem[arg];
    cpu.program_counter += 2;
}

void AND_Zero_X() {
    ZERO_PAGE_X(AND);
    cpu.acc &= cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
}

void AND_Abs() {
    ABSOLUTE(AND);
    cpu.acc &= cpu.mem[arg];
    cpu.program_counter += 3;
}

void AND_Abs_X() {
    ABSOLUTE_X(AND);
    cpu.acc &= cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
}

void AND_Abs_Y() {
    ABSOLUTE_Y(AND);
    cpu.acc &= cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
}

void AND_Ind_X() {
    INDIRECT_X(AND);
    cpu.acc &= cpu.mem[getIndexedIndirectAddress(arg)];
    cpu.program_counter += 2;
}

void AND_Ind_Y() {
    INDIRECT_Y(AND);
    cpu.acc &= cpu.mem[getIndirectIndexedAddress(arg)];
    cpu.program_counter += 2;
}

// LDA

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

// LDX

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

// LDY

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

void LDY_Zero_Y() {
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

// ORA

void ORA_Imediate() {
    IMEDIATE(ORA);
    cpu.acc |= arg;
    cpu.program_counter += 2;
}

void ORA_Zero() {
    ZERO_PAGE(ORA);
    cpu.acc |= cpu.mem[arg];
    cpu.program_counter += 2;
}

void ORA_Zero_X() {
    ZERO_PAGE_X(ORA);
    cpu.acc |= cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
}

void ORA_Abs() {
    ABSOLUTE(ORA);
    cpu.acc |= cpu.mem[arg];
    cpu.program_counter += 3;
}

void ORA_Abs_X() {
    ABSOLUTE_X(ORA);
    cpu.acc |= cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
}

void ORA_Abs_Y() {
    ABSOLUTE_Y(ORA);
    cpu.acc |= cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
}

void ORA_Ind_X() {
    INDIRECT_X(ORA);
    cpu.acc |= cpu.mem[getIndexedIndirectAddress(arg)];
    cpu.program_counter += 2;
}

void ORA_Ind_Y() {
    INDIRECT_Y(ORA);
    cpu.acc |= cpu.mem[getIndirectIndexedAddress(arg)];
    cpu.program_counter += 2;
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

// LSR

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
    [0x69] = &ADC_Imediate,
    [0x65] = &ADC_Zero,
    [0x75] = &ADC_Zero_X,
    [0x6D] = &ADC_Abs,
    [0x7D] = &ADC_Abs_X,
    [0x79] = &ADC_Abs_Y,
    [0x61] = &ADC_Ind_X,
    [0x71] = &ADC_Ind_Y,

    [0x29] = &AND_Imediate,
    [0x25] = &AND_Zero,
    [0x35] = &AND_Zero_X,
    [0x2D] = &AND_Abs,
    [0x3D] = &AND_Abs_X,
    [0x39] = &AND_Abs_Y,
    [0x21] = &AND_Ind_X,
    [0x31] = &AND_Ind_Y,

    [0xA9] = &LDA_Imediate,
    [0xA5] = &LDA_Zero,
    [0xB5] = &LDA_Zero_X,
    [0xAD] = &LDA_Abs,
    [0xBD] = &LDA_Abs_X,
    [0xB9] = &LDA_Abs_Y,
    [0xA1] = &LDA_Ind_X,
    [0xB1] = &LDA_Ind_Y,

    [0xA2] = &LDX_Imediate,
    [0xA6] = &LDX_Zero,
    [0xB6] = &LDX_Zero_Y,
    [0xAE] = &LDX_Abs,
    [0xBE] = &LDX_Abs_Y,

    [0xA0] = &LDY_Imediate,
    [0xA4] = &LDY_Zero,
    [0xB4] = &LDY_Zero_Y,
    [0xAC] = &LDY_Abs,
    [0xBC] = &LDY_Abs_X,

    [0x4A] = &LSR_Acc,
    [0x46] = &LSR_Zero,
    [0x56] = &LSR_Zero_X,
    [0x4E] = &LSR_Abs,
    [0x5E] = &LSR_Abs_X,

    [0x09] = &ORA_Imediate,
    [0x05] = &ORA_Zero,
    [0x15] = &ORA_Zero_X,
    [0x0D] = &ORA_Abs,
    [0x1D] = &ORA_Abs_X,
    [0x19] = &ORA_Abs_Y,
    [0x01] = &ORA_Ind_X,
    [0x11] = &ORA_Ind_Y,

    [0x85] = &STA_Zero,
    [0x95] = &STA_Zero_X,
    [0x8D] = &STA_Abs,
    [0x9D] = &STA_Abs_X,
    [0x99] = &STA_Abs_Y,
    [0x81] = &STA_Ind_X,
    [0x91] = &STA_Ind_Y,

    [0x86] = &STX_Zero,
    [0x96] = &STX_Zero_Y,
    [0x8E] = &STX_Abs,

    [0x84] = &STY_Zero,
    [0x94] = &STY_Zero_X,
    [0x8C] = &STY_Abs
};
