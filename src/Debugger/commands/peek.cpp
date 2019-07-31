#include "Debugger.h"
#include "Disassembler.h"
#include <curses.h>


void Debugger::command_peek(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: %s\n",command_help_map["peek"].c_str());
    print_usage:
        printw("\nUsage:");
        printw("\n  'peek registers'\n  - Print Registers' Contents to Terminal\n");
        printw("\n  'peek relative [neg_offset] [pos_offset]\n  - Print RAM Contents to Terminal,\n     Relative to Program Counter location,\n     From PC - 'neg_offset' to PC + 'pos_offset'\n");
        printw("\n  'peek absolute [start_location] [end_location]\n  - Print RAM Contents to Terminal,\n     Absolute location, from 'start_location' to 'end_location'\n");
        return;
    invalid_usage:
        printw("Invalid Usage\n");
        goto print_usage;
    }
    if(args.size()<2){
        printw("missing arguments: rel|pos negative_offset positive_offset\n");
        return;
    }
    uint32_t start;
    uint32_t end;
    try{
        if(args[1]=="registers"){
            printw("PC:0x%03X\n",cpu.PC);
            printw("SP:0x%03X\n",cpu.SP);
            printw("DT:0x%03X\n",cpu.DT);
            printw("ST:0x%03X\n",cpu.ST);
            printw("I:0x%03X\n",cpu.I);
            for(uint8_t i=0;i<16;i++){
                printw("V%X:0x%03X,  KB_%X:%u%s",i,cpu.V[i],i,cpu.KB[i],((i+1)%2?";   ":";\n"));
            }
            return;
        }else if(args[1]=="relative"){
            if(args.size()<4)goto invalid_usage;
            start=cpu.PC-read_num(args[2]);
            end=cpu.PC+read_num(args[3]);
            if(start%2||end%2){
                printw("offsets must not be odd\n");
                return;
            }
        }else if(args[1]=="absolute"){
            if(args.size()<4)goto invalid_usage;
            start=read_num(args[2]);
            end=read_num(args[2]);
            if(start%2||end%2){
                printw("start/end must not be odd\n");
                return;
            }else if(start>end){
                printw("start must not be larger than end\n");
                return;
            }
        }else{
            goto invalid_usage;
        }
    }catch(...){
        goto invalid_usage;
    }
    for(uint32_t i=start;i<=end;i+=2){
        disassembled_instruction inst=Disassembler::disassembleInstruction(cpu.RAM[i],cpu.RAM[i+1]);
        printw("%s\n",inst.getDisplay2(i).c_str());
    }
}
