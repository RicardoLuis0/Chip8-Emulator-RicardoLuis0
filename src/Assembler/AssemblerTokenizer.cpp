#include "AssemblerTokenizer.h"

#include <stdexcept>

const static struct{AssemblerTokenType_t type;std::string str;} keywords[]{
    {SYS,"SYS"},
    {CLS,"CLS"},
    {RET,"RET"},
    {JMP,"JMP"},
    {CALL,"CALL"},
    {SE,"SE"},
    {SNE,"SNE"},
    {SKP,"SKP"},
    {SNKP,"SNKP"},
    {KEY,"KEY"},
    {MOV,"MOV"},
    {ADD,"ADD"},
    {SUB,"SUB"},
    {RSB,"RSB"},
    {OR,"OR"},
    {AND,"AND"},
    {XOR,"XOR"},
    {SHR,"SHR"},
    {SHL,"SHL"},
    {RND,"RND"},
    {DRW,"DRW"},
    {LDFNT,"LDFNT"},
    {BCD,"BCD"},
    {STR,"STR"},
    {LDR,"LDR"},
    {V0,"V0"},
    {V1,"V1"},
    {V2,"V2"},
    {V3,"V3"},
    {V4,"V4"},
    {V5,"V5"},
    {V6,"V6"},
    {V7,"V7"},
    {V8,"V8"},
    {V9,"V9"},
    {VA,"VA"},
    {VB,"VB"},
    {VC,"VC"},
    {VD,"VD"},
    {VE,"VE"},
    {VF,"VF"},
};

bool fullHexMatch(std::string buffer);

bool partialHexMatch(std::string buffer){
    if(buffer=="0"||buffer=="0x")return true;
    return fullHexMatch(buffer);
}

bool checkhex(std::string str){
    for(char c:str){
        if(!((c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f')))return false;
    }
    return true;
}

bool fullHexMatch(std::string buffer){
    if(buffer.substr(0,2)!="0x")return false;
    return checkhex(buffer.substr(2));
}

unsigned long getHexMatch(std::string buffer){
    if(buffer.substr(0,2)!="0x")throw std::runtime_error("no match for hex");
    return stoul(buffer.substr(2),0,16);
}

bool partialMatch(std::string buffer){
    for(auto k:keywords){
        if(k.str.length()>=buffer.length()&&
           buffer==k.str.substr(0,buffer.length()))return true;
    }
    return false;
}

bool fullMatch(std::string buffer){
    for(auto k:keywords){
        if(buffer==k.str)return true;
    }
    return false;
}

AssemblerTokenType_t getMatch(std::string buffer){//throws on invalid buffer
    for(auto k:keywords){
        if(buffer==k.str)return k.type;
    }
    throw std::runtime_error("no match for "+buffer);
}

std::vector<AssemblerToken> tokenizeASM(const std::string &asm_str){
    std::vector<AssemblerToken> output;
    std::string buffer="";
    auto tryMatch=[&](){
        if(fullMatch(buffer)){
            output.emplace_back(getMatch(buffer));
            buffer="";
        }else if(fullHexMatch(buffer)){
            output.emplace_back(getHexMatch(buffer));
            buffer="";
        }else{
            throw std::runtime_error("no match for "+buffer);
        }
    };
    char c;
    uint32_t i;
    for(i=0;i<asm_str.length()&&(c=asm_str[i]);i++){
        if(c=='\n'||c==';'||c==' '||c=='\t'||c==','){
            if(buffer!="")tryMatch();
            if(c==';')for(i=0;i<asm_str.length()&&(c=asm_str[i])!='\n';i++);
        }else if(partialMatch(buffer+c)||partialHexMatch(buffer+c)){
            buffer+=c;
        }else{
            tryMatch();
        }
    }
    if(buffer!=""){
        tryMatch();
    }
    return output;
}
