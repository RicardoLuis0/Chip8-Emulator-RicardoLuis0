#include "Debugger.h"

Debugger::UnclosedStringException::UnclosedStringException():runtime_error("Unclosed String In splitCommand"){}

std::vector<std::string> Debugger::splitCommand(std::string s){
    std::vector<std::string> temp;
    std::string buffer;
    bool reading_string=false;
    bool reading_escape=false;
    for(char c:s){
        if(reading_string){
            if(reading_escape){
                buffer+=c;
                reading_escape=false;
            }else{
                if(c=='\\'){
                    reading_escape=true;
                }else if(c=='"'){
                    temp.push_back(buffer);
                    reading_string=false;
                }
            }
        }else{
            if(c==' '||c=='"'){
                if(buffer.length()>0)temp.push_back(buffer);
                if(c=='"'){
                    reading_string=true;
                    reading_escape=false;
                }
            }else{
                buffer+=c;
            }
        }
    }
    if(reading_string){
        throw UnclosedStringException();
    }
    if(buffer.length()>0){
        temp.push_back(buffer);
    }
    return temp;
}

