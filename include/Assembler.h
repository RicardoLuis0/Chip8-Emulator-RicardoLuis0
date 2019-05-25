#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <vector>
#include <string>
#include "AssemblerToken.h"

bool assemble_file(std::string input_filename,std::string output_filename);//read input file, tokenize, parse and assemble, write instructions into output, return success
std::vector<uint16_t> assemble_tokens(std::vector<std::vector<AssemblerToken>>);//read tokenized asm source, return instruction list
uint16_t assemble_instruction(std::vector<AssemblerToken> line);//read tokenized asm line, return instruction
#endif // ASSEMBLER_H
