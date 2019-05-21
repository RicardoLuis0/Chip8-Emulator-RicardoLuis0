#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <map>

/**
 * Holds all argument options for the program.
 */
class Arguments {
    public:
        /**
         * Constructor for class
         * @param map of <string option_name,string option_value>
         */
        Arguments(std::map<std::string,std::string> options);
        /**
         * Check if options exists
         * @param option: option name
         * @return whether options exists or not
         */
        bool hasOption(std::string option);
        /**
         * Get option value
         * @param option: option name
         */
        std::string getOption(std::string option);
    protected:
        std::map<std::string,std::string> options;
};

#endif // ARGUMENTS_H
