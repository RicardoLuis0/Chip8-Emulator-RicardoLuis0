#include "CPU.h"
#include <stdexcept>

void CPU::sys_call(uint16_t address){//call system procedure at address
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::clear_screen(){//clear screen
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::return_procedure(){//return from procedure
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::jump(uint16_t address){//jump to address
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::jump_v0(uint16_t address){//jump to V[0]+address
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::call_procedure(uint16_t address){//call procedure at address
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::skip_if_eq(uint8_t X,uint8_t value){//skip next instruction if V[X] == value
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::skip_if_eq_reg(uint8_t X,uint8_t Y){//skip next instruction if V[X] == V[Y]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::skip_if_not_eq(uint8_t X,uint8_t value){//skip next instruction if V[X] != value
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::skip_if_not_eq_reg(uint8_t X,uint8_t Y){//skip next instruction if V[X] != V[Y]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::move(uint8_t X,uint8_t value){//move value to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::move_reg(uint8_t X,uint8_t Y){//move V[Y] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::move_i(uint8_t value){//move value to I
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::move_reg_dt(uint8_t X){//move DT to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::move_dt(uint8_t X){//move DT to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::move_st(uint8_t X){//move ST to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::add(uint8_t X,uint8_t value){//add value to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::add_reg(uint8_t X,uint8_t Y){//add V[Y] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::or_operation(uint8_t X,uint8_t Y){//move V[X] | V[Y] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::and_operation(uint8_t X,uint8_t Y){//move V[X] & V[Y] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::xor_operation(uint8_t X,uint8_t Y){//move V[X] ^ V[Y] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::subtract(uint8_t X,uint8_t Y){//subtract V[Y] from V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::shift_right(uint8_t X,uint8_t Y){//shift V[X] to the right by 1, store least significant bit in V[Y]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::reverse_subtract(uint8_t X,uint8_t Y){//move V[Y]-V[X] to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::shift_left(uint8_t X,uint8_t Y){//shift V[X] to the left by 1, store most significant bit in V[Y]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::random(uint8_t X,uint8_t mask){//move random number & mask to V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::draw_sprite(uint8_t X,uint8_t Y,uint8_t height){//draw sprite stored in memory location I at (V[X],V[Y]) coords, with given height
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::skip_key(uint8_t X){//skip next instruction if the key at V[X] is currently pressed
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::skip_not_key(uint8_t X){//skip next instruction if the key at V[X] is currently NOT pressed
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::read_key(uint8_t X){//wait for keypress, and store it at V[X]
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::load_font(uint8_t X){//move the location of the font for V[X] to I
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::binary_coded_decimal(uint8_t X){//store the binary coded decimal value of V[X] at I,I+1,I+2
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::store(uint8_t X){//store the values of V[0]~V[X] to memory starting at I
    throw std::runtime_error("Unimplemented Operation");
}
void CPU::load(uint8_t X){//load the values of V[0]~V[X] from memory starting at I
    throw std::runtime_error("Unimplemented Operation");
}
