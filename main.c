#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t byte;
typedef unsigned short word;

typedef struct Cpu {
    byte* mem;
    word mem_size;

    word program_counter;
    byte stack_ptr;
    byte acc;

    byte x;
    byte y;

    byte carry: 1;
    byte zero: 1;
    byte interrupt_disabled: 1;
    byte decimal_mode: 1;
    byte break_command: 1;
    byte nop: 1;
    byte overflow: 1;
    byte negative: 1;

} CPU;

CPU cpu; // Global CPU instance, everything is 0 by default

void init(word mem_size) {
    cpu.mem_size = mem_size;
    cpu.mem = malloc(mem_size + 1);
    memset(cpu.mem, 0, mem_size);
    cpu.program_counter = 0X600;
}

void printState() {
    printf("\
PROGRAM COUNTER\t%.4X\n\
STACK POINTER\t%.2X\n\
ACCUMULATOR\t%.2X\n\
X\t\t%.2X\n\
Y\t\t%.2X\n\
CARRY FLAG\t%d\n\
ZERO FLAG\t%d\n\
INTERRUPT DIS\t%d\n\
DECIMAL MODE\t%d\n\
BREAK COMMAND\t%d\n\
OVERFLOW FLAG\t%d\n\
NEGATIVE FLAG\t%d\n\n",
        cpu.program_counter, cpu.stack_ptr, cpu.acc, cpu.x, cpu.y,
        cpu.carry, cpu.zero, cpu.interrupt_disabled, cpu.decimal_mode,
        cpu.break_command, cpu.overflow, cpu.negative);
}

void printComputerInfo() {
    printf("MOS 6502 (%dKB)\n\n", (cpu.mem_size + 1) / 1024);
}

void shutdown() {
    free(cpu.mem);
}

void setMem(word mem_addr, byte bytes, byte* data) {
    for (word i = 0; i < bytes; i++) {
        cpu.mem[mem_addr + i] = data[i];
    }
}

void memDump(word mem_addr, byte bytes) {
    byte cols = 16;
    printf("MEM DUMP (%dB)\n", bytes);
    for (byte i = 0; i <= (bytes - 1) / cols; ++i) {
        printf("%.4X ", mem_addr + (i * cols));
        for (byte j = 0; j < (i == ((bytes - 1) / cols) ? bytes - (i * cols) : cols); ++j) {
            printf(" %.2X", cpu.mem[mem_addr + (i * cols) + j]);
        }
        printf("\n");
    }
    printf("\n");
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
    byte opcode = cpu.mem[cpu.program_counter];

    //byte bytes = INS_MATRIX[opcode] - 1;
    memDump(cpu.program_counter, 8);

    if (opcode == 0XA9) { // LDA Imediate
        byte arg = loadByteArg();
        printf("\tLDA #$%.2X\n", arg);
        cpu.acc = arg;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XA5) { // LDA Zero Page
        byte arg = loadByteArg();
        printf("\tLDA $%.2X\n", arg);
        byte data = cpu.mem[arg];
        cpu.acc = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XB5) { // LDA Zero Page + X
        byte arg = loadByteArg();
        printf("\tLDA $%.2X\n +X", arg);
        byte data = cpu.mem[arg] + cpu.x;
        cpu.acc = data;
        cpu.program_counter += 2;
        checkState();
    } else
    if (opcode == 0XAD) { // LDA Absolute /LDA $1FA0
        word arg = loadWordArg();
        printf("\tLDA $%.4X\n", arg);
        byte data = cpu.mem[arg];
        cpu.acc = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XBD) { // LDA Absolute + X
        word arg = loadWordArg();
        printf("\tLDA $%.4X\n +X", arg);
        byte data = cpu.mem[arg] + cpu.x;
        cpu.acc = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0XB9) { // LDA Absolute + Y
        word arg = loadWordArg();
        printf("\tLDA $%.4X\n +Y", arg);
        byte data = cpu.mem[arg] + cpu.y;
        cpu.acc = data;
        cpu.program_counter += 3;
        checkState();
    } else
    if (opcode == 0X85) { // STA Zero Page
        byte arg = loadByteArg();
        printf("\tSTA $%.2X\n", arg);
        cpu.mem[arg] = cpu.acc;
        cpu.program_counter += 2;
    } else
    if (opcode == 0X8D) { // STA Absolute
        word arg = loadWordArg();
        printf("\tSTA $%.4X\n", arg);
        cpu.mem[arg] = cpu.acc;
        cpu.program_counter += 3;
    }
    else return;

    printState();
    getchar();
    execute();
}

void run() {
    execute();
}

int main(int argc, char argv[]) {
    init(64 * 1024 - 1);
    printComputerInfo();

    byte initialMem[] = {
        0XA9, 0X01,
        0X8D, 0X00, 0X02,
        0XA9, 0X05,
        0X8D, 0X01, 0X02,
        0XA9, 0X0A,
        0X8D, 0X02, 0X02
    };

    setMem(0X600, 15, initialMem);
    run();

    memDump(0X0200, 32);

    shutdown();
    return 0;
}
