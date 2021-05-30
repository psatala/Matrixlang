#include "../../headers/LanguageObjects/SwitchC.h"

SwitchC::SwitchC() {}

std::string SwitchC::print(int identLevel) { 
    std::string toPrintString = std::string("Switch C") + "\n";
    
    toPrintString += ident(identLevel) + "Expression: " + 
        postExpression->print(identLevel + 1);
    
    for(int i = 0; i < caseCInstructions.size(); ++i) {
        toPrintString += ident(identLevel) + "Case C no. " + 
            std::to_string(i) + ": " + 
            caseCInstructions[i]->print(identLevel + 1);
    }

    toPrintString += ident(identLevel) + "Default: ";
    if(defaultInstruction) {
        toPrintString += defaultInstruction->print(identLevel + 1);
    }
    
    return toPrintString;
}

// SwitchC::~SwitchC() {}