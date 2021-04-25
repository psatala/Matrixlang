#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>
int main()
{
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    
    std::ifstream fileStream;
    fileStream.open("../examples/HelloWorld.ml", std::ifstream::in);
    if(fileStream) {
        inStream << fileStream.rdbuf();
        fileStream.close();
    }
    
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);

    while(!interpreter.lexer.getIsProcessed()) {
        Token* token = interpreter.lexer.getToken();
        std::cout << token->type << std::endl;
        delete token;
    }
    return 0;
}