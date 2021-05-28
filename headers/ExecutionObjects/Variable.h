#pragma once

#include <memory>

#include "../Token.h"

class Variable {
public:
    TokenType type;
    virtual void overrideMe() {}// = 0;

    virtual std::unique_ptr<Variable> add(const Variable* firstVariable, 
        const Variable* secondVariable) {
        throw std::string("Addition operator not supported for those types");
    }
    
};
