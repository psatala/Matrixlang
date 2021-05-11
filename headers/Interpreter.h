#pragma once

#include "Parser.h"

class Interpreter {
    std::ostream& errStream;
    std::ostream& outStream;
    

public:
    Parser parser;

    Interpreter(std::unique_ptr<std::istream> inStream, std::ostream& errStream, 
        std::ostream& outStream) : 
        errStream(errStream), outStream(outStream),
        parser(std::move(inStream), errStream) {}
};