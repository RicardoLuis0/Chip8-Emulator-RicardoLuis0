#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>


#include <SDL2/SDL.h>
#include "ArgumentParser.h"
#include "Emulator.h"
#include "FileLoader.h"
#include "splitString.h"
#include "Disassembler.h"
#include "SDLHandler.h"

#include <curses.h>
#include "QuitException.h"

std::string getline_curs(){
    char c;
    std::string buffer;
    while((c=getch())!='\n')buffer+=c;
    return buffer;
}

int main(int argc,char ** argv){
    initscr();
    printw("Chip8 Emulator\nby RicardoLuis0\n\nParsing Arguments...");
    refresh();
    Arguments args=ArgumentParser::parse(argc,argv);
    std::string file;
    //read file option
    if(args.hasOption("file")){
        file=args.getOption("file");
        printw("Done.\n");
        refresh();
    }else{
        printw("Error\n >Missing required parameter \"-file\"\n");
        printw("Getting file parameter input from user...");
        int sv1_x,sv1_y,sv2_x,sv2_y;
        getyx(stdscr,sv1_y,sv1_x);
        printw("\n >Please Enter file to load:");
        file=getline_curs();
        refresh();
        getyx(stdscr,sv2_y,sv2_x);
        mvprintw(sv1_y,sv1_x,"Done.");
        move(sv2_y,sv2_x);
        refresh();
    }
    std::cout<<"Seeding random number generator...";
    srand(time(NULL));
    std::cout<<"Done.\nInitializing SDL2...";
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        std::cout<<"Error.\n >Error while Initializing SDL: "<<SDL_GetError()<<"\n";
        endwin();
        return 0;
    }
    std::cout<<"Done.\n";
    try{
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
            throw QuitException(1);
        }
        std::cout<<"Done.\nWriting to Output File...";
        for(disassembled_instruction asm_ins:asm_vec){
            f<<asm_ins.getDisplay(location);
            location+=2;
        }
        std::cout<<"Done.\n";
    }else if(args.hasOption("debug")){
        std::cout<<"Initializing Debugger...\n";
        throw std::runtime_error("Debugging not Implemented yet");
    }else{
        std::cout<<"Initializing Chip8 CPU...\n";
        CPU cpu;
        std::cout<<"Done.\nInitializing SDL Handler (IO)...";
        SDLHandler display;
        std::cout<<"Done.\nLoading ROM...";
        cpu.loadProgram(file);
        std::cout<<"Done.\nStarting Emulation.\n";
        while(1){
            try{
                if(display.update(cpu)){
                    break;
                }
                cpu.doCycle();
            }catch(QuitException &e){
                throw;
            }catch(...){
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Exeption Thrown","An Exeption was Thrown by the Emulator, Aborting execution.",0);
                throw;
            }
        }
    }
    }catch(QuitException &e){
        SDL_Quit();
        endwin();
        return e.getEndCode();
    }catch(...){
        SDL_Quit();
        endwin();
        throw;
    }
    SDL_Quit();
    endwin();
    return 0;
}
