#include <stdint.h>

#ifndef INSTURCTIONS_H
#define INSTURCTIONS_H

typedef uint8_t byte;
typedef unsigned short word;

void initInsMatrix();
void getInsRules(byte opcode, byte *bytes, byte *addressing_mode, byte *target);

#endif
