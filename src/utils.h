#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef char bool;

unsigned int bytesToKB(unsigned int bytes);
void printHex(byte* data, unsigned int count);

#endif // UTILS_H
