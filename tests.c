#include "cpu.h"

extern struct CPU cpu;

void is_eql(const char* str, word res, word expected) {
    char spec_result[32];
    bool is_failed = 0;
    if (res == expected) {
        sprintf(spec_result, "Success");
    } else {
        is_failed = 1;
        sprintf(spec_result, "Fail (%.4X != %.4X)", res, expected);
    }
    printf("%s => ", str);
    if (is_failed) {
        printf("\033[0;31m"); // Red
    } else {
        printf("\033[0;32m"); // Green
    }
    printf("%s\n", spec_result);
    printf("\033[0m"); // Back to default
}

int main(int argc, char argv[]) {
    init(4 * 1024);

    // ADC

    setOpByteArg(0X69, 14);
    cpu.acc = 15;
    tick();
    is_eql("ADC_Imediate add values without carry", cpu.acc, 29);
    is_eql("overflow == 0", cpu.overflow, 0);
    is_eql("carry == 0", cpu.carry, 0);

    reset();
    setOpByteArg(0X69, 14);
    cpu.acc = 15;
    cpu.carry = 1;
    tick();
    is_eql("ADC_Imediate add values with carry", cpu.acc, 30);
    is_eql("overflow == 0", cpu.overflow, 0);
    is_eql("carry == 0", cpu.carry, 0);

    reset();
    setOpByteArg(0X69, 0XFF);
    cpu.acc = 2;
    cpu.carry = 1;
    tick();
    is_eql("ADC_Imediate add values with carry and overflows register", cpu.acc, 2);
    is_eql("overflow == 0", cpu.overflow, 0);
    is_eql("carry == 1", cpu.carry, 1);

    reset();
    setOpByteArg(0X69, 127);
    cpu.acc = 25;
    tick();
    is_eql("ADC_Imediate add 2 positive values without carry and changes sign", cpu.acc, 152);
    is_eql("overflow == 1", cpu.overflow, 1);
    is_eql("carry == 0", cpu.carry, 0);
    is_eql("negative == 1", cpu.negative, 1);

    reset();
    setOpByteArg(0X69, -128);
    cpu.acc = -2;
    tick();
    is_eql("ADC_Imediate add 2 negative values without carry and changes sign", cpu.acc, 126); // -128
    is_eql("negative == 0", cpu.negative, 0);
    is_eql("overflow == 1", cpu.overflow, 1);
    is_eql("carry == 1", cpu.carry, 1);

    reset();
    setOpByteArg(0X65, 0X0F);
    setMemByte(0X0F, 25);
    cpu.acc = 15;
    tick();
    is_eql("ADC_Zero add values without carry", cpu.acc, 40);

    reset();
    setOpByteArg(0X75, 0X0A);
    setMemByte(0X0C, 26);
    cpu.acc = 15;
    cpu.x = 2;
    tick();
    is_eql("ADC_Zero_X add values without carry", cpu.acc, 41);

    reset();
    setOpWordArg(0X6D, 0X2A, 0X01);
    setMemByte(0X012A, 27);
    cpu.acc = 15;
    tick();
    is_eql("ADC_Abs add values without carry", cpu.acc, 42);

    reset();
    setOpWordArg(0X7D, 0X2A, 0X01);
    setMemByte(0X012D, 30);
    cpu.acc = 15;
    cpu.x = 3;
    tick();
    is_eql("ADC_Abs_X add values without carry", cpu.acc, 45);

    reset();
    setOpWordArg(0X79, 0X14, 0X01);
    setMemByte(0X0117, 31);
    cpu.acc = 15;
    cpu.y = 3;
    tick();
    is_eql("ADC_Abs_Y add values without carry", cpu.acc, 46);

    reset();
    setOpByteArg(0X61, 0X01);
    setMemWord(0X03, 0XC1, 0X06);
    setMemByte(0X06C1, 14);
    cpu.acc = 15;
    cpu.x = 2;
    tick();
    is_eql("ADC_Ind_X add values without carry", cpu.acc, 29);

    reset();
    setOpByteArg(0X71, 0X02);
    setMemWord(0X02, 0XC1, 0X06);
    setMemByte(0X06C5, 18);
    cpu.acc = 15;
    cpu.y = 4;
    tick();
    is_eql("ADC_Ind_Y add values without carry", cpu.acc, 33);

    // LDA

    reset();
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
    is_eql("LDX_Zero_Y sets value to X", cpu.x, 0X28);

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

    // LDY

    reset();
    setOpByteArg(0XA0, 0X26);
    tick();
    is_eql("LDY_Imediate sets value to Y", cpu.y, 0X26);

    reset();
    setOpByteArg(0XA4, 0X02);
    setMemByte(0X02, 0X27);
    tick();
    is_eql("LDY_Zero sets value to Y", cpu.y, 0X27);

    reset();
    setOpByteArg(0XB4, 0X03);
    setMemByte(0X04, 0X28);
    cpu.x = 1;
    tick();
    is_eql("LDY_Zero_X sets value to Y", cpu.y, 0X28);

    reset();
    setOpWordArg(0XAC, 0X02, 0X08);
    setMemByte(0X0802, 0X29);
    tick();
    is_eql("LDY_Abs sets value to Y", cpu.y, 0X29);

    reset();
    setOpWordArg(0XBC, 0X02, 0X0F);
    setMemByte(0X0F03, 0X32);
    cpu.x = 1;
    tick();
    is_eql("LDY_Abs_X sets value to Y", cpu.y, 0X32);

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

    // STX

    reset();
    setOpByteArg(0X86, 0X02);
    cpu.x = 0X21;
    tick();
    is_eql("STX_Zero sets X value to mem addr", cpu.mem[0X02], 0X21);

    reset();
    setOpByteArg(0X96, 0X03);
    cpu.x = 0X22;
    cpu.y = 1;
    tick();
    is_eql("STX_Zero_Y sets X value to mem addr", cpu.mem[0X04], 0X22);

    reset();
    setOpWordArg(0X8E, 0X02, 0X0C);
    cpu.x = 0X23;
    tick();
    is_eql("STX_Abs sets X value to mem addr", cpu.mem[0X0C02], 0X23);

    // STY

    reset();
    setOpByteArg(0X84, 0X02);
    cpu.y = 0X21;
    tick();
    is_eql("STY_Zero sets Y value to mem addr", cpu.mem[0X02], 0X21);

    reset();
    setOpByteArg(0X94, 0X03);
    cpu.y = 0X22;
    cpu.x = 1;
    tick();
    is_eql("STY_Zero_X sets Y value to mem addr", cpu.mem[0X04], 0X22);

    reset();
    setOpWordArg(0X8C, 0X02, 0X0C);
    cpu.y = 0X23;
    tick();
    is_eql("STY_Abs sets Y value to mem addr", cpu.mem[0X0C02], 0X23);

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
