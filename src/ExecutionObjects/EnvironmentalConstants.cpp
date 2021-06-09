#include "../../headers/ExecutionObjects/EnvironmentalConstants.h"
#include "../../headers/ExecutionObjects/ScopeManager.h"
#include "../../headers/ExecutionObjects/SimpleVariable.h"

namespace EnvironmentalConstants {
    void addAllEnvironmentalConstants(ScopeManager* scopeManager) {
        
        scopeManager->addGlobalVariable("INT_MIN", 
            std::make_unique<SimpleVariable>(SimpleVariable
            (std::numeric_limits<int>::min())));

        scopeManager->addGlobalVariable("INT_MAX", 
            std::make_unique<SimpleVariable>(SimpleVariable
            (std::numeric_limits<int>::max())));

        scopeManager->addGlobalVariable("FLOAT_MIN", 
            std::make_unique<SimpleVariable>(SimpleVariable
            (std::numeric_limits<float>::min())));

        scopeManager->addGlobalVariable("FLOAT_MAX", 
            std::make_unique<SimpleVariable>(SimpleVariable
            (std::numeric_limits<float>::max())));
        
        scopeManager->addGlobalVariable("PI", 
            std::make_unique<SimpleVariable>(SimpleVariable
            (static_cast<float>(std::atan(1) * 4))));
    }
}