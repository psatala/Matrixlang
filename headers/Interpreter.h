#pragma once

#include "Lexer.h"

class Interpreter {
    std::stringstream& inStream;
    std::stringstream& errStream;
    std::stringstream& outStream;
    Lexer lexer;

public:

    Interpreter(std::stringstream& inStream, std::stringstream& errStream, 
        std::stringstream& outStream) : 
        inStream(inStream), errStream(errStream), outStream(outStream),
        lexer(inStream, errStream) {}
};