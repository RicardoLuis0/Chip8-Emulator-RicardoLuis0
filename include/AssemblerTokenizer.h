#ifndef ASSEMBLERTOKENIZER_H
#define ASSEMBLERTOKENIZER_H

#include <vector>
#include <string>
#include "AssemblerToken.h"

std::vector<AssemblerToken> tokenizeASM(const std::string &asm_str);

#endif // ASSEMBLERTOKENIZER_H
