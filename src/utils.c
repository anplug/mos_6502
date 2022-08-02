#include <stdio.h>
#include "utils.h"

unsigned int bytesToKB(unsigned int bytes) {
    return (bytes + 1) / 1024;
}

void printHex(byte* data, unsigned int count) {
    for (int i = 0; i < count; ++i) {
        printf("%.2X ", data[i]);
    }
    printf("\n");
}
