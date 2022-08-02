#ifndef PROGRAM_LOADER_H
#define PROGRAM_LOADER_H

#include "utils.h"

#define CHUNK_SIZE 1024

byte* loadProgram(char file_name[], int* size);

#endif // PROGRAM_LOADER_H
