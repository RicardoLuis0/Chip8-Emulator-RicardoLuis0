#include "QuitException.h"

QuitException::QuitException(int ec):runtime_error("Trying to Quit with exit code "+std::to_string(ec)),endcode(ec){
}

int QuitException::getEndCode(){
    return endcode;
}
