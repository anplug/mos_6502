#include <stdio.h>
#include "program_loader.h"

bool fileAbsent(FILE* file) {
    if (file == NULL) {
        printf("not found\n");
        fclose(file);
        return 1;
    }
    return 0;
}

byte* sanitizeBuffer(byte* buffer) {
    if (buffer == NULL)
    {
        // Probably need to abort everything here
        printf("Something went wrong with reallocating !!!!\n");
    }
    return buffer;
}

byte* loadProgram(char file_name[], int* size) {
    FILE *file = fopen(file_name, "rb");
    *size = 0;

    printf("Loading %s...\n", file_name);

    if (fileAbsent(file)) {
        printf("File loading failed!!!");
        return NULL;
    }

    byte* program = malloc(CHUNK_SIZE);
    byte* realloc_buffer = NULL;
    int bytes_fetched = 0;

    do {
        bytes_fetched = fread(program + (*size), sizeof(byte), CHUNK_SIZE, file);
        printf("%d bytes loaded\n", bytes_fetched);
        *size += CHUNK_SIZE;
        if (bytes_fetched == CHUNK_SIZE) {
            printf("Allocating %d more bytes\n", CHUNK_SIZE);
            program = sanitizeBuffer(realloc(program, *size + CHUNK_SIZE));
        } else {
            int decrease = CHUNK_SIZE - bytes_fetched;
            *size -= decrease;
            printf("Last part, shrinking by %d bytes\n", decrease);
            program = sanitizeBuffer(realloc(program, *size));
        }
    } while(bytes_fetched == CHUNK_SIZE);

    fclose(file);
    return program;
}
