#pragma once

#include <sstream>

#include "Token.h"

class Lexer {
    std::stringstream& inStream;
    std::stringstream& errStream;

    std::stringstream placeholderStringstream;
    
public:
    Lexer(): 
        inStream(placeholderStringstream), errStream(placeholderStringstream) {}
    
    Lexer(std::stringstream& inStream, std::stringstream& errStream) : 
        inStream(inStream), errStream(errStream) {}

    
};