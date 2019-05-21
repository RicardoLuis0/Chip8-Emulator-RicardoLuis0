#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Console.h"

Console::Console(){
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    
}
void Console::moveCursor(short x,short y){
    SetConsoleCursorPosition(handle,{x,y});
}
