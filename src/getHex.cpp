#include "getHex.h"
#include <sstream>
#include <algorithm>

std::string getHex(unsigned n,unsigned d){
    std::stringstream sstream;
    std::string str;
    sstream<<std::hex<<n;
    sstream>>str;
    str="0x"+std::string(std::max(0u,d-str.length()),'0')+str;
    return str;
}

std::string getHexSimple(unsigned n,unsigned d){
    std::stringstream sstream;
    std::string str;
    sstream<<std::hex<<n;
    sstream>>str;
    str=std::string(std::max(0u,d-str.length()),'0')+str;
    return str;
}
