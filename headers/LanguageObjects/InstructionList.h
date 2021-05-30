#pragma once

#include <memory>
#include <vector>

#include "../LanguageObjects.h"
#include "Instruction.h"

class InstructionList {
public:
    std::vector<std::unique_ptr<Instruction>> instructions;
    InstructionList();

    std::string print(int identLevel);

    // ~InstructionList();
};