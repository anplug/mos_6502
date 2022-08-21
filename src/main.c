#include "cpu.h"
#include "program_loader.h"

#define DEFAULT_PROGRAM "./samples/default.dsk"

int main(int argc, char* argv[]) {
    init(64 * 1024);
    printComputerInfo();

    char* file_name;

    if (argc == 1) {
        printf("No file specified, fallback to default\n");
        file_name = DEFAULT_PROGRAM;
    }
    else if (argc == 2) {
        file_name  = argv[1];
    }

    int program_size = 0;
    byte* program = loadProgram(file_name, &program_size);

    printf("Program size is %dKB (%dB)\n", bytesToKB(program_size), program_size);
    printHex(program, program_size);

    setMem(0x600, program_size, program); // Virtual ROM loading
    execute();

    memDump(0x0000, 32);

    shutdown();
    return 0;
}
