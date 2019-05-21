#ifndef PROGRAM_H
#define PROGRAM_H


struct Program {
        Program(unsigned short length,unsigned char * data);
        unsigned short length;
        unsigned char * data;
};

#endif // PROGRAM_H
