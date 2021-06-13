#ifndef MACROS_H
#define MACROS_H

#define ACCUMULATOR(ins) \
    printf(#ins " A\n");

#define IMEDIATE(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " #$%.2X\n", arg);

#define ZERO_PAGE(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " $%.2X\n", arg);

#define ZERO_PAGE_X(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " $%.2X, X\n", arg);

#define ZERO_PAGE_Y(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " $%.2X, Y\n", arg);

#define ABSOLUTE(ins) \
    word arg = loadWordArg(); \
    printf(#ins " $%.4X\n", arg);

#define ABSOLUTE_X(ins) \
    word arg = loadWordArg(); \
    printf(#ins " $%.4X, X\n", arg);

#define ABSOLUTE_Y(ins) \
    word arg = loadWordArg(); \
    printf(#ins " $%.4X, Y\n", arg);

#define INDIRECT_X(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " ($%.2X, X)\n", arg);

#define INDIRECT_Y(ins) \
    byte arg = loadByteArg(); \
    printf(#ins " ($%.2X), Y\n", arg);

#endif // MACROS_H
