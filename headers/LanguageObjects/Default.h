#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "InstructionList.h"

class Default {
public:
    std::unique_ptr<InstructionList> instructionList;
    Default(std::unique_ptr<InstructionList> instructionList) : 
        instructionList(std::move(instructionList)) {}

    std::string print(int identLevel) {
        return std::string("Default") + "\n" + 
            ident(identLevel) + "Instruction list: " + 
                instructionList->print(identLevel + 1);
    }
};