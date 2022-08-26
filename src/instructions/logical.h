#include "_common.h"

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

// EOR

void EOR_Imediate() {
    IMEDIATE(EOR);
    cpu.acc |= arg;
    cpu.program_counter += 2;
}

void EOR_Zero() {
    ZERO_PAGE(EOR);
    cpu.acc |= cpu.mem[arg];
    cpu.program_counter += 2;
}

void EOR_Zero_X() {
    ZERO_PAGE_X(EOR);
    cpu.acc |= cpu.mem[arg + cpu.x];
    cpu.program_counter += 2;
}

void EOR_Abs() {
    ABSOLUTE(EOR);
    cpu.acc |= cpu.mem[arg];
    cpu.program_counter += 3;
}

void EOR_Abs_X() {
    ABSOLUTE_X(EOR);
    cpu.acc |= cpu.mem[arg + cpu.x];
    cpu.program_counter += 3;
}

void EOR_Abs_Y() {
    ABSOLUTE_Y(EOR);
    cpu.acc |= cpu.mem[arg + cpu.y];
    cpu.program_counter += 3;
}

void EOR_Ind_X() {
    INDIRECT_X(EOR);
    cpu.acc |= cpu.mem[getIndexedIndirectAddress(arg)];
    cpu.program_counter += 2;
}

void EOR_Ind_Y() {
    INDIRECT_Y(EOR);
    cpu.acc |= cpu.mem[getIndirectIndexedAddress(arg)];
    cpu.program_counter += 2;
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
