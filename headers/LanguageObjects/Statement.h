#pragma once

#include "../LanguageObjects.h"
#include "Instruction.h"
#include "Block.h"

class Statement {
public:
    std::variant<std::unique_ptr<Instruction>, std::unique_ptr<Block>> 
        instructions;
    Statement(std::variant<std::unique_ptr<Instruction>, std::unique_ptr<Block>> 
        instructions);
 
    std::string print(int identLevel);

    // ~Statement();
};