#include "../cpu.h"

#ifndef COMMON_H
#define COMMON_H

extern struct CPU cpu;

#define ACCUMULATOR(ins) \
    printf(#ins " A\n");

#define IMPLICIT(ins) \
    printf(#ins);

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

void checkNegZero(byte* operand_ptr) {
    if (*operand_ptr == 0) cpu.zero = 1;
    if (*operand_ptr & 128) cpu.negative = 1;
}

#endif // COMMON_H
