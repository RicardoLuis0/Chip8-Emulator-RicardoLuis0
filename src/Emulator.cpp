#include <cstring>
#include <iostream>


#include "Emulator.h"
#include "FileLoader.h"
template<typename T1,typename T2>
constexpr T1 min(T1 a,T2 b){
    return (a<b?a:b);
}

Emulator::Emulator(){
    resetRAM();
}

void Emulator::resetRegisters(unsigned short program_counter){
    memset(stack,0,sizeof(stack));
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
    PC=starting_position;
}
