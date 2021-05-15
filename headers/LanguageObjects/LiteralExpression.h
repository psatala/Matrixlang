#pragma once

#include <memory>

#include "Expression.h"
#include "../Token.h"

class LiteralExpression : public Expression {

    std::string getTokenInfo() {
        if(INT_NUMBER == token.type)
            return "int number: " + std::to_string(std::get<int>(token.value));
        if(FLOAT_NUMBER == token.type)
            return "float number: " + 
                std::to_string(std::get<float>(token.value));
        return "unexpected token type";
    }

public:
    Token token;
    LiteralExpression(Token token): token(token) {}
    
    std::string print(int identationLevel) override {
        return std::string("Literal expression: ") + getTokenInfo() + "\n";
    }

};
