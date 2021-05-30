#include "../../headers/LanguageObjects/Default.h"

Default::Default(std::unique_ptr<InstructionList> instructionList) : 
    instructionList(std::move(instructionList)) {}

std::string Default::print(int identLevel) {
    return std::string("Default") + "\n" + 
        ident(identLevel) + "Instruction list: " + 
            instructionList->print(identLevel + 1);
}

// Default::~Default() {}