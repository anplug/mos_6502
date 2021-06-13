#include "cpu.h"

extern struct CPU cpu;

void is_eql(const char* str, word res, word expected) {
    char* spec_result = res == expected ? "Success" : "Fail";
    printf("%s => %s\n", str, spec_result);
}

int main(int argc, char argv[]) {
    init(4 * 1024);

    byte memLDA[] = { 0XA9, 0X26 };
    setMem(0X600, 2, memLDA);
    tick();
    is_eql("LDA Imediate sets value to cpu.acc", cpu.acc, 0X26);

    reset();
    byte memLSR[] = { 0X4A };
    setMem(0X600, 1, memLSR);
    cpu.acc = 15;
    tick();
    is_eql("LSR A has shifted value", cpu.acc, 7);
    is_eql("LSR A sets carry flag to 1", cpu.carry, 1);

    shutdown();
    return 0;
}
