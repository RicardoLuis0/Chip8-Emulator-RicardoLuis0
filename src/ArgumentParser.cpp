#include "ArgumentParser.h"

using std::map;
using std::string;

Arguments ArgumentParser::parse(int argc,char ** argv){
    bool filename_read=false;
    bool reading_option=false;
    string option;
    map<string,string> options;
    char * str;
    for(int i=1;i<argc&&(str=argv[i]);i++){
        if(str[0]=='-'){
            if(str[1]!='\0'){
                if(reading_option){
                    options[option]="";
                }
                option=string(&str[1]);
                continue;
            }
        }
        if(reading_option){
            if(option=="file"){
                filename_read=true;
            }
            options[option]=string(str);
            reading_option=false;
        }else if(!filename_read){
            options["file"]=string(str);
        }
    }
    return Arguments(options);
}
