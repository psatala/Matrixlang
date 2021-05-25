#pragma once

#include <gtest/gtest.h>
#include "../headers/Interpreter.h"


//class for passing data to parametrised tests
class ParserInputOutput {
public:
    std::string input;
    std::string expectedOutput;
    ParserInputOutput(std::string input, std::string expectedOutput) :
        input(input), expectedOutput(expectedOutput) {}
};
