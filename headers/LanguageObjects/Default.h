#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "InstructionList.h"

class Default {
public:
    std::unique_ptr<InstructionList> instructionList;
    Default(std::unique_ptr<InstructionList> instructionList);

    std::string print(int identLevel);

    // ~Default();
};