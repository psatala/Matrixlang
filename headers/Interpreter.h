#pragma once

#include "Lexer.h"

class Interpreter {
    std::ostream& errStream;
    std::ostream& outStream;
    

public:
    Lexer lexer;

    Interpreter(std::unique_ptr<std::istream> inStream, std::ostream& errStream, 
        std::ostream& outStream) : 
        errStream(errStream), outStream(outStream),
        lexer(std::move(inStream), errStream) {}
};