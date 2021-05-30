#pragma once

#include <memory>
#include <vector>

#include "../LanguageObjects.h"
#include "Switch.h"
#include "CaseGo.h"
#include "Default.h"

class SwitchGo : public Switch {
public:
    std::vector<std::unique_ptr<CaseGo>> caseGoInstructions;
    std::unique_ptr<Default> defaultInstruction;
    SwitchGo() {}

    std::string print(int identLevel) override { 
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

    std::unique_ptr<Variable> execute(ScopeManager* scopeManager) override {
        for(unsigned int i = 0; i < caseGoInstructions.size(); ++i) {
            if(caseGoInstructions[i]->expression->value(scopeManager)->
                getLogicalValue()) {
                
                return caseGoInstructions[i]->execute(scopeManager);
            }
        }
        if(defaultInstruction)
            defaultInstruction->execute(scopeManager);
        return std::unique_ptr<Variable>(nullptr);
    }

};