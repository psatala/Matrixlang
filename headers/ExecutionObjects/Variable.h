#pragma once

#include "../Token.h"

class Variable {
public:
    TokenType type;
    virtual void overrideMe() = 0;
};
