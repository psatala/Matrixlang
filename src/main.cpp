#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/Interpreter.h"

#include "../tests/TestPrograms.h"

int main()
{
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(R"(
                int main()
                    1 + 2 + 3;
                )");

    fileStream->open("../examples/HelloWorld.ml", std::ifstream::in);
    if(!*fileStream)
        return -1;

    Interpreter interpreter = Interpreter(std::move(inStream), std::cerr, 
        std::cout);

    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();
        std::cout << program->print();


    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}