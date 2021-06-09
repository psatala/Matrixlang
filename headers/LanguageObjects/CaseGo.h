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
        std::unique_ptr<InstructionList> instructionList) : 
        expression(std::move(expression)), 
        instructionList(std::move(instructionList)) {}

    std::string print(int identLevel) { 
        return std::string("Case Go") + "\n" + 
            ident(identLevel) + "Expression: " + 
                expression->print(identLevel + 1) +
            ident(identLevel) + "Instruction list: " + 
                instructionList->print(identLevel + 1);
    }

    std::unique_ptr<Variable> execute(ScopeManager* scopeManager) {
        scopeManager->addBlock();
        std::unique_ptr<Variable> variable = 
            instructionList->execute(scopeManager);
        scopeManager->endBlock();
        return std::move(variable);
    }
    
};