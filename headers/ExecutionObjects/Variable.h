#pragma once

#include "../Token.h"

class Variable {
public:
    TokenType type;
    virtual bool getLogicalValue() { return false; }
};
