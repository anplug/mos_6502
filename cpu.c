#include "cpu.h"
#include "macros.h"

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
    if (opcode == 0XA9) {
        IMEDIATE(LDA);
        cpu.acc = arg;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XA5) {
        ZERO_PAGE(LDA);
        cpu.acc = cpu.mem[arg];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB5) {
        ZERO_PAGE_X(LDA);
        cpu.acc = cpu.mem[arg + cpu.x];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XAD) {
        ABSOLUTE(LDA);
        cpu.acc = cpu.mem[arg];
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XBD) {
        ABSOLUTE_X(LDA);
        cpu.acc = cpu.mem[arg + cpu.x];
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XB9) {
        ABSOLUTE_Y(LDA);
        cpu.acc = cpu.mem[arg + cpu.y];
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XA1) {
        INDIRECT_X(LDA);
        cpu.acc = cpu.mem[getIndexedIndirectAddress(arg)];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB1) {
        INDIRECT_Y(LDA);
        cpu.acc = cpu.mem[getIndirectIndexedAddress(arg)];
        cpu.program_counter += 2;
        checkState();
    } else
    // STA
    if (opcode == 0X85) {
        ZERO_PAGE(STA);
        cpu.mem[arg] = cpu.acc;
        cpu.program_counter += 2;
    } else
    if (opcode == 0X95) {
        ZERO_PAGE_X(STA);
        cpu.mem[arg + cpu.x] = cpu.acc;
        cpu.program_counter += 2;
    } else
    if (opcode == 0X8D) {
        ABSOLUTE(STA);
        cpu.mem[arg] = cpu.acc;
        cpu.program_counter += 3;
    } else
    if (opcode == 0X9D) {
        ABSOLUTE_X(STA);
        cpu.mem[arg + cpu.x] = cpu.acc;
        cpu.program_counter += 3;
    } else
    if (opcode == 0X99) {
        ABSOLUTE_Y(STA);
        cpu.mem[arg + cpu.y] = cpu.acc;
        cpu.program_counter += 3;
    } else
    if (opcode == 0X81) {
        INDIRECT_X(STA);
        cpu.mem[getIndexedIndirectAddress(arg)] = cpu.acc;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0X91) {
        INDIRECT_Y(STA);
        cpu.mem[getIndirectIndexedAddress(arg)] = cpu.acc;
        cpu.program_counter += 2;
        checkState();
    } else
    // LDX
    if (opcode == 0XA2) {
        IMEDIATE(LDX);
        cpu.x = arg;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XA6) {
        ZERO_PAGE(LDX);
        cpu.x = cpu.mem[arg];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB6) {
        ZERO_PAGE_Y(LDX);
        cpu.x = cpu.mem[arg + cpu.y];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XAE) {
        ABSOLUTE(LDX);
        cpu.x = cpu.mem[arg];
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XBE) {
        ABSOLUTE_Y(LDX);
        cpu.x = cpu.mem[arg + cpu.y];
        cpu.program_counter += 3;
        checkState();
    } else
    // LDY
    if (opcode == 0XA0) {
        IMEDIATE(LDY);
        cpu.y = arg;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XA4) {
        ZERO_PAGE(LDY);
        cpu.y = cpu.mem[arg];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB4) {
        ZERO_PAGE_X(LDY);
        cpu.y = cpu.mem[arg + cpu.x];
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XAC) {
        ABSOLUTE(LDY);
        cpu.y = cpu.mem[arg];
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XBC) {
        ABSOLUTE_X(LDY);
        cpu.y = cpu.mem[arg + cpu.x];
        cpu.program_counter += 3;
        checkState();
    }
    else return -1;

    return 0;
}
