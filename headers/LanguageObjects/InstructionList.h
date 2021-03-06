#pragma once

#include <memory>
#include <vector>

#include "../LanguageObjects.h"
#include "Instruction.h"

class InstructionList {
public:
    std::vector<std::unique_ptr<Instruction>> instructions;
    InstructionList() {}

    std::string print(int identLevel) {
        std::string toPrintString = std::string("Instruction list") + "\n";
        for(int i = 0; i < instructions.size(); ++i) {
            toPrintString += ident(identLevel) + "Instruction: " + 
                instructions[i]->print(identLevel + 1);
        }
        return toPrintString;
    }

    std::unique_ptr<Variable> execute(ScopeManager* scopeManager) {
        for(int i = 0; i < instructions.size(); ++i) {
            if(std::unique_ptr<Variable> variable = 
                instructions[i]->execute(scopeManager))
                return std::move(variable);
        }
        return std::unique_ptr<Variable>(nullptr);
    }
};