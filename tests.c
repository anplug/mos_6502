#include "cpu.h"

extern struct CPU cpu;

void is_eql(const char* str, word res, word expected) {
    char spec_result[32];
    if (res == expected) {
        sprintf(spec_result, "Success");
    } else {
        sprintf(spec_result, "Fail (%.4X != %.4X)", res, expected);
    }
    printf("%s => %s\n", str, spec_result);
}

int main(int argc, char argv[]) {
    init(4 * 1024);

    setOpByteArg(0XA9, 0X26);
    tick();
    is_eql("LDA_Imediate sets value to Acc", cpu.acc, 0X26);

    reset();
    setOpByteArg(0XA5, 0X02);
    setMemByte(0X02, 0X27);
    tick();
    is_eql("LDA_Zero sets value to Acc", cpu.acc, 0X27);

    reset();
    setOpByteArg(0XB5, 0X03);
    setMemByte(0X04, 0X28);
    cpu.x = 1;
    tick();
    is_eql("LDA_Zero_X sets value to Acc", cpu.acc, 0X28);

    reset();
    setOpWordArg(0XAD, 0X02, 0X21);
    setMemByte(0X2102, 0X29);
    tick();
    is_eql("LDA_Abs sets value to Acc", cpu.acc, 0X29);

    reset();
    setOpWordArg(0XBD, 0X02, 0X21);
    setMemByte(0X2103, 0X31);
    cpu.x = 1;
    tick();
    is_eql("LDA_Abs_X sets value to Acc", cpu.acc, 0X31);

    reset();
    setOpWordArg(0XB9, 0X02, 0X21);
    setMemByte(0X2103, 0X32);
    cpu.y = 1;
    tick();
    is_eql("LDA_Abs_Y sets value to Acc", cpu.acc, 0X32);

    reset();
    setOpByteArg(0XA1, 0X01);
    setMemWord(0X02, 0X25, 0XF1);
    setMemByte(0XF125, 0X11);
    cpu.x = 1;
    tick();
    is_eql("LDA_Ind_X sets value to Acc", cpu.acc, 0X11);

    reset();
    setOpByteArg(0XB1, 0X06);
    setMemWord(0X06, 0X88, 0XA5);
    setMemByte(0XA589, 0X13);
    cpu.y = 0X01;
    tick();
    is_eql("LDA_Ind_Y without Carry sets value to Acc", cpu.acc, 0X13);

    reset();
    setOpByteArg(0XB1, 0X01);
    setMemWord(0X01, 0XFD, 0XB9);
    setMemByte(0XBA01, 0X13);
    cpu.y = 4;
    tick();
    is_eql("LDA_Ind_Y with Carry sets value to Acc", cpu.acc, 0X13);

    reset();
    setOp(0X4A);
    cpu.acc = 15;
    tick();
    is_eql("LSR_Acc shifts -> Acc value", cpu.acc, 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    shutdown();
    return 0;
}
