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
        printf("\033[0;31m%s\033[0m\n", spec_result); // Red
    } else {
        printf("\033[0;32m%s\033[0m\n", spec_result); // Green
    }
}

int main(int argc, char** argv) {
    init(4 * 1024);

    // ADC

    setOpByteArg(0x69, 14);
    cpu.acc = 15;
    tick();
    is_eql("ADC_Imediate add values without carry", cpu.acc, 29);
    is_eql("overflow == 0", cpu.overflow, 0);
    is_eql("carry == 0", cpu.carry, 0);

    reset();
    setOpByteArg(0x69, 14);
    cpu.acc = 15;
    cpu.carry = 1;
    tick();
    is_eql("ADC_Imediate add values with carry", cpu.acc, 30);
    is_eql("overflow == 0", cpu.overflow, 0);
    is_eql("carry == 0", cpu.carry, 0);

    reset();
    setOpByteArg(0x69, 0xFF);
    cpu.acc = 2;
    cpu.carry = 1;
    tick();
    is_eql("ADC_Imediate add values with carry and overflows register", cpu.acc, 2);
    is_eql("overflow == 0", cpu.overflow, 0);
    is_eql("carry == 1", cpu.carry, 1);

    reset();
    setOpByteArg(0x69, 127);
    cpu.acc = 25;
    tick();
    is_eql("ADC_Imediate add 2 positive values without carry and changes sign", cpu.acc, 152);
    is_eql("overflow == 1", cpu.overflow, 1);
    is_eql("carry == 0", cpu.carry, 0);
    is_eql("negative == 1", cpu.negative, 1);

    reset();
    setOpByteArg(0x69, -128);
    cpu.acc = -2;
    tick();
    is_eql("ADC_Imediate add 2 negative values without carry and changes sign", cpu.acc, 126); // -128
    is_eql("negative == 0", cpu.negative, 0);
    is_eql("overflow == 1", cpu.overflow, 1);
    is_eql("carry == 1", cpu.carry, 1);

    reset();
    setOpByteArg(0x65, 0x0F);
    setMemByte(0x0F, 25);
    cpu.acc = 15;
    tick();
    is_eql("ADC_Zero add values without carry", cpu.acc, 40);

    reset();
    setOpByteArg(0x75, 0x0A);
    setMemByte(0x0C, 26);
    cpu.acc = 15;
    cpu.x = 2;
    tick();
    is_eql("ADC_Zero_X add values without carry", cpu.acc, 41);

    reset();
    setOpWordArg(0x6D, 0x2A, 0x01);
    setMemByte(0x012A, 27);
    cpu.acc = 15;
    tick();
    is_eql("ADC_Abs add values without carry", cpu.acc, 42);

    reset();
    setOpWordArg(0x7D, 0x2A, 0x01);
    setMemByte(0x012D, 30);
    cpu.acc = 15;
    cpu.x = 3;
    tick();
    is_eql("ADC_Abs_X add values without carry", cpu.acc, 45);

    reset();
    setOpWordArg(0x79, 0x14, 0x01);
    setMemByte(0x0117, 31);
    cpu.acc = 15;
    cpu.y = 3;
    tick();
    is_eql("ADC_Abs_Y add values without carry", cpu.acc, 46);

    reset();
    setOpByteArg(0x61, 0x01);
    setMemWord(0x03, 0xC1, 0x06);
    setMemByte(0x06C1, 14);
    cpu.acc = 15;
    cpu.x = 2;
    tick();
    is_eql("ADC_Ind_X add values without carry", cpu.acc, 29);

    reset();
    setOpByteArg(0x71, 0x02);
    setMemWord(0x02, 0xC1, 0x06);
    setMemByte(0x06C5, 18);
    cpu.acc = 15;
    cpu.y = 4;
    tick();
    is_eql("ADC_Ind_Y add values without carry", cpu.acc, 33);

    // AND

    // 10010011 = 0x93
    // 01110001 = 0x71
    // 00010001 = 0x11

    byte and_arg_1 = 0x93;
    byte and_arg_2 = 0x71;
    byte and_res = 0x11;

    reset();
    setOpByteArg(0x29, and_arg_1);
    cpu.acc = and_arg_2;
    tick();
    is_eql("AND_Imediate acc & val", cpu.acc, and_res);

    reset();
    setOpByteArg(0x25, 0x0A);
    setMemByte(0x0A, and_arg_1);
    cpu.acc = and_arg_2;
    tick();
    is_eql("AND_Zero acc & val", cpu.acc, and_res);

    reset();
    setOpByteArg(0x35, 0x0A);
    setMemByte(0x0C, and_arg_2);
    cpu.acc = and_arg_1;
    cpu.x = 2;
    tick();
    is_eql("AND_Zero_X acc & val", cpu.acc, and_res);

    reset();
    setOpWordArg(0x2D, 0x2A, 0x01);
    setMemByte(0x012A, and_arg_1);
    cpu.acc = and_arg_2;
    tick();
    is_eql("AND_Abs acc & val", cpu.acc, and_res);

    reset();
    setOpWordArg(0x3D, 0x2A, 0x01);
    setMemByte(0x012D, and_arg_1);
    cpu.acc = and_arg_2;
    cpu.x = 3;
    tick();
    is_eql("AND_Abs_X acc & val", cpu.acc, and_res);

    reset();
    setOpWordArg(0x39, 0x14, 0x01);
    setMemByte(0x0117, and_arg_1);
    cpu.acc = and_arg_2;
    cpu.y = 3;
    tick();
    is_eql("AND_Abs_Y acc & val", cpu.acc, and_res);

    reset();
    setOpByteArg(0x21, 0x01);
    setMemWord(0x03, 0xC1, 0x06);
    setMemByte(0x06C1, and_arg_2);
    cpu.acc = and_arg_1;
    cpu.x = 2;
    tick();
    is_eql("AND_Ind_X acc & val", cpu.acc, and_res);

    reset();
    setOpByteArg(0x31, 0x02);
    setMemWord(0x02, 0xC1, 0x06);
    setMemByte(0x06C5, and_arg_1);
    cpu.acc = and_arg_2;
    cpu.y = 4;
    tick();
    is_eql("AND_Ind_Y acc & val", cpu.acc, and_res);

    // ASL

    reset();
    setOp(0x0A);
    cpu.acc = 129; // 1000 0001 << 1 -> 0000 0010
    tick();
    is_eql("ASL_Acc shifts << Acc value", cpu.acc, 2);
    is_eql("and sets carry flag to 1", cpu.carry, 1);
    is_eql("and sets negative flag to 0", cpu.negative, 0);

    reset();
    setOp(0x0A);
    cpu.acc = 65; // 0100 0001 << 1 -> 1000 0010
    tick();
    is_eql("ASL_Acc shifts << Acc value with last bit 0", cpu.acc, 130);
    is_eql("and sets carry flag to 0", cpu.carry, 0);
    is_eql("and sets negative flag to 1", cpu.negative, 1);

    reset();
    setOpByteArg(0x06, 0x05);
    cpu.mem[0x05] = 129;
    tick();
    is_eql("ASL_Zero shifts << Mem value", cpu.mem[0x05], 2);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpByteArg(0x06, 0x05);
    cpu.mem[0x05] = 65; // 0100 0001 << 1 -> 1000 0010
    tick();
    is_eql("ASL_Zero shifts << Mem value with last bit 0", cpu.mem[0x05], 130);
    is_eql("and sets carry flag to 0", cpu.carry, 0);
    is_eql("and sets negative flag to 1", cpu.negative, 1);

    reset();
    setOpByteArg(0x16, 0x05);
    cpu.mem[0x06] = 129;
    cpu.x = 1;
    tick();
    is_eql("ASL_Zero_X shifts << Mem value", cpu.mem[0x06], 2);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpWordArg(0x0E, 0xFA, 0x01);
    cpu.mem[0x01FA] = 129;
    tick();
    is_eql("ASL_Abs shifts << Mem value", cpu.mem[0x01FA], 2);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpWordArg(0x1E, 0xFA, 0x01);
    cpu.mem[0x01FC] = 129;
    cpu.x = 2;
    tick();
    is_eql("ASL_Abs_X shifts -> Mem value", cpu.mem[0x01FC], 2);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    // LDA

    reset();
    setOpByteArg(0xA9, 0x26);
    tick();
    is_eql("LDA_Imediate sets value to Acc", cpu.acc, 0x26);

    reset();
    setOpByteArg(0xA5, 0x02);
    setMemByte(0x02, 0x27);
    tick();
    is_eql("LDA_Zero sets value to Acc", cpu.acc, 0x27);

    reset();
    setOpByteArg(0xB5, 0x03);
    setMemByte(0x04, 0x28);
    cpu.x = 1;
    tick();
    is_eql("LDA_Zero_X sets value to Acc", cpu.acc, 0x28);

    reset();
    setOpWordArg(0xAD, 0x02, 0x08);
    setMemByte(0x0802, 0x29);
    tick();
    is_eql("LDA_Abs sets value to Acc", cpu.acc, 0x29);

    reset();
    setOpWordArg(0xBD, 0x02, 0x0A);
    setMemByte(0x0A03, 0x31);
    cpu.x = 1;
    tick();
    is_eql("LDA_Abs_X sets value to Acc", cpu.acc, 0x31);

    reset();
    setOpWordArg(0xB9, 0x02, 0x0F);
    setMemByte(0x0F03, 0x32);
    cpu.y = 1;
    tick();
    is_eql("LDA_Abs_Y sets value to Acc", cpu.acc, 0x32);

    reset();
    setOpByteArg(0xA1, 0x01);
    setMemWord(0x02, 0xA6, 0x05);
    setMemByte(0x05A6, 0x11);
    cpu.x = 1;
    tick();
    is_eql("LDA_Ind_X sets value to Acc", cpu.acc, 0x11);

    reset();
    setOpByteArg(0xB1, 0x06);
    setMemWord(0x06, 0x88, 0x07);
    setMemByte(0x0789, 0x13);
    cpu.y = 0x01;
    tick();
    is_eql("LDA_Ind_Y without Carry sets value to Acc", cpu.acc, 0x13);

    reset();
    setOpByteArg(0xB1, 0x01);
    setMemWord(0x01, 0xFD, 0xB9);
    setMemByte(0xBA01, 0x13);
    cpu.y = 4;
    tick();
    is_eql("LDA_Ind_Y with Carry sets value to Acc", cpu.acc, 0x13);

    // LDX

    setOpByteArg(0xA2, 0x26);
    tick();
    is_eql("LDX_Imediate sets value to X", cpu.x, 0x26);

    reset();
    setOpByteArg(0xA6, 0x02);
    setMemByte(0x02, 0x27);
    tick();
    is_eql("LDX_Zero sets value to X", cpu.x, 0x27);

    reset();
    setOpByteArg(0xB6, 0x03);
    setMemByte(0x04, 0x28);
    cpu.y = 1;
    tick();
    is_eql("LDX_Zero_Y sets value to X", cpu.x, 0x28);

    reset();
    setOpWordArg(0xAE, 0x02, 0x08);
    setMemByte(0x0802, 0x29);
    tick();
    is_eql("LDX_Abs sets value to X", cpu.x, 0x29);

    reset();
    setOpWordArg(0xBE, 0x02, 0x0F);
    setMemByte(0x0F03, 0x32);
    cpu.y = 1;
    tick();
    is_eql("LDX_Abs_Y sets value to X", cpu.x, 0x32);

    // LDY

    reset();
    setOpByteArg(0xA0, 0x26);
    tick();
    is_eql("LDY_Imediate sets value to Y", cpu.y, 0x26);

    reset();
    setOpByteArg(0xA4, 0x02);
    setMemByte(0x02, 0x27);
    tick();
    is_eql("LDY_Zero sets value to Y", cpu.y, 0x27);

    reset();
    setOpByteArg(0xB4, 0x03);
    setMemByte(0x04, 0x28);
    cpu.x = 1;
    tick();
    is_eql("LDY_Zero_X sets value to Y", cpu.y, 0x28);

    reset();
    setOpWordArg(0xAC, 0x02, 0x08);
    setMemByte(0x0802, 0x29);
    tick();
    is_eql("LDY_Abs sets value to Y", cpu.y, 0x29);

    reset();
    setOpWordArg(0xBC, 0x02, 0x0F);
    setMemByte(0x0F03, 0x32);
    cpu.x = 1;
    tick();
    is_eql("LDY_Abs_X sets value to Y", cpu.y, 0x32);

    // LSR

    reset();
    setOp(0x4A);
    cpu.acc = 15;
    tick();
    is_eql("LSR_Acc shifts >> Acc value", cpu.acc, 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpByteArg(0x46, 0x05);
    cpu.mem[0x05] = 15;
    tick();
    is_eql("LSR_Zero shifts >> Mem value", cpu.mem[0x05], 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpByteArg(0x56, 0x05);
    cpu.mem[0x06] = 15;
    cpu.x = 1;
    tick();
    is_eql("LSR_Zero_X shifts >> Mem value", cpu.mem[0x06], 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpWordArg(0x4E, 0xFA, 0x01);
    cpu.mem[0x01FA] = 15;
    tick();
    is_eql("LSR_Abs shifts >> Mem value", cpu.mem[0x01FA], 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    reset();
    setOpWordArg(0x5E, 0xFA, 0x01);
    cpu.mem[0x01FC] = 15;
    cpu.x = 2;
    tick();
    is_eql("LSR_Abs_X shifts >> Mem value", cpu.mem[0x01FC], 7);
    is_eql("and sets carry flag to 1", cpu.carry, 1);

    // ORA

    // 10000111 = 0x87
    // 01010101 = 0x55
    // 11010111 = 0xD7

    byte ora_arg_1 = 0x87;
    byte ora_arg_2 = 0x55;
    byte ora_res = 0xD7;

    reset();
    setOpByteArg(0x09, ora_arg_1);
    cpu.acc = ora_arg_2;
    tick();
    is_eql("ORA_Imediate acc | val", cpu.acc, ora_res);

    reset();
    setOpByteArg(0x05, 0x0A);
    setMemByte(0x0A, ora_arg_1);
    cpu.acc = ora_arg_2;
    tick();
    is_eql("ORA_Zero acc | val", cpu.acc, ora_res);

    reset();
    setOpByteArg(0x15, 0x0A);
    setMemByte(0x0C, ora_arg_2);
    cpu.acc = ora_arg_1;
    cpu.x = 2;
    tick();
    is_eql("ORA_Zero_X acc | val", cpu.acc, ora_res);

    reset();
    setOpWordArg(0x0D, 0x2A, 0x01);
    setMemByte(0x012A, ora_arg_1);
    cpu.acc = ora_arg_2;
    tick();
    is_eql("ORA_Abs acc | val", cpu.acc, ora_res);

    reset();
    setOpWordArg(0x1D, 0x2A, 0x01);
    setMemByte(0x012D, ora_arg_1);
    cpu.acc = ora_arg_2;
    cpu.x = 3;
    tick();
    is_eql("ORA_Abs_X acc | val", cpu.acc, ora_res);

    reset();
    setOpWordArg(0x19, 0x14, 0x01);
    setMemByte(0x0117, ora_arg_1);
    cpu.acc = ora_arg_2;
    cpu.y = 3;
    tick();
    is_eql("ORA_Abs_Y acc | val", cpu.acc, ora_res);

    reset();
    setOpByteArg(0x01, 0x01);
    setMemWord(0x03, 0xC1, 0x06);
    setMemByte(0x06C1, ora_arg_2);
    cpu.acc = ora_arg_1;
    cpu.x = 2;
    tick();
    is_eql("ORA_Ind_X acc | val", cpu.acc, ora_res);

    reset();
    setOpByteArg(0x11, 0x02);
    setMemWord(0x02, 0xC1, 0x06);
    setMemByte(0x06C5, ora_arg_1);
    cpu.acc = ora_arg_2;
    cpu.y = 4;
    tick();
    is_eql("ORA_Ind_Y acc | val", cpu.acc, ora_res);

    // STA

    reset();
    setOpByteArg(0x85, 0x02);
    cpu.acc = 0x21;
    tick();
    is_eql("STA_Zero sets Acc value to mem addr", cpu.mem[0x02], 0x21);

    reset();
    setOpByteArg(0x95, 0x03);
    cpu.acc = 0x22;
    cpu.x = 1;
    tick();
    is_eql("STA_Zero_X sets Acc value to mem addr", cpu.mem[0x04], 0x22);

    reset();
    setOpWordArg(0x8D, 0x02, 0x0C);
    cpu.acc = 0x23;
    tick();
    is_eql("STA_Abs sets Acc value to mem addr", cpu.mem[0x0C02], 0x23);

    reset();
    setOpWordArg(0x9D, 0x02, 0x0C);
    cpu.acc = 0x24;
    cpu.x = 1;
    tick();
    is_eql("STA_Abs_X sets Acc value to mem addr", cpu.mem[0x0C03], 0x24);

    reset();
    setOpWordArg(0x99, 0x02, 0x0F);
    cpu.acc = 0x25;
    cpu.y = 2;
    tick();
    is_eql("STA_Abs_Y sets Acc value to mem addr", cpu.mem[0x0F04], 0x25);

    reset();
    setOpByteArg(0x81, 0x01);
    setMemWord(0x02, 0x25, 0x0F);
    cpu.acc = 0xA1;
    cpu.x = 1;
    tick();
    is_eql("STA_Ind_X sets Acc value to mem addr", cpu.mem[0x0F25], 0xA1);

    reset();
    setOpByteArg(0x91, 0x01);
    setMemWord(0x01, 0x88, 0x07);
    cpu.acc = 0xA3;
    cpu.y = 5;
    tick();
    is_eql("STA_Ind_Y without Carry sets Acc value to mem addr", cpu.mem[0x078D], 0xA3);

    reset();
    setOpByteArg(0x91, 0x01);
    setMemWord(0x01, 0xFE, 0x01);
    cpu.acc = 0xA4;
    cpu.y = 3;
    tick();
    is_eql("STA_Ind_Y with Carry sets Acc value to mem addr", cpu.mem[0x0201], 0xA4);

    // STX

    reset();
    setOpByteArg(0x86, 0x02);
    cpu.x = 0x21;
    tick();
    is_eql("STX_Zero sets X value to mem addr", cpu.mem[0x02], 0x21);

    reset();
    setOpByteArg(0x96, 0x03);
    cpu.x = 0x22;
    cpu.y = 1;
    tick();
    is_eql("STX_Zero_Y sets X value to mem addr", cpu.mem[0x04], 0x22);

    reset();
    setOpWordArg(0x8E, 0x02, 0x0C);
    cpu.x = 0x23;
    tick();
    is_eql("STX_Abs sets X value to mem addr", cpu.mem[0x0C02], 0x23);

    // STY

    reset();
    setOpByteArg(0x84, 0x02);
    cpu.y = 0x21;
    tick();
    is_eql("STY_Zero sets Y value to mem addr", cpu.mem[0x02], 0x21);

    reset();
    setOpByteArg(0x94, 0x03);
    cpu.y = 0x22;
    cpu.x = 1;
    tick();
    is_eql("STY_Zero_X sets Y value to mem addr", cpu.mem[0x04], 0x22);

    reset();
    setOpWordArg(0x8C, 0x02, 0x0C);
    cpu.y = 0x23;
    tick();
    is_eql("STY_Abs sets Y value to mem addr", cpu.mem[0x0C02], 0x23);

    // Register transafer operations
    //
    //

    reset();
    setOp(0xAA);
    cpu.acc = 0x23;
    tick();
    is_eql("TAX_Impl sets Acc value to X", cpu.x, 0x23);

    reset();
    setOp(0xA8);
    cpu.acc = 0x24;
    tick();
    is_eql("TAY_Impl sets Acc value to Y", cpu.y, 0x24);

    reset();
    setOp(0x8A);
    cpu.x = 0x25;
    tick();
    is_eql("TXA_Impl sets X value to Acc", cpu.acc, 0x25);

    reset();
    setOp(0x98);
    cpu.y = 0x26;
    tick();
    is_eql("TYA_Impl sets Y value to Acc", cpu.acc, 0x26);

    reset();
    setOp(0xBA);
    cpu.stack_ptr = 0x27;
    tick();
    is_eql("TSX_Impl sets stack pointer value to X", cpu.x, 0x27);

    reset();
    setOp(0x9A);
    cpu.x = 0x28;
    tick();
    is_eql("TSX_Impl sets X value to stack pointer", cpu.stack_ptr, 0x28);

    shutdown();
    return 0;
}
