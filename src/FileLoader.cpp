#include "FileLoader.h"

#include <stdexcept>

#define PROGRAM_MAX_SIZE 4096

Program FileLoader::load(std::string filename,int max_len){
    FILE * f=fopen(filename.c_str(),"rb");
    if(f){
        fseek(f,0,SEEK_END);
        long len=ftell(f);
        fseek(f,0,SEEK_SET);
        if(len>max_len){
            fclose(f);
            throw std::runtime_error("file too large, size: "+std::to_string(len)+", max: "+std::to_string(max_len));
        }
        unsigned char * data=new unsigned char[len];
        fread(data,len,1,f);
        fclose(f);
        return Program(short(len),data);
    }else{
        throw std::runtime_error("could not open file: \""+filename+"\"");
    }
}
