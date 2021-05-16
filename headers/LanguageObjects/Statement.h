#pragma once

#include "../LanguageObjects.h"
#include "InstructionList.h"
#include "Instruction.h"

class Statement {
public:
    std::unique_ptr<InstructionList> instructionList;
    Statement(std::unique_ptr<InstructionList> instructionList) : 
        instructionList(std::move(instructionList)) {}
    // Statement(std::unique_ptr<Instruction> instruction) {
    //     instructionList->instructions.size();
    //     instructionList->instructions.push_back(std::move(instruction));
    // }
    
    std::string print(int identLevel) {
        std::string toPrintString = std::string("Statement") + "\n";
        if(instructionList)
            toPrintString += ident(identLevel) + "Instruction List: " + 
                instructionList->print(identLevel + 1);
        return toPrintString;
    }
};