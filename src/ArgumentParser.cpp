#include "ArgumentParser.h"

//std::map<std::string,bool> name,uses_parameter

Arguments ArgumentParser::parse(int argc,char ** argv,std::map<std::string,bool> option_types){
    bool reading_option=false;
    std::string option;
    std::map<std::string,std::string> options;
    char * str;
    for(int i=1;i<argc&&(str=argv[i]);i++){
        if(str[0]=='-'){
            if(str[1]!='\0'){
                if(reading_option){
                    throw std::runtime_error("MISSINGVALUE"+option);
                }
                option=std::string(&str[1]);
                if(option_types.find(option)==option_types.end()){
                    throw std::runtime_error(option);
                }
                if(option_types[option]){
                    reading_option=true;
                }else{
                    options[option]="";
                }
                continue;
            }
        }
        if(reading_option){
            options[option]=std::string(str);
            reading_option=false;
        }
    }
    if(reading_option){
        throw std::runtime_error("MISSINGVALUE"+option);
    }
    return Arguments(options);
}
