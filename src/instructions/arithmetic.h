#include "_common.h"

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
    checkNegZero(&cpu.acc);
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

// TODO: DEC
// TODO: DEX
// TODO: DEY
// TODO: INC
// TODO: INX
// TODO: INY
// TODO: SBC
