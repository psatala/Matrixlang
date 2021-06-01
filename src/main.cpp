#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/Interpreter.h"

#include "../tests/TestPrograms.h"

int main(int argc, char** argv)
{
    if(argc < 2) {
        std::cerr << "File name not specified";
        return -1;
    }
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();

    fileStream->open(std::string(argv[1]), std::ifstream::in);
    if(!*fileStream) {
        std::cerr << "Could not open file";
        return -1;
    }

    Interpreter interpreter = Interpreter(std::move(fileStream), std::cin, 
        std::cerr, std::cout);
    interpreter.start();
    return 0;
}