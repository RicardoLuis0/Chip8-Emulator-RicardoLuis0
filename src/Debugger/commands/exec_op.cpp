#include "Debugger.h"
#include <curses.h>

void Debugger::command_exec_op(std::vector<std::string> args){
    //exec_op draw_font X Y letter
    //exec_op clear_screen
    if(args.size()<2){
        printw("missing operation argument\n");
    }
    if(args[1]=="draw_font"){
        int temp_I=cpu.I;
        int temp_0=cpu.V0;
        int temp_1=cpu.V1;
        if(args.size()<5){
            printw("missing draw arguments\n");
        }
        cpu.V0=stoi(args[4],nullptr,16);
        cpu.load_font(0);
        cpu.V0=stoi(args[2]);
        cpu.V1=stoi(args[3]);
        cpu.draw_sprite(0,1,5);
        cpu.I=temp_I;
        cpu.V0=temp_0;
        cpu.V1=temp_1;
    }else if(args[1]=="clear_screen"){
        cpu.clear_screen();
    }else{
        printw("unknown operation\n");
    }
}
