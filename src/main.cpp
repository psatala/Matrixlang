#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/Interpreter.h"

#include "../tests/TestPrograms.h"

int main(int argc, char** argv)
{
    // parsing arguments
    if(argc < 2) {
        std::cerr << "File name not specified";
        return -1;
    }
    if(argc >= 3) {
        // resize stack
        // be aware that there is no hard cap if you choose to resize the stack
        // use this option responsibly
        try {
            int newStackSize = std::stoi(std::string(argv[2]));
            if(newStackSize < 0) {
                std::cerr << "Resizing stack: stack height must not be "
                    "negative\n";
                return -1;
            }
            ScopeManager::MAX_STACK_DEPTH = 
                static_cast<unsigned int>(newStackSize);
        }
        catch(std::invalid_argument) {
            std::cerr << "Resizing stack: Cannot convert string to int: "
                "argument invalid\n";
            return -1;
        }
        catch(std::out_of_range) {
            std::cerr << "Resizing stack: Cannot convert string to int: "
                "argument out of range";
            return -1;
        }
    }

    // open file
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();

    fileStream->open(std::string(argv[1]), std::ifstream::in);
    if(!*fileStream) {
        std::cerr << "Could not open file";
        return -1;
    }

    // run interpreter
    Interpreter interpreter = Interpreter(std::move(fileStream), std::cin, 
        std::cerr, std::cout);
    interpreter.start();
    return 0;
}