#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>

#include "Program.h"

class FileLoader {
    public:
        static Program load(std::string filename,int max_len=4096);
};

#endif // FILELOADER_H
