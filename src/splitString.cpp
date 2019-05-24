#include "splitString.h"

#include <algorithm>
#include <functional>

std::vector<std::string> splitString(std::string str,std::vector<delimdata> delims){
    bool add=false;
    std::string buffer;
    std::vector<std::string> output;
    for(char c:str){
        add=true;
        for(delimdata d:delims){
            if(c==d.delim){
                if(buffer.size()>0||!d.skipempty){
                    output.push_back(buffer);
                    buffer="";
                }
                add=false;
                break;
            }
        }
        if(add) buffer+=c;
    }
    if(buffer.size()>0){
        output.push_back(buffer);
    }
    return output;
}

std::vector<std::string> splitString(std::string str,char delim,bool skipempty){
    std::string buffer;
    std::vector<std::string> output;
    for(char c:str){
        if(c==delim){
            if(buffer.size()>0||!skipempty){
                output.push_back(buffer);
                buffer="";
            }
        }else{
            buffer+=c;
        }
    }
    if(buffer!=""){
        output.push_back(buffer);
    }
    return output;
}
