#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>
int main()
{
    // std::unique_ptr<std::ifstream> fileStream = 
    //     std::make_unique<std::ifstream>();

    // fileStream->open("../examples/HelloWorld.ml", std::ifstream::in);
    // if(!*fileStream)
    //     return -1;
    
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            R"(Matrix <int>[,])");

    Interpreter interpreter = Interpreter(std::move(inStream), std::cerr, 
        std::cout);

    // while(!interpreter.parser.lexer.getIsProcessed()) {
    //     const std::optional<Token> token = interpreter.parser.lexer.getToken();
    //     std::cout << token->type << std::endl;
    // }
    try {
            interpreter.parser.parseMatrixType().value();
    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}