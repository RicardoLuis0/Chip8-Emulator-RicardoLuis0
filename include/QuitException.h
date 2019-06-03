#ifndef QUITEXCEPTION_H
#define QUITEXCEPTION_H

#include <stdexcept>

class QuitException:std::runtime_error{
    public:
        QuitException(int endcode);
        int getEndCode();
    protected:
        int endcode;
};

#endif // QUITEXCEPTION_H
