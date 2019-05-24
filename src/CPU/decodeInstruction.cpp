#include "CPU.h"

operation_t CPU::decodeInstruction(RawInstruction operation){
    switch(operation.section1){
    case 0x0://CLS,RET,SYS
        switch(operation.section234){
        case 0x0E0://CLS
            return CLS;
        case 0x0EE://RET
            return RET;
        default://SYS NNN
            return SYS;
        }
    case 0x1://JMP NNN
        return JMP;
    case 0x2://CALL NNN
        return CALL;
    case 0x3://SE VX NNN
        return SE;
    case 0x4://SNE VX NNN
        return SNE;
    case 0x5://SE VX,VY
        if(operation.section4==0x0){
            return SE_REG;
        }
        return INVALID_OPERATION;
    case 0x6://MOV VX,NN
        return MOV;
    case 0x7://ADD VX,NN
        return ADD;
    case 0x8://MOV,OR,AND,XOR,ADD,SHR,RSB,SHL
        switch(operation.section4){
        case 0x0://MOV VX,VY
            return MOV_REG;
        case 0x1://OR VX,VY
            return OR;
        case 0x2://AND VX,VY
            return AND;
        case 0x3://XOR VX,VY
            return XOR;
        case 0x4://ADD VX,VY
            return ADD_REG;
        case 0x5://SUB VX,VY
            return SUB;
        case 0x6://SHR VX,VY
            return SHR;
        case 0x7://RSB VX,VY
            return RSB;
        case 0xE://SHL VX,VY
            return SHL;
        default:
            return INVALID_OPERATION;
        }
        break;
    case 0x9://SNE VX,VY
        if(operation.section4==0x0){
            return SNE_REG;
        }
        return INVALID_OPERATION;
    case 0xA://MOV I,NNN
        return MOV_I;
    case 0xB://JMP V0,NNN
        return JMP_V0;
    case 0xC://RND VX,NN
        return RND;
    case 0xD://DRW VX,VY,N
        return DRW;
    case 0xE://SKP,SNKP
        switch(operation.section34){
        case 0x9E://SKP VX
            return SKP;
        case 0xA1://SNKP VY
            return SNKP;
        default:
            return INVALID_OPERATION;
        }
        break;
    case 0xF://MOV,KEY,ADD,FONT,STR,LDR
        switch(operation.high_byte){
        case 0x07://MOV VX,DT
            return MOV_V_DT;
        case 0x0A://KEY VX
            return KEY;
        case 0x15://MOV DT,VX
            return MOV_DT;
        case 0x18://MOV ST,VX
            return MOV_ST;
        case 0x1E://ADD I,VX
            return ADD;
        case 0x29://FONT VX
            return FONT;
        case 0x33://BCD VX
            return BCD;
        case 0x55://STR VX
            return STR;
        case 0x65://LDR VX
            return LDR;
        default:
            return INVALID_OPERATION;
        }
    }
}
