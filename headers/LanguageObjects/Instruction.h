#pragma once

#include <memory>
#include <variant>

#include "../LanguageObjects.h"
#include "Expressions/Expression.h"
#include "If.h"
#include "Switch.h"
#include "For.h"
#include "Return.h"
#include "Declaration.h"

class Block;


class Instruction {
public:
    std::variant<
        std::unique_ptr<Expression>, 
        std::unique_ptr<If>, 
        std::unique_ptr<Switch>, 
        std::unique_ptr<For>,
        std::unique_ptr<Return>,
        std::unique_ptr<Declaration>, 
        std::unique_ptr<Block>
        >
            instructionVariant;
    
    Instruction(std::variant<
        std::unique_ptr<Expression>, 
        std::unique_ptr<If>, 
        std::unique_ptr<Switch>, 
        std::unique_ptr<For>,
        std::unique_ptr<Return>,
        std::unique_ptr<Declaration>, 
        std::unique_ptr<Block>
        >
            instructionVariant);

    std::string print(int identLevel);

    std::unique_ptr<Variable> execute(ScopeManager* scopeManager);

};
