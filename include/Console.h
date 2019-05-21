#ifndef CONSOLE_H
#define CONSOLE_H


class Console
{
    public:
        Console();
        void moveCursor(short x,short y);
    protected:

    private:
        void * handle;
};

#endif // CONSOLE_H
