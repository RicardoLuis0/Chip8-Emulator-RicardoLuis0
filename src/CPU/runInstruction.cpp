#include "CPU.h"
#include "getHex.h"
#include <stdexcept>

void CPU::runInstruction(operation_t op,RawInstruction data){

    switch(op){
    case INVALID_OPERATION:
        throw std::runtime_error("Invalid Operation: "+getHex(data.whole,4)+"\n");
    case SYS:
        sys_call(data.section234);
        break;
    case CLS:
        clear_screen();
        break;
    case RET:
        return_procedure();
        break;
    case JMP:
        jump(data.section234);
        break;
    case JMP_V0:
        jump_v0(data.section234);
        break;
    case CALL:
        call_procedure(data.section234);
        break;
    case SE:
        skip_if_eq(data.section2,data.section34);
        break;
    case SE_REG:
        skip_if_eq_reg(data.section2,data.section3);
        break;
    case SNE:
        skip_if_not_eq(data.section2,data.section34);
        break;
    case SNE_REG:
        skip_if_not_eq_reg(data.section2,data.section3);
        break;
    case MOV:
        move(data.section2,data.section34);
        break;
    case MOV_REG:
        move_reg(data.section2,data.section3);
        break;
    case MOV_I:
        move_i(data.section234);
        break;
    case MOV_REG_DT:
        move_reg_dt(data.section2);
        break;
    case MOV_DT:
        move_dt(data.section2);
        break;
    case MOV_ST:
        move_st(data.section2);
        break;
    case ADD:
        add(data.section2,data.section34);
        break;
    case ADD_REG:
        add_reg(data.section2,data.section3);
        break;
    case OR:
        or_operation(data.section2,data.section3);
        break;
    case AND:
        and_operation(data.section2,data.section3);
        break;
    case XOR:
        xor_operation(data.section2,data.section3);
        break;
    case SUB:
        subtract(data.section2,data.section3);
        break;
    case SHR:
        shift_right(data.section2,data.section3);
        break;
    case RSB:
        reverse_subtract(data.section2,data.section3);
        break;
    case SHL:
        shift_left(data.section2,data.section3);
        break;
    case RND:
        random(data.section2,data.section34);
        break;
    case DRW:
        draw_sprite(data.section2,data.section3,data.section4);
        break;
    case SKP:
        skip_key(data.section2);
        break;
    case SNKP:
        skip_not_key(data.section2);
        break;
    case KEY:
        read_key(data.section2);
        break;
    case LDFNT:
        load_font(data.section2);
        break;
    case BCD:
        binary_coded_decimal(data.section2);
        break;
    case STR:
        store(data.section2);
        break;
    case LDR:
        load(data.section2);
        break;
    }
}
