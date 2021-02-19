#include "cpu.h"

extern struct CPU cpu;

int main(int argc, char argv[]) {
    init(4 * 1024);

    printf("Checking 0XA9 => ");
    byte mem[] = { 0XA9, 0X26 };
    setMem(0X600, 2, mem);
    tick();
    if (cpu.acc == 0X26) {
        printf("Success\n");
    } else {
        printf("Fail\n");
    }

    shutdown();
    return 0;
}
