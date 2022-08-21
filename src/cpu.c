#include "cpu.h"

struct CPU cpu; // Global CPU instance, everything is 0 by default

#include "instructions.h"

void init(uint32_t mem_size) {
    cpu.mem_size = mem_size - 1;
    cpu.mem = malloc(mem_size);
    memset(cpu.mem, 0, mem_size + 1);
    cpu.program_counter = 0x600;
    cpu.stack_ptr = 0xFF;
}

void reset() {
    shutdown();
    init(cpu.mem_size + 1);
}

void shutdown() {
    free(cpu.mem);

    cpu.program_counter = 0;
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
    printf("MOS 6502 (%dKB)\n\n", bytesToKB(cpu.mem_size));
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

void setStatusRegister(byte val) {
    cpu.carry = val & 1;
    cpu.zero = (val >> 1) & 1;
    cpu.interrupt_disabled = (val >> 2) & 1;
    cpu.decimal_mode = (val >> 3) & 1;
    cpu.break_command = (val >> 4) & 1;
    cpu.overflow = (val >> 6) & 1;
    cpu.negative = (val >> 7) & 1;
}

byte statusRegister() {
    return (cpu.negative << 7) + (cpu.overflow << 6) + (cpu.break_command << 4) +
    (cpu.decimal_mode << 3) + (cpu.interrupt_disabled << 2) + (cpu.zero << 1) + cpu.carry;
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

void execute() {
    memDump(cpu.program_counter, 8);
    getchar(); // Temporarily, to step through program by pressing keys
    printState();
    if (tick() == 0) {
        execute();
    }
}

short tick() {
    byte opcode = cpu.mem[cpu.program_counter];
    if (!is_opcode_valid(opcode)) {
        printf("Invalid opcode, abort processing!!!");
        return -1;
    }
    inst_ptr_t instruction = inst_matrix[opcode];
    instruction();

    return 0;
}

bool is_opcode_valid(byte opcode) {
    return inst_matrix[opcode] != 0;
}
