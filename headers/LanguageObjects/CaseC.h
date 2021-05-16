#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "../Token.h"
#include "InstructionList.h"

class CaseC {

    std::string getTokenInfo() {
        if(INT_NUMBER == token.type)
            return "int number: " + std::to_string(std::get<int>(token.value));
        if(FLOAT_NUMBER == token.type)
            return "float number: " + 
                std::to_string(std::get<float>(token.value));
        if(STRING == token.type)
            return "string literal: " + std::get<std::string>(token.value);
        return "unexpected token type";
    }

public:
    Token token;
    std::unique_ptr<InstructionList> instructionList;
    CaseC(Token token, std::unique_ptr<InstructionList> instructionList) : 
        token(token), instructionList(std::move(instructionList)) {}

    std::string print(int identLevel) { 
        return std::string("Case C") + "\n" + 
            ident(identLevel) + "Token: " + getTokenInfo() + "\n" + 
            ident(identLevel) + "Instruction list: " + 
                instructionList->print(identLevel + 1);
    }
};