#pragma once

#include "../LanguageObjects.h"
#include "Instruction.h"
#include "Block.h"

class Statement {
public:
    std::variant<std::unique_ptr<Instruction>, std::unique_ptr<Block>> 
        instructions;

    Statement(std::variant<std::unique_ptr<Instruction>, 
        std::unique_ptr<Block>> instructions) : 
        instructions(std::move(instructions)) {}

    std::string print(int identLevel) {
        std::string toPrintString = std::string("Statement") + "\n";
        // instructions
        if(std::unique_ptr<Instruction>* instruction = 
            std::get_if<std::unique_ptr<Instruction>>
            (&instructions)) {

            return toPrintString + ident(identLevel) + "Instruction: " + 
                (*instruction)->print(identLevel + 1);
        }

        // block
        return toPrintString + ident(identLevel) + "Block: " + 
            std::get<std::unique_ptr<Block>>
            (instructions)->print(identLevel + 1);

    }

};
