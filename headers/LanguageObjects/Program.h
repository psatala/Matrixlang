#pragma once

#include <memory>

#include "Expression.h"
#include "../LanguageObjects.h"

class Program {
public:
    std::unique_ptr<Expression> expression;
    Program(std::unique_ptr<Expression> expression) : 
        expression(std::move(expression)) {}
    std::string print() {
        return std::string("Program") + "\n"
            + ident(1) + expression->print(2);
    }
};
