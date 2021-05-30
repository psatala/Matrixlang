#include "../../headers/LanguageObjects/CaseGo.h"

CaseGo::CaseGo(std::unique_ptr<Expression> expression,
    std::unique_ptr<InstructionList> instructionList) : 
    expression(std::move(expression)), 
    instructionList(std::move(instructionList)) {}

std::string CaseGo::print(int identLevel) { 
    return std::string("Case Go") + "\n" + 
        ident(identLevel) + "Expression: " + 
            expression->print(identLevel + 1) +
        ident(identLevel) + "Instruction list: " + 
            instructionList->print(identLevel + 1);
}

// CaseGo::~CaseGo() {}