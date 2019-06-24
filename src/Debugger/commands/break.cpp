#include "Debugger.h"
#include <curses.h>


#define GET_HEXPOS() if(args.size()<3){printw("missing position argument\n");return;}bool is_hex=args[2].substr(0,2)=="0x";uint32_t pos=is_hex?stoul(args[2].substr(2),nullptr,16):stoul(args[2]);

void Debugger::command_break(std::vector<std::string> args){
    if(args.size()<2){
        printw("missing action argument\n");
    }
    if(args[1]=="set"){
        GET_HEXPOS()
        breakpoints.insert(pos);
        printw("breakpoint @0x%03lx (%lu) set\n",pos,pos);
    }else if(args[1]=="unset"){
        GET_HEXPOS()
        breakpoints.erase(pos);
        printw("breakpoint @0x%03lx (%lu) unset\n",pos,pos);
    }else if(args[1]=="clear"){
        breakpoints.clear();
        printw("all breakpoint cleared\n");
    }else if(args[1]=="list"){
        for(uint32_t bkp:breakpoints){
            printw(" * @0x%03lx (%lu)\n",bkp,bkp);
        }
    }else{
        printw("invalid action argument\n");
    }
    return;
}
