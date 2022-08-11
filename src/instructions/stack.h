#include "_common.h"

void PHA_Impl() {
    IMPLICIT(PHA);
    cpu.stack_ptr -= 1;
    cpu.mem[0x100 + cpu.stack_ptr] = cpu.acc;
    cpu.program_counter += 1;
}

void PHP_Impl() {
    IMPLICIT(PHP);
    cpu.stack_ptr -= 1;
    cpu.mem[0x100 + cpu.stack_ptr] = statusRegister();
    cpu.program_counter += 1;
}

void PLA_Impl() {
    IMPLICIT(PLA);
    cpu.acc = cpu.mem[0x100 + cpu.stack_ptr];
    cpu.stack_ptr += 1;
    cpu.program_counter += 1;
    checkNegZero(&cpu.acc);
}

void PLP_Impl() {
    IMPLICIT(PLP);
    setStatusRegister(cpu.mem[0x100 + cpu.stack_ptr]);
    cpu.stack_ptr += 1;
    cpu.program_counter += 1;
}
