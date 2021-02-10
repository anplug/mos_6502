#include "instructions.h"

byte INS_MATRIX[255];

void initInsMatrix() {
    INS_MATRIX[0XA9] = 0X2; //10
    //INS_MATRIX[0XA5] = 2;
    //INS_MATRIX[0XB5] = 2;
    //INS_MATRIX[0XAD] = 3;
    //INS_MATRIX[0XBD] = 3;
    //INS_MATRIX[0XB9] = 3;
    //INS_MATRIX[0XA1] = 2;
    //INS_MATRIX[0XB1] = 2;
}

void getInsRules(byte opcode, byte *bytes, byte *addressing_mode, byte *target) {
    byte rules = INS_MATRIX[opcode];
    *bytes = rules >> 6;
    *addressing_mode = rules >> 2 | 0X0F;
    *target = rules | 0X03;
}
