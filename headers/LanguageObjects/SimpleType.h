#pragma once

#include "../Token.h"
#include "Type.h"

class SimpleType : public Type {

    std::string getTokenTypeInfo() {
        switch(type) {
            case INT:
                return "int";
            case FLOAT:
                return "float";
            case STRING:
                return "string";
            default:
                return "unknown type";
        }   
    }

public:
    TokenType type;
    SimpleType(TokenType type): type(type) {}
    std::string print(int identLevel) override {
        return std::string("Simple type: ") + getTokenTypeInfo() + "\n";
    }
};
