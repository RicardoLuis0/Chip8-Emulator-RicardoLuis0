#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>


#include <SDL2/SDL.h>
#include "ArgumentParser.h"
#include "Console.h"
#include "Emulator.h"
#include "FileLoader.h"
#include "splitString.h"
#include "Disassembler.h"

int main(int argc,char ** argv){
    std::cout<<"Chip8 Emulator\nby RicardoLuis0\n\nCreating Console Object...";
    Console con;
    std::cout<<"Done.\nParsing Arguments...";
    Arguments args=ArgumentParser::parse(argc,argv);
    std::string file;
    //read file option
    if(args.hasOption("file")){
        file=args.getOption("file");
        std::cout<<"Done.\n";
    }else{
        std::cout<<"Error\n >Missing required parameter \"-file\"\n";
        std::cout<<"Getting file parameter input from user...\n";
        std::cout<<" >Please Enter file to load:";
        std::getline(std::cin,file);
        con.moveCursor(41,6);
        std::cout<<"Done.";
        con.moveCursor(0,8);
    }
    std::cout<<"Seeding random number generator...";
    srand(time(NULL));
    std::cout<<"Done.\nInitializing SDL2...";
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        std::cout<<"Error.\n >Error while Initializing SDL: "<<SDL_GetError()<<"\n";
        return 0;
    }
    std::cout<<"Done.\n";
    if(args.hasOption("disassemble")){
        std::cout<<"Opening Input File...";
        Program p=FileLoader::load(file,4096-0x200);
        std::vector<disassembled_instruction> asm_vec;
        std::cout<<"Done.\nStarting Disassembly...";
        for(unsigned i=0;i<p.length;){
            uint8_t byte0=p.data[i++];
            if(i<p.length){
                uint8_t byte1=p.data[i++];
                asm_vec.push_back(Disassembler::disassembleInstruction(byte0,byte1));
            }
        }
        std::cout<<"Done.\nOpening Output File...";
        uint16_t location=0x200;
        std::ofstream f(splitString(file,{{'/',false},{'\\',false}}).back()+".c8asm");
        if(!f){
            std::cout<<"Error.\n Could not open file\n";
            return 0;
        }
        std::cout<<"Done.\nWriting to Output File...";
        for(disassembled_instruction asm_ins:asm_vec){
            f<<asm_ins.getDisplay(location);
            location+=2;
        }
        std::cout<<"Done.\n";
    }else if(args.hasOption("debug")){
        std::cout<<"Initializing Debugger...\n";
        Emulator emu;
        con.moveCursor(24,10);
        std::cout<<"Done.";
        con.moveCursor(0,13);
        std::cout<<"Loading ROM...";
        emu.loadProgramFile(file);
        std::cout<<"Done.\nStarting Debugging...\n\n\n";
        emu.initDebug();
    }else{
        std::cout<<"Initializing Emulator...\n";
        Emulator emu;
        con.moveCursor(24,10);
        std::cout<<"Done.";
        con.moveCursor(0,13);
        std::cout<<"Loading ROM...";
        emu.loadProgramFile(file);
        std::cout<<"Done.\nStarting Emulation...\n\n\n";
        while(1){
            try{
                emu.draw();
                emu.runCycle();
            }catch(...){
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Exeption Thrown","An Exeption was Thrown by the Emulator, Aborting execution.",0);
                SDL_Quit();
                throw;
            }
        }
    }
    SDL_Quit();
    return 0;
}
