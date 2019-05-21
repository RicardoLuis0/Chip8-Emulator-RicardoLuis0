#ifndef RAWINSTRUCTION_H
#define RAWINSTRUCTION_H


union RawInstruction {
    RawInstruction(unsigned char byte0,unsigned char byte1);
    unsigned short whole;
    unsigned char bytes[2];
    struct{
        union{
            unsigned char high_byte;
            unsigned char section34;
        };
        union{
            unsigned char low_byte;
            unsigned char section12;
        };
    };
    struct{
        union{
            struct{
                unsigned short section234:12;
            };
            struct{
                unsigned char section4:4,section3:4,section2:4,section1:4;
            };
        };
    };
};

#endif // RAWINSTRUCTION_H
