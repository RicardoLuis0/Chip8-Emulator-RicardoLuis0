#include "AssemblerToken.h"

AssemblerToken::AssemblerToken(AssemblerTokenType_t tok):type(tok),val(0){}

AssemblerToken::AssemblerToken(unsigned long _val):type(LITERAL),val(_val){}
