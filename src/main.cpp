#include <iostream>


#include "ArgumentParser.h"
#include "Console.h"
#include "Emulator.h"

int main(int argc,char ** argv){
    std::cout<<"Chip8 Emulator\nby RicardoLuis0\n\n";
    std::cout<<"Creating Console Object...";
    Console con;
    std::cout<<"Done\n";
    std::cout<<"Parsing Arguments...";
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
    Emulator emu;
    emu.loadProgramFile(file);
    while(1){
        emu.runCycle();
    }
    return 0;
}
