#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>


int main()
{
    
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            // R"(a = b + c * 2 < d)"
            // R"(++--!a)"
            // R"(a + ++ b)"
            // R"(1)"
            // R"("abc" 1 + 2 "def")"
            // R"(abc(1, 2 + 3))"
            R"(a[1][2, 3])"
            );

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