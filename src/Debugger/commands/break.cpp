#include "Debugger.h"
#include <curses.h>

#define GET_HEXPOS() if(args.size()<3){printw("missing position argument\n");return;}uint32_t pos=read_num(args[2]);

void Debugger::command_break(std::vector<std::string> args){
    if(args[0]=="help"||(args.size()>1&&args[1]=="help")){
        printw("Command: %s\n",command_help_map["break"].c_str());
    print_usage:
        printw("\nUsage:");
        printw("\n  'break start'\n  - Enables breaking\n");
        printw("\n  'break stop'\n  - Disables breaking\n");
        printw("\n  'break set [location]'\n  - Sets a breakpoint at 'location' memory position\n");
        printw("\n  'break unset [location]'\n  - Unsets the breakpoint at 'location' memory position\n");
        printw("\n  'break clear'\n  - Unsets all breakpoints\n");
        printw("\n  'break list'\n  - Lists all breakpoints\n");
        return;
    invalid_usage:
        printw("Invalid Usage\n");
        goto print_usage;
    }
    if(args.size()<2){
        goto invalid_usage;
    }
    if(args[1]=="start"){
        printw("Breaking Enabled\n");
        do_breaks=true;
    }else if(args[1]=="stop"){
        printw("Breaking Disabled\n");
        do_breaks=false;
    }else if(args[1]=="set"){
        if(!do_breaks){
            printw("Breaking is Disabled!\n");
        }
        GET_HEXPOS()
        if(breakpoints.find(pos)==breakpoints.end()){
            breakpoints.insert(pos);
            printw("Breakpoint @0x%03lx (%lu) Set\n",pos,pos);
        }else{
            printw("Breakpoint @0x%03lx (%lu) Already Exists\n",pos,pos);
        }
    }else if(args[1]=="unset"){
        GET_HEXPOS()
        breakpoints.erase(pos);
        printw("Breakpoint @0x%03lx (%lu) Unset\n",pos,pos);
    }else if(args[1]=="clear"){
        breakpoints.clear();
        printw("All Breakpoint Unset\n");
    }else if(args[1]=="list"){
        if(breakpoints.empty()){
            printw("No Breakpoints\n");
        }else{
            printw("Breakpoints:\n\n");
            for(uint32_t bkp:breakpoints){
                printw(" * @0x%03lx (%lu)\n",bkp,bkp);
            }
        }
    }else{
        goto invalid_usage;
    }
    return;
}
