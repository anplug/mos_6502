#include "_common.h"

void TAX_Impl() {
    IMPLICIT(TAX);
    cpu.x = cpu.acc;
    cpu.program_counter += 1;
    checkNegZero(&cpu.x);
}

void TAY_Impl() {
    IMPLICIT(TAY);
    cpu.y = cpu.acc;
    cpu.program_counter += 1;
    checkNegZero(&cpu.y);
}

void TXA_Impl() {
    IMPLICIT(TXA);
    cpu.acc = cpu.x;
    cpu.program_counter += 1;
    checkNegZero(&cpu.acc);
}

void TYA_Impl() {
    IMPLICIT(TYA);
    cpu.acc = cpu.y;
    cpu.program_counter += 1;
    checkNegZero(&cpu.acc);
}

void TSX_Impl() {
    IMPLICIT(TSX);
    cpu.x = cpu.stack_ptr;
    cpu.program_counter += 1;
    checkNegZero(&cpu.x);
}

void TXS_Impl() {
    IMPLICIT(TXS);
    cpu.stack_ptr = cpu.x;
    cpu.program_counter += 1;
}
