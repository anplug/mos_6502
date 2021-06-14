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

void reset() {
    shutdown();
    init(cpu.mem_size + 1);
}

void shutdown() {
    free(cpu.mem);

    cpu.program_counter = 0;;
    cpu.stack_ptr = 0;
    cpu.acc = 0;
    cpu.x = 0;
    cpu.y = 0;
    cpu.negative = 0;
    cpu.overflow = 0;
    cpu.break_command = 0;
    cpu.decimal_mode = 0;
    cpu.interrupt_disabled = 0;
    cpu.zero = 0;
    cpu.carry = 0;
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

void setMemByte(word mem_addr, byte data) {
    cpu.mem[mem_addr] = data;
}

void setMemWord(word mem_addr, byte data1, byte data2) {
    cpu.mem[mem_addr] = data1;
    cpu.mem[mem_addr + 1] = data2;
}

void setOp(byte opcode) {
    cpu.mem[cpu.program_counter] = opcode;
}

void setOpByteArg(byte opcode, byte arg) {
    cpu.mem[cpu.program_counter] = opcode;
    cpu.mem[cpu.program_counter + 1] = arg;
}

void setOpWordArg(byte opcode, byte arg1, byte arg2) {
    cpu.mem[cpu.program_counter] = opcode;
    cpu.mem[cpu.program_counter + 1] = arg1;
    cpu.mem[cpu.program_counter + 2] = arg2;
}

void memDump(word mem_addr, byte bytes) {
    printf("| MEM DUMP (%dB)\n", bytes);
    for (byte i = 0; i <= (bytes - 1) / DUMP_COLUMNS; ++i) {
        printf("| %.4X ", mem_addr + (i * DUMP_COLUMNS));
        for (byte j = 0; j < (i == ((bytes - 1) / DUMP_COLUMNS) ? bytes - (i * DUMP_COLUMNS) : DUMP_COLUMNS); ++j) {
            printf(" %.2X", cpu.mem[mem_addr + (i * DUMP_COLUMNS) + j]);
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

void execute() {
    memDump(cpu.program_counter, 8);
    getchar();
    printState();
    if (tick() == 0) {
        execute();
    }
}

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
