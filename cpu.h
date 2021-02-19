#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CPU_H
#define CPU_H

typedef uint8_t byte;
typedef unsigned short word;

struct CPU {
    byte* mem;
    word mem_size;

    word program_counter;
    byte stack_ptr;
    byte acc;

    byte x;
    byte y;

    byte negative: 1;
    byte overflow: 1;
    byte nop: 1;
    byte break_command: 1;
    byte decimal_mode: 1;
    byte interrupt_disabled: 1;
    byte zero: 1;
    byte carry: 1;
};

void init(uint32_t mem_size);
void shutdown();
void printState();
void printComputerInfo();
void setMem(word mem_addr, byte bytes, byte* data);
void memDump(word mem_addr, byte bytes);
void checkState();
byte loadByteArg();
word loadWordArg();
word getIndirectIndexedAddress(byte arg);
word getIndexedIndirectAddress(byte arg);
void execute();
short tick();

#endif // CPU_H
