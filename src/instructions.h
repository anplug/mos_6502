#include "instructions/arithmetic.h"
#include "instructions/bitwise.h"
#include "instructions/branching.h"
#include "instructions/cmp.h"
#include "instructions/logical.h"
#include "instructions/mem.h"
#include "instructions/register.h"
#include "instructions/stack.h"
#include "instructions/subroutine.h"
#include "instructions/system.h"

inst_ptr_t inst_matrix[256] = {
    // arithmetic.h
    [0x69] = &ADC_Imediate,
    [0x65] = &ADC_Zero,
    [0x75] = &ADC_Zero_X,
    [0x6D] = &ADC_Abs,
    [0x7D] = &ADC_Abs_X,
    [0x79] = &ADC_Abs_Y,
    [0x61] = &ADC_Ind_X,
    [0x71] = &ADC_Ind_Y,

    // logical.h
    [0x29] = &AND_Imediate,
    [0x25] = &AND_Zero,
    [0x35] = &AND_Zero_X,
    [0x2D] = &AND_Abs,
    [0x3D] = &AND_Abs_X,
    [0x39] = &AND_Abs_Y,
    [0x21] = &AND_Ind_X,
    [0x31] = &AND_Ind_Y,

    // bitwise.h
    [0x0A] = &ASL_Acc,
    [0x06] = &ASL_Zero,
    [0x16] = &ASL_Zero_X,
    [0x0E] = &ASL_Abs,
    [0x1E] = &ASL_Abs_X,

    // mem.h
    [0xA9] = &LDA_Imediate,
    [0xA5] = &LDA_Zero,
    [0xB5] = &LDA_Zero_X,
    [0xAD] = &LDA_Abs,
    [0xBD] = &LDA_Abs_X,
    [0xB9] = &LDA_Abs_Y,
    [0xA1] = &LDA_Ind_X,
    [0xB1] = &LDA_Ind_Y,

    // mem.h
    [0xA2] = &LDX_Imediate,
    [0xA6] = &LDX_Zero,
    [0xB6] = &LDX_Zero_Y,
    [0xAE] = &LDX_Abs,
    [0xBE] = &LDX_Abs_Y,

    // mem.h
    [0xA0] = &LDY_Imediate,
    [0xA4] = &LDY_Zero,
    [0xB4] = &LDY_Zero_Y,
    [0xAC] = &LDY_Abs,
    [0xBC] = &LDY_Abs_X,

    // bitwise.h
    [0x4A] = &LSR_Acc,
    [0x46] = &LSR_Zero,
    [0x56] = &LSR_Zero_X,
    [0x4E] = &LSR_Abs,
    [0x5E] = &LSR_Abs_X,

    // logical.h
    [0x09] = &ORA_Imediate,
    [0x05] = &ORA_Zero,
    [0x15] = &ORA_Zero_X,
    [0x0D] = &ORA_Abs,
    [0x1D] = &ORA_Abs_X,
    [0x19] = &ORA_Abs_Y,
    [0x01] = &ORA_Ind_X,
    [0x11] = &ORA_Ind_Y,

    // mem.h
    [0x85] = &STA_Zero,
    [0x95] = &STA_Zero_X,
    [0x8D] = &STA_Abs,
    [0x9D] = &STA_Abs_X,
    [0x99] = &STA_Abs_Y,
    [0x81] = &STA_Ind_X,
    [0x91] = &STA_Ind_Y,

    // mem.h
    [0x86] = &STX_Zero,
    [0x96] = &STX_Zero_Y,
    [0x8E] = &STX_Abs,

    // mem.h
    [0x84] = &STY_Zero,
    [0x94] = &STY_Zero_X,
    [0x8C] = &STY_Abs,

    // register.h
    [0xAA] = &TAX_Impl,
    [0xA8] = &TAY_Impl,
    [0x8A] = &TXA_Impl,
    [0x98] = &TYA_Impl,
    [0xBA] = &TSX_Impl,
    [0x9A] = &TXS_Impl
};
