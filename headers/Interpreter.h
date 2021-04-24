#pragma once

#include "Lexer.h"

class Interpreter {
    std::stringstream& inStream;
    std::stringstream& errStream;
    std::stringstream& outStream;
    

public:
    Lexer lexer;

    Interpreter(std::stringstream& inStream, std::stringstream& errStream, 
        std::stringstream& outStream) : 
        inStream(inStream), errStream(errStream), outStream(outStream),
        lexer(inStream, errStream) {}
};