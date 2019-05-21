#ifndef RAWINSTRUCTION_H
#define RAWINSTRUCTION_H


union RawInstruction {
    RawInstruction(unsigned char byte0,unsigned char byte1);
    unsigned short whole;
    unsigned char bytes[2];
    struct{
        unsigned char section1:4;
        unsigned char section2:4;
        unsigned char section3:4;
        unsigned char section4:4;
    };
};

#endif // RAWINSTRUCTION_H
