#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include "Arguments.h"

/**
 * Parses the arguments sent to the program, and splits it into options
 */
class ArgumentParser {
    public:
        /**
         * parses argc,argv into and generates an Arguments object
         * @param argc: number of arguments
         * @param argv: list of arguments
         * @return Arguments object created from inputs
         */
        static Arguments parse(int argc,char ** argv,std::map<std::string,bool> exists);
};

#endif // ARGUMENTPARSER_H
