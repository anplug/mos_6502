#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#ifndef CPU_H
#define CPU_H

#define DUMP_COLUMNS 16

typedef void (*inst_ptr_t)();

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
void reset();
void shutdown();
void printState();
void printComputerInfo();
void setMem(word mem_addr, byte bytes, byte* data);
void setMemByte(word mem_addr, byte data);
void setMemWord(word mem_addr, byte data1, byte data2);
void setOp(byte optcode);
void setOpByteArg(byte optcode, byte arg);
void setOpWordArg(byte optcode, byte arg1, byte arg2);
void memDump(word mem_addr, byte bytes);
void execute();
short tick();
bool is_opcode_valid(byte opcode);

#endif // CPU_H
