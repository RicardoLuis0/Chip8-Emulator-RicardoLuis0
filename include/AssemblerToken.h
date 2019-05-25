#ifndef ASSEMBLERTOKEN_H
#define ASSEMBLERTOKEN_H

#include <cstdint>

enum AssemblerTokenType_t{
    INSTRUCTIONS_START,
        SYS,
        CLS,
        RET,
        JMP,
        CALL,
        SE,
        SNE,
        SKP,
        SNKP,
        KEY,
        MOV,
        ADD,
        SUB,
        RSB,
        OR,
        AND,
        XOR,
        SHR,
        SHL,
        RND,
        DRW,
        LDFNT,
        BCD,
        STR,
        LDR,
    INSTRUCTIONS_END,
    REGISTERS_START,
        V0,
        V1,
        V2,
        V3,
        V4,
        V5,
        V6,
        V7,
        V8,
        V9,
        VA,
        VB,
        VC,
        VD,
        VE,
        VF,
    REGISTERS_END,
    LITERAL,
};

struct AssemblerToken {
    AssemblerToken(AssemblerTokenType_t tok);
    AssemblerToken(unsigned long val);
    AssemblerTokenType_t type;
    unsigned long val;
};

#endif // ASSEMBLERTOKEN_H
