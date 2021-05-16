#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>


int main()
{
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();

    fileStream->open("../examples/HelloWorld.ml", std::ifstream::in);
    if(!*fileStream)
        return -1;


    Interpreter interpreter = Interpreter(std::move(fileStream), std::cerr, 
        std::cout);

    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();
        std::cout << program->print();


    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}