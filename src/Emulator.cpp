#include <cstring>
#include <iostream>


#include "Emulator.h"
#include "FileLoader.h"
template<typename T1,typename T2>
constexpr T1 min(T1 a,T2 b){
    return (a<b?a:b);
}

void Emulator::runCycle(){
    if(DT)DT--;
    if(ST){
        doSound();
        ST--;
    }
}

void Emulator::resetRegisters(unsigned short program_counter){
    memset(V,0,sizeof(V));
    memset(stack,0,sizeof(stack));
    SP=0;
    PC=program_counter;
    DT=0;
    ST=0;
    I=0;
}

void Emulator::resetRAM(){
    memset(RAM,0,sizeof(RAM));
}

void Emulator::loadProgramFile(std::string file,unsigned short starting_position){
    Program program=FileLoader::load(file,4096-starting_position);
    loadProgram(program,starting_position);
    delete program.data;
}

void Emulator::loadProgram(Program program,unsigned short starting_position){
    memcpy(RAM+starting_position,program.data,min(program.length,4096-starting_position));
    resetRegisters(starting_position);
}

RawInstruction Emulator::readInstruction(){
    unsigned char byte=RAM[PC++];
    return {byte,RAM[PC++]};
}

void Emulator::doSound(){
    std::cout<<"Beep!";
    //TODO
}
