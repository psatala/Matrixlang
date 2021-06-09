#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "InstructionList.h"

class Block {
public:
    std::unique_ptr<InstructionList> instructionList;
    Block(std::unique_ptr<InstructionList> instructionList) : 
        instructionList(std::move(instructionList)) {}
    
    std::string print(int identLevel) {
        return std::string("Block") + "\n" + 
            ident(identLevel) + "Instruction List: " + 
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
