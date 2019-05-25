#include "Disassembler.h"
#include "CPU.h"
#include "getHex.h"

disassembled_instruction::disassembled_instruction(RawInstruction _data):data(_data),valid(false){}
disassembled_instruction::disassembled_instruction(RawInstruction _data,std::string _asm_str):data(_data),valid(true),asm_str(_asm_str){}

std::string disassembled_instruction::getDisplay(){
    return (valid?asm_str+";":";INVALID ")+getHex(data.whole,4)+"\n";
}
std::string disassembled_instruction::getDisplay(uint16_t location){
    return (valid?asm_str+";":";INVALID ")+getHex(data.whole,4)+"@"+getHex(location,4)+"\n";
}

disassembled_instruction Disassembler::disassembleInstruction(uint8_t byte0,uint8_t byte1){
    return disassembleInstruction(RawInstruction(byte0,byte1));
}

disassembled_instruction Disassembler::disassembleInstruction(uint16_t bytewhole){
    return disassembleInstruction(RawInstruction(bytewhole));
}

disassembled_instruction Disassembler::disassembleInstruction(RawInstruction instruction){
    operation_t op=CPU::decodeInstruction(instruction);
    switch(op){
    case SYS://SYS NNN
        return disassembled_instruction(instruction,"SYS "+getHex(instruction.section234,3));
    case CLS://CLS
        return disassembled_instruction(instruction,"CLS");
    case RET://RET
        return disassembled_instruction(instruction,"CLS");
    case JMP://JMP NNN
        return disassembled_instruction(instruction,"JMP "+getHex(instruction.section234,3));
    case JMP_V0://JMP V0,NNN
        return disassembled_instruction(instruction,"JMP V0,"+getHex(instruction.section234,3));
    case CALL://CALL NNN
        return disassembled_instruction(instruction,"CALL "+getHex(instruction.section234,3));
    case SE://SE VX,NN
        return disassembled_instruction(instruction,"SE V"+getHexSimple(instruction.section2,1)+","+getHex(instruction.section34,2));
    case SE_REG://SE VX,VY
        return disassembled_instruction(instruction,"SE V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case SNE://SNE VX,NN
        return disassembled_instruction(instruction,"SNE V"+getHexSimple(instruction.section2,1)+","+getHex(instruction.section34,2));
    case SNE_REG://SNE VX,VY
        return disassembled_instruction(instruction,"SNE V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case MOV://MOV VX,NN
        return disassembled_instruction(instruction,"MOV V"+getHexSimple(instruction.section2,1)+","+getHex(instruction.section34,2));
    case MOV_REG://MOV VX,VY
        return disassembled_instruction(instruction,"MOV V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case MOV_I://MOV I,NNN
        return disassembled_instruction(instruction,"MOV I,"+getHex(instruction.section234,3));
    case MOV_REG_DT://MOV VX,DT
        return disassembled_instruction(instruction,"MOV V"+getHexSimple(instruction.section2,1)+",DT");
    case MOV_DT://MOV DT,VX
        return disassembled_instruction(instruction,"MOV DT,V"+getHexSimple(instruction.section2,1));
    case MOV_ST://MOV ST,VX
        return disassembled_instruction(instruction,"MOV ST,V"+getHexSimple(instruction.section2,1));
    case ADD://ADD VX,NN
        return disassembled_instruction(instruction,"ADD V"+getHexSimple(instruction.section2,1)+","+getHex(instruction.section34,2));
    case ADD_REG://ADD VX,VY
        return disassembled_instruction(instruction,"ADD V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case ADD_I://ADD I,VX
        return disassembled_instruction(instruction,"ADD I,V"+getHexSimple(instruction.section2,1));
    case OR://OR VX,VY
        return disassembled_instruction(instruction,"OR V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case AND://AND VX,VY
        return disassembled_instruction(instruction,"AND V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case XOR://XOR VX,VY
        return disassembled_instruction(instruction,"XOR V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case SUB://SUB VX,VY
        return disassembled_instruction(instruction,"SUB V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case SHR://SHR VX,VY
        return disassembled_instruction(instruction,"SHR V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case RSB://RSB VX,VY
        return disassembled_instruction(instruction,"RSB V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case SHL://SHL VX,VY
        return disassembled_instruction(instruction,"SHL V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case RND://RND VX,VY
        return disassembled_instruction(instruction,"RND V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1));
    case DRW://DRW VX,VY,N
        return disassembled_instruction(instruction,"DRW V"+getHexSimple(instruction.section2,1)+",V"+getHexSimple(instruction.section3,1)+","+getHex(instruction.section4,1));
    case SKP://SKP VX
        return disassembled_instruction(instruction,"SKP V"+getHexSimple(instruction.section2,1));
    case SNKP://SNKP VX
        return disassembled_instruction(instruction,"SNKP V"+getHexSimple(instruction.section2,1));
    case KEY://KEY VX
        return disassembled_instruction(instruction,"KEY V"+getHexSimple(instruction.section2,1));
    case LDFNT://LDFNT VX
        return disassembled_instruction(instruction,"LDFNT V"+getHexSimple(instruction.section2,1));
    case BCD://BCD VX
        return disassembled_instruction(instruction,"BCD V"+getHexSimple(instruction.section2,1));
    case STR://STR VX
        return disassembled_instruction(instruction,"STR V"+getHexSimple(instruction.section2,1));
    case LDR://LDR VX
        return disassembled_instruction(instruction,"LDR V"+getHexSimple(instruction.section2,1));
    default:
    case INVALID_OPERATION:
        return disassembled_instruction(instruction);
    }
}
