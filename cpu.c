#include "cpu.h"

struct CPU cpu; // Global CPU instance, everything is 0 by default

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
    if (tick() == 0) {
        printState();
        execute();
    }
}

// 0 -> executed
// -1 -> no opcode
short tick() {
    byte opcode = cpu.mem[cpu.program_counter];

    // LDA
    if (opcode == 0XA9) { // LDA Imediate
        byte arg = loadByteArg();
        printf("LDA #$%.2X\n", arg);
        cpu.acc = arg;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XA5) { // LDA Zero Page
        byte arg = loadByteArg();
        printf("LDA $%.2X\n", arg);
        byte data = cpu.mem[arg];
        cpu.acc = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB5) { // LDA Zero Page + X
        byte arg = loadByteArg();
        printf("LDA $%.2X, X\n", arg);
        byte data = cpu.mem[arg + cpu.x];
        cpu.acc = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XAD) { // LDA Absolute
        word arg = loadWordArg();
        printf("LDA $%.4X\n", arg);
        byte data = cpu.mem[arg];
        cpu.acc = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XBD) { // LDA Absolute + X
        word arg = loadWordArg();
        printf("LDA $%.4X, X\n", arg);
        byte data = cpu.mem[arg + cpu.x];
        cpu.acc = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XB9) { // LDA Absolute + Y
        word arg = loadWordArg();
        printf("LDA $%.4X, Y\n", arg);
        byte data = cpu.mem[arg + cpu.y];
        cpu.acc = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XA1) { // LDA (Indirect, X) (Indexed Indirect)
        byte arg = loadByteArg();
        printf("LDA ($%.2X, X)\n", arg);
        byte data = cpu.mem[getIndexedIndirectAddress(arg)];
        cpu.acc = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB1) { // LDA (Indirect), Y (Indirect Indexed)
        byte arg = loadByteArg();
        printf("LDA ($%.2X), Y\n", arg);
        byte data = cpu.mem[getIndirectIndexedAddress(arg)];
        cpu.acc = data;
        cpu.program_counter += 2;
        checkState();
    } else
    // STA
    if (opcode == 0X85) { // STA Zero Page
        byte arg = loadByteArg();
        printf("STA $%.2X\n", arg);
        cpu.mem[arg] = cpu.acc;
        cpu.program_counter += 2;
    } else
    if (opcode == 0X95) { // STA Zero Page + X
        byte arg = loadByteArg();
        printf("STA $%.2X, X\n", arg);
        cpu.mem[arg + cpu.x] = cpu.acc;
        cpu.program_counter += 2;
    } else
    if (opcode == 0X8D) { // STA Absolute
        word arg = loadWordArg();
        printf("STA $%.4X\n", arg);
        cpu.mem[arg] = cpu.acc;
        cpu.program_counter += 3;
    } else
    if (opcode == 0X9D) { // STA Absolute + X
        word arg = loadWordArg();
        printf("STA $%.4X\n", arg);
        cpu.mem[arg + cpu.x] = cpu.acc;
        cpu.program_counter += 3;
    } else
    if (opcode == 0X99) { // STA Absolute + Y
        word arg = loadWordArg();
        printf("STA $%.4X\n", arg);
        cpu.mem[arg + cpu.y] = cpu.acc;
        cpu.program_counter += 3;
    } else
    if (opcode == 0X81) { // STA (Indirect, X) (Indexed Indirect)
        byte arg = loadByteArg();
        printf("STA ($%.2X, X)\n", arg);
        cpu.acc = cpu.mem[getIndexedIndirectAddress(arg)];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0X91) { // STA (Indirect), Y (Indirect Indexed)
        byte arg = loadByteArg();
        printf("STA ($%.2X), Y\n", arg);
        cpu.acc = cpu.mem[getIndirectIndexedAddress(arg)];
        cpu.program_counter += 2;
        checkState();
    } else
    // LDX
    if (opcode == 0XA2) { // LDX Imediate
        byte arg = loadByteArg();
        printf("LDX #$%.2X\n", arg);
        cpu.x = arg;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XA6) { // LDX Zero Page
        byte arg = loadByteArg();
        printf("LDX $%.2X\n", arg);
        byte data = cpu.mem[arg];
        cpu.x = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB6) { // LDX Zero Page + Y
        byte arg = loadByteArg();
        printf("LDX $%.2X, Y\n", arg);
        byte data = cpu.mem[arg + cpu.y];
        cpu.x = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XAE) { // LDX Absolute
        word arg = loadWordArg();
        printf("LDX $%.4X\n", arg);
        byte data = cpu.mem[arg];
        cpu.x = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XBE) { // LDX Absolute + Y
        word arg = loadWordArg();
        printf("LDX $%.4X, Y\n", arg);
        byte data = cpu.mem[arg + cpu.y];
        cpu.x = data;
        cpu.program_counter += 3;
        checkState();
    }
    else return -1;

    return 0;
}
