#pragma once

#include <map>

#include "../Token.h"

class Operator {
public:
    TokenType type;
    Operator(TokenType type) : type(type) { operatorMapSetup(); }

    std::map<TokenType, std::string> operatorMap;
    void operatorMapSetup() {
        operatorMap[PLUS] = "+";
        operatorMap[MINUS] = "-";
        operatorMap[MULTIPLY] = "*";
        operatorMap[DIVIDE] = "/";
        operatorMap[MODULO] = "%";
        operatorMap[LESS_THAN] = "<";
        operatorMap[MORE_THAN] = ">";
        operatorMap[NOT] = "!";
        operatorMap[ASSIGN] = "=";

        operatorMap[COLON] = ":";
        operatorMap[SEMICOLON] = ";";
        operatorMap[COMMA] = ",";
        operatorMap[DOT] = ".";
        operatorMap[L_SQUARE_BRACKET] = "[";
        operatorMap[R_SQUARE_BRACKET] = "]";
        operatorMap[L_PARENT] = "(";
        operatorMap[R_PARENT] = ")";
        operatorMap[L_BRACKET] = "{";
        operatorMap[R_BRACKET] = "}";
        operatorMap[INCREMENT] = "++";
        operatorMap[DECREMENT] = "--";
        
        operatorMap[LESS_EQUAL] = "<=";
        operatorMap[MORE_EQUAL] = ">=";
        operatorMap[EQUAL] = "==";
        operatorMap[NOT_EQUAL] = "!=";

        operatorMap[AND] = "&&";
        operatorMap[OR] = "||";
        
        operatorMap[PLUS_ASSIGN] = "+=";
        operatorMap[MINUS_ASSIGN] = "-=";
        operatorMap[MULTIPLY_ASSIGN] = "*=";
        operatorMap[DIVIDE_ASSIGN] = "/=";
        operatorMap[MODULO_ASSIGN] = "%=";
    }
    
    std::string print(int identationLevel) {
        return operatorMap[type] + "\n";
    }
};
