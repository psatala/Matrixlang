#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "InstructionList.h"

class Block {
public:
    std::unique_ptr<InstructionList> instructionList;
    Block(std::unique_ptr<InstructionList> instructionList);
    
    std::string print(int identLevel);

    // ~Block();
};