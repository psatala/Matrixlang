#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "../Token.h"
#include "InstructionList.h"

class CaseC {

    std::string getTokenInfo();

public:
    Token token;
    std::unique_ptr<InstructionList> instructionList;
    CaseC(Token token, std::unique_ptr<InstructionList> instructionList);

    std::string print(int identLevel);
    
    // ~CaseC();
};