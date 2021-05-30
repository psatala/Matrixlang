#include "../../headers/LanguageObjects/Block.h"

Block::Block(std::unique_ptr<InstructionList> instructionList) : 
    instructionList(std::move(instructionList)) {}

std::string Block::print(int identLevel) {
    return std::string("Block") + "\n" + 
        ident(identLevel) + "Instruction List: " + 
        instructionList->print(identLevel + 1);
}

// Block::~Block() {}