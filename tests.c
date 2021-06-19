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

    // LDA

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
    setOpWordArg(0XAD, 0X02, 0X08);
    setMemByte(0X0802, 0X29);
    tick();
    is_eql("LDA_Abs sets value to Acc", cpu.acc, 0X29);

    reset();
    setOpWordArg(0XBD, 0X02, 0X0A);
    setMemByte(0X0A03, 0X31);
    cpu.x = 1;
    tick();
    is_eql("LDA_Abs_X sets value to Acc", cpu.acc, 0X31);

    reset();
    setOpWordArg(0XB9, 0X02, 0X0F);
    setMemByte(0X0F03, 0X32);
    cpu.y = 1;
    tick();
    is_eql("LDA_Abs_Y sets value to Acc", cpu.acc, 0X32);

    reset();
    setOpByteArg(0XA1, 0X01);
    setMemWord(0X02, 0XA6, 0X05);
    setMemByte(0X05A6, 0X11);
    cpu.x = 1;
    tick();
    is_eql("LDA_Ind_X sets value to Acc", cpu.acc, 0X11);

    reset();
    setOpByteArg(0XB1, 0X06);
    setMemWord(0X06, 0X88, 0X07);
    setMemByte(0X0789, 0X13);
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

    // STA

    reset();
    setOpByteArg(0X85, 0X02);
    cpu.acc = 0X21;
    tick();
    is_eql("STA_Zero sets Acc value to mem addr", cpu.mem[0X02], 0X21);

    reset();
    setOpByteArg(0X95, 0X03);
    cpu.acc = 0X22;
    cpu.x = 1;
    tick();
    is_eql("STA_Zero_X sets Acc value to mem addr", cpu.mem[0X04], 0X22);

    reset();
    setOpWordArg(0X8D, 0X02, 0X0C);
    cpu.acc = 0X23;
    tick();
    is_eql("STA_Abs sets Acc value to mem addr", cpu.mem[0X0C02], 0X23);

    reset();
    setOpWordArg(0X9D, 0X02, 0X0C);
    cpu.acc = 0X24;
    cpu.x = 1;
    tick();
    is_eql("STA_Abs_X sets Acc value to mem addr", cpu.mem[0X0C03], 0X24);

    reset();
    setOpWordArg(0X99, 0X02, 0X0F);
    cpu.acc = 0X25;
    cpu.y = 2;
    tick();
    is_eql("STA_Abs_Y sets Acc value to mem addr", cpu.mem[0X0F04], 0X25);

    reset();
    setOpByteArg(0X81, 0X01);
    setMemWord(0X02, 0X25, 0X0F);
    cpu.acc = 0XA1;
    cpu.x = 1;
    tick();
    is_eql("STA_Ind_X sets Acc value to mem addr", cpu.mem[0X0F25], 0XA1);

    reset();
    setOpByteArg(0X91, 0X01);
    setMemWord(0X01, 0X88, 0X07);
    cpu.acc = 0XA3;
    cpu.y = 5;
    tick();
    is_eql("STA_Ind_Y without Carry sets Acc value to mem addr", cpu.mem[0X078D], 0XA3);

    reset();
    setOpByteArg(0X91, 0X01);
    setMemWord(0X01, 0XFE, 0X01);
    cpu.acc = 0XA4;
    cpu.y = 3;
    tick();
    is_eql("STA_Ind_Y with Carry sets Acc value to mem addr", cpu.mem[0X0201], 0XA4);

    // LDX

    setOpByteArg(0XA2, 0X26);
    tick();
    is_eql("LDX_Imediate sets value to X", cpu.x, 0X26);

    reset();
    setOpByteArg(0XA6, 0X02);
    setMemByte(0X02, 0X27);
    tick();
    is_eql("LDX_Zero sets value to X", cpu.x, 0X27);

    reset();
    setOpByteArg(0XB6, 0X03);
    setMemByte(0X04, 0X28);
    cpu.y = 1;
    tick();
    is_eql("LDA_Zero_Y sets value to X", cpu.x, 0X28);

    reset();
    setOpWordArg(0XAE, 0X02, 0X08);
    setMemByte(0X0802, 0X29);
    tick();
    is_eql("LDX_Abs sets value to X", cpu.x, 0X29);

    reset();
    setOpWordArg(0XBE, 0X02, 0X0F);
    setMemByte(0X0F03, 0X32);
    cpu.y = 1;
    tick();
    is_eql("LDX_Abs_Y sets value to X", cpu.x, 0X32);

    // LSR

    reset();
    setOp(0X4A);
    cpu.acc = 15;
    tick();
    is_eql("LSR_Acc shifts -> Acc value", cpu.acc, 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    shutdown();
    return 0;
}
