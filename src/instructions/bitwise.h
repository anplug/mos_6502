#include "_common.h"

// ASL

void ASL(byte* arg) {
    cpu.carry = (*arg & 128) ? 1 : 0;
    *arg <<= 1;
    checkNegZero(arg);
}

void ASL_Acc() {
    ACCUMULATOR(ASL);
    ASL(&cpu.acc);
    cpu.program_counter += 1;
}

void ASL_Zero() {
    ZERO_PAGE(ASL);
    ASL(cpu.mem + arg);
    cpu.program_counter += 2;
}

void ASL_Zero_X() {
    ZERO_PAGE_X(ASL);
    ASL(cpu.mem + arg + cpu.x);
    cpu.program_counter += 2;
}

void ASL_Abs() {
    ABSOLUTE(ASL);
    ASL(cpu.mem + arg);
    cpu.program_counter += 3;
}

void ASL_Abs_X() {
    ABSOLUTE_X(ASL);
    ASL(cpu.mem + arg + cpu.x);
    cpu.program_counter += 3;
}

// LSR

void LSR(byte* arg) {
    cpu.carry = *arg & 1;
    *arg >>= 1;
    checkNegZero(arg);
}

void LSR_Acc() {
    ACCUMULATOR(LSR);
    LSR(&cpu.acc);
    cpu.program_counter += 1;
}

void LSR_Zero() {
    ZERO_PAGE(LSR);
    LSR(cpu.mem + arg);
    cpu.program_counter += 2;
}

void LSR_Zero_X() {
    ZERO_PAGE_X(LSR);
    LSR(cpu.mem + arg + cpu.x);
    cpu.program_counter += 2;
}

void LSR_Abs() {
    ABSOLUTE(LSR);
    LSR(cpu.mem + arg);
    cpu.program_counter += 3;
}

void LSR_Abs_X() {
    ABSOLUTE_X(LSR);
    LSR(cpu.mem + arg + cpu.x);
    cpu.program_counter += 3;
}

// TODO: ROL
// TODO: ROR
