#ifndef RAWINSTRUCTION_H
#define RAWINSTRUCTION_H

#include <cstdint>

union RawInstruction {
    RawInstruction(uint8_t byte0,uint8_t byte1);
    uint16_t whole;
    uint8_t bytes[2];
    struct{
        union{
            uint8_t section34;
        };
        union{
            uint8_t section12;
        };
    };
    struct{
        union{
            struct{
                uint16_t section234:12;
            };
            struct{
                uint8_t section4:4,section3:4,section2:4,section1:4;
            };
        };
    };
};

#endif // RAWINSTRUCTION_H
