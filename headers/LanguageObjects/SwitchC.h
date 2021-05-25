#pragma once

#include <memory>
#include <vector>

#include "../LanguageObjects.h"
#include "Expression.h"
#include "Switch.h"
#include "CaseC.h"
#include "Default.h"

class SwitchC : public Switch {
public:
    std::unique_ptr<Expression> postExpression;
    std::vector<std::unique_ptr<CaseC>> caseCInstructions;
    std::unique_ptr<Default> defaultInstruction;
    SwitchC() {}

    std::string print(int identLevel) override { 
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
};