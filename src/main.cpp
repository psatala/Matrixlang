#include <iostream>

#include "../headers/Interpreter.h"

int main()
{
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    inStream << "int a = 10;";
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);
    return 0;
}