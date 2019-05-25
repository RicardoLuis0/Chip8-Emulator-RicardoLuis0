#ifndef ASSEMBLERTOKENIZER_H
#define ASSEMBLERTOKENIZER_H

#include <vector>
#include <string>
#include "AssemblerToken.h"

///@return vector of lines (a line is a vector of tokens)
std::vector<std::vector<AssemblerToken>> tokenizeASM(const std::string &asm_str);

#endif // ASSEMBLERTOKENIZER_H
