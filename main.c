#include "cpu.h"

int main(int argc, char argv[]) {
    init(64 * 1024);
    printComputerInfo();

    //byte initialMem[] = {
    //    0XA9, 0X01,
    //    0X8D, 0X00, 0X02,
    //    0XA9, 0X05,
    //    0X8D, 0X01, 0X02,
    //    0XA9, 0X0A,
    //    0X8D, 0X02, 0X02
    //};

    byte mem[] = {
        0XA9, 0X26,
        0X85, 0X03,
        0XA9, 0X25,
        0X85, 0X02,
        0XA9, 0X24,
        0X85, 0X01,

        0XA9, 0X23,
        0X85, 0X00,
        0XA9, 0X00,
        0XA2, 0X02,
        0XB5, 0X00
    };

    setMem(0X600, 22, mem); // Virtual ROM loading
    execute();

    memDump(0X0000, 32);

    shutdown();
    return 0;
}
