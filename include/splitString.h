#ifndef SPLITSTRING_H
#define SPLITSTRING_H

#include <string>
#include <vector>
struct delimdata{
    char delim;
    bool skipempty;
};
std::vector<std::string> splitString(std::string str,char delim,bool skipempty);
std::vector<std::string> splitString(std::string str,std::vector<delimdata> delims);

#endif // SPLITSTRING_H
