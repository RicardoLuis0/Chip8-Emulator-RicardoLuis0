#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <thread>

#include <SDL2/SDL.h>
#include "ArgumentParser.h"
#include "FileLoader.h"
#include "splitString.h"
#include "Disassembler.h"
#include "SDLHandler.h"
#include "Debugger.h"

#include <cstring>

#include <curses.h>
#include "QuitException.h"

std::string getline_curs(){
    char c;
    std::string buffer;
    while((c=getch())!='\n'){
        if(c=='\b'){
            if(buffer.length()>0){
                buffer.resize(buffer.length()-1);
                clrtoeol();
            }
        }else{
            buffer+=c;
        }
    }
    return buffer;
}

std::map<std::string,bool> paramdata{
    {"file",true},
    {"debug",false},
    {"disassemble",false},
};

int main(int argc,char ** argv){
    std::string file;
    std::string usage("\nUsage:\n\t-file [filename]\t: filename to open, does not apply to debug mode\n\t-debug\t\t\t: debug mode\n\t-disassemble\t\t: disassemble ROM\n");
    Arguments args({});
    try{
        args=ArgumentParser::parse(argc,argv,paramdata);
    }catch(std::runtime_error &e){
        std::string temp(e.what());
        if(temp.substr(0,12)=="MISSINGVALUE"){
            printf("Error.\nMissing value for -%s parameter\n",std::string(e.what()).substr(12).c_str());
        }else{
            printf("Error.\nInvalid parameter -%s\n%s",temp.c_str(),usage.c_str());
        }
        return 1;
    }
    //read file option
    if(!args.hasOption("file")&&!args.hasOption("debug")){
        printf("Error.\nMissing -file parameter.\n%s",usage.c_str());
        return 1;
    }
    if(args.hasOption("file"))file=args.getOption("file");
    initscr();
    scrollok(stdscr,true);
    printw("Chip8 Emulator\nby RicardoLuis0\n");
    printw("\nSeeding random number generator...");
    srand(time(NULL));
    printw("Done.\n");
    refresh();
    printw("Initializing SDL2...");
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        printw("Error.\n >Error while Initializing SDL: %s\n",SDL_GetError());
        endwin();
        return 0;
    }
    printw("Done.\n");
    try{
        if(args.hasOption("disassemble")){
            printw("Opening Input File...");
            Program p=FileLoader::load(file,4096-0x200);
            std::vector<disassembled_instruction> asm_vec;
            printw("Done.\nStarting Disassembly...");
            for(unsigned i=0;i<p.length;){
                uint8_t byte0=p.data[i++];
                if(i<p.length){
                    uint8_t byte1=p.data[i++];
                    asm_vec.push_back(Disassembler::disassembleInstruction(byte0,byte1));
                }
            }
            printw("Done.\nOpening Output File...");
            uint16_t location=0x200;
            std::ofstream f(splitString(file,{{'/',false},{'\\',false}}).back()+".c8asm");
            if(!f){
                printw("Error.\n Could not open file\n");
                throw QuitException(1);
            }
            printw("Done.\nWriting to Output File...");
            for(disassembled_instruction asm_ins:asm_vec){
                f<<asm_ins.getDisplay(location);
                location+=2;
            }
            printw("Done.\n");
        }else if(args.hasOption("debug")){
            printw("Initializing Debugger...");
            Debugger debugger;
            printw("Done.\n");
            debugger.startDebug();
        }else{
            printw("Initializing Chip8 CPU...\n");
            CPU cpu;
            printw("Done.\nLoading ROM...");
            cpu.loadProgram(file);
            printw("Done.\nOpening Display Window...");
            SDLHandler display;
            printw("Done.\nStarting Emulation.\n");
            while(1){
                try{
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
