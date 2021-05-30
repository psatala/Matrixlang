#include "../../headers/LanguageObjects/InstructionList.h"

InstructionList::InstructionList() {
    instructions.clear();
}

std::string InstructionList::print(int identLevel) {
    std::string toPrintString = std::string("Instruction list") + "\n";
    for(int i = 0; i < instructions.size(); ++i) {
        toPrintString += ident(identLevel) + "Instruction: " + 
            instructions[i]->print(identLevel + 1);
    }
    return toPrintString;
}

// InstructionList::~InstructionList() {}