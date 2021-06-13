#include "cpu.h"
#include "macros.h"

struct CPU cpu; // Global CPU instance, everything is 0 by default

#include "instructions.h"

void init(uint32_t mem_size) {
    cpu.mem_size = mem_size - 1;
    cpu.mem = malloc(mem_size);
    memset(cpu.mem, 0, mem_size);
    cpu.program_counter = 0X600;
    cpu.stack_ptr = 0XFF;
}

void shutdown() {
    free(cpu.mem);
}

void printState() {
    printf("\
| PROG COUNTER\t%.4X\tNV-BDIZC\n\
| STACK POINTER\t%.2X\t%d%d %d%d%d%d%d\n\
| ACCUMULATOR\t%.2X\n\
| X\t\t%.2X\n\
| Y\t\t%.2X\n\n",
        cpu.program_counter, cpu.stack_ptr,
        cpu.negative, cpu.overflow, cpu.break_command, cpu.decimal_mode,
        cpu.interrupt_disabled, cpu.zero, cpu.carry,
        cpu.acc, cpu.x, cpu.y);
}

void printComputerInfo() {
    printf("MOS 6502 (%dKB)\n\n", (cpu.mem_size + 1) / 1024);
}

void setMem(word mem_addr, byte bytes, byte* data) {
    for (word i = 0; i < bytes; i++) {
        cpu.mem[mem_addr + i] = data[i];
    }
}

void memDump(word mem_addr, byte bytes) {
    byte cols = 16;
    printf("| MEM DUMP (%dB)\n", bytes);
    for (byte i = 0; i <= (bytes - 1) / cols; ++i) {
        printf("| %.4X ", mem_addr + (i * cols));
        for (byte j = 0; j < (i == ((bytes - 1) / cols) ? bytes - (i * cols) : cols); ++j) {
            printf(" %.2X", cpu.mem[mem_addr + (i * cols) + j]);
        }
        printf("\n");
    }
}

void checkState() {
    if (cpu.acc == 0) cpu.zero = 1;
    if (cpu.acc & 128) cpu.negative = 1;
}

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
    byte addr_high = cpu.mem[arg] + cpu.y + 1;
    return ((word)addr_high << 8) | (word)addr_low;
}

word getIndexedIndirectAddress(byte arg) {
    byte addr_low = cpu.mem[arg + cpu.x];
    byte addr_high = cpu.mem[arg + cpu.x + 1];
    return ((word)addr_high < 8) | addr_low;
}

void execute() {
    memDump(cpu.program_counter, 8);
    getchar();
    printState();
    if (tick() == 0) {
        execute();
    }
}

// 0 -> executed
// -1 -> opcode invalid
short tick() {
    byte opcode = cpu.mem[cpu.program_counter];
    if (!is_opcode_valid(opcode)) {
        return -1;
    }
    inst_ptr_t instruction = inst_matrix[opcode];
    instruction();

    return 0;
}

bool is_opcode_valid(byte opcode) {
    return inst_matrix[opcode] != 0;
}
