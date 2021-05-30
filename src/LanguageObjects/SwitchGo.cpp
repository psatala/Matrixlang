#include "../../headers/LanguageObjects/SwitchGo.h"

SwitchGo::SwitchGo() {}

std::string SwitchGo::print(int identLevel) { 
    std::string toPrintString = std::string("Switch Go") + "\n";
    for(int i = 0; i < caseGoInstructions.size(); ++i) {
        toPrintString += ident(identLevel) + "Case Go no. " + 
            std::to_string(i) + ": " + 
            caseGoInstructions[i]->print(identLevel + 1);
    }

    toPrintString += ident(identLevel) + "Default: ";
    if(defaultInstruction) {
        toPrintString += defaultInstruction->print(identLevel + 1);
    }
    
    return toPrintString;
}

// SwitchGo::~SwitchGo() {}