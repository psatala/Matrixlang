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

    while(!interpreter.lexer.getIsProcessed()) {
        Token* token = interpreter.lexer.getToken();
        std::cout << token->type << std::endl;
        delete token;
    }
    return 0;
}