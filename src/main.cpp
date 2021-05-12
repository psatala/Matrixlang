#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>


int main()
{
    
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            R"(Vector<float>[ ])"
            );

    Interpreter interpreter = Interpreter(std::move(inStream), std::cerr, 
        std::cout);

    try {

    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}