#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Expressions/Expression.h"
#include "InstructionList.h"

class CaseGo {
public:
    std::unique_ptr<Expression> expression;
    std::unique_ptr<InstructionList> instructionList;
    CaseGo(std::unique_ptr<Expression> expression,
        std::unique_ptr<InstructionList> instructionList);

    std::string print(int identLevel);

    // ~CaseGo();
};