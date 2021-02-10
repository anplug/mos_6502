### Emulating MOS 6502 in Apple II Computer

http://www.obelisk.me.uk/6502/

* MOS Technology 6502 - 1.022,727 MHz
* 4 KB of RAM (max 48 KB)
* An audio cassette interface for loading programs and storing data
* Integer BASIC programming language built into the ROMs
* The video controller displayed 40 columns by 24 lines of monochrome, upper-case-only (the original character set matches ASCII characters 0x20 to 0x5F) text on the screen, with NTSC composite video output suitable for display on a TV monitor, or on a regular TV set by way of a separate RF modulator.


## Memory

* ($0000-$00FF) - Zero Page
* ($0100-$01FF) - System stack
* ...
* ($FFFA-$FFFB) - non-maskable interrupt handler
* ($FFFC-$FFFD) - power on reset location
* ($FFFE-$FFFF) - BRK/interrupt request handler

## Registers

#### Program Counter (16 bits)
Points to the next instruction to be executed, modified automatically. The value of the program counter can be modified by executing a jump, a relative branch or a subroutine call to another memory address or by returning from a subroutine or interrupt.

#### Stack Pointer (8 bits)
Holds the low 8 bits of the next free location on the stack.

#### Accumulator (8 bits)
Is used in all arithmetic and logical operations (except inc and dec)

### Index Registers (8 bits):
The value of it can be loaded and saved in memory, compared with values held in memory or incremented and decremented.

#### X
Most commonly used to hold counters or offsets for accessing memory.
!It can be used to get a copy of the stack pointer or change its value.

#### Y
Can be used as well to hold counters or offsets for accessing memory.

### Processor Status (8 bits)
####  Carry Flag
If the last operation caused an overflow from bit 7 of the result or an underflow from bit 0.
This condition is set during arithmetic, comparison and during logical shifts.
It can be explicitly set using the 'Set Carry Flag' (SEC) instruction and cleared with 'Clear Carry Flag' (CLC).

#### Zero Flag
The zero flag is set if the result of the last operation as was zero.

#### Interrupt Disable
The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' (SEI) instruction.
While this flag is set the processor will not respond to interrupts from devices until it is cleared by a 'Clear Interrupt Disable' (CLI) instruction.

#### Decimal Mode
While the decimal mode flag is set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction.
The flag can be explicitly set using 'Set Decimal Flag' (SED) and cleared with 'Clear Decimal Flag' (CLD).

#### Break Command
The break command bit is set when a BRK instruction has been executed and an interrupt has been generated to process it.

#### Overflow Flag
The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's complement result (e.g. adding to positive numbers and ending up with a negative result: 64 + 64 => -128). It is determined by looking at the carry between bits 6 and 7 and between bit 7 and the carry flag.

#### Negative Flag
The negative flag is set if the result of the last operation had bit 7 set to a one.

## Instructrion Processing Methods Concepts:

### Encoding (draft)

Encode all instruction rules into single 2 or 4 byte number

`rule = getRuleforOpcode(opcode);`
Rule format `0000 0000`

01 = amount of bytes:
* 01 -> 1
* 10 -> 2
* 11 -> 3

2345 = addressing mode:
* 0000 -> implicit
* 0001 -> accumulator (? same as implicit)
* 0010 -> imediate (8-bit constant)
* 0011 -> zero page
* 0100 -> zero page + X
* 0101 -> zero page + Y
* 0110 -> relative
* 0111 -> absolute
* 1000 -> absolute + X
* 1001 -> absolute + Y
* 1010 -> indirect
* 1011 -> indirect + X
* 1100 -> indirect + Y

67 = target:
* 00 - zero page
* 01 - accumulator
* 10 - memory
