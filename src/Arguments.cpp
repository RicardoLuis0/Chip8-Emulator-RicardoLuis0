#include "Arguments.h"

Arguments::Arguments(std::map<std::string,std::string> opt_map):options(opt_map){}

bool Arguments::hasOption(std::string option){
    return options.find(option)!=options.end();
}

std::string Arguments::getOption(std::string option){
    auto value=options.find(option);
    if(value!=options.end()){
        return value->second;
    }else{
        throw std::runtime_error("No match for option "+option);
    }
}
