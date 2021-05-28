#pragma once

#include <memory>

#include "Variable.h"
#include "Execution.h"

namespace VariableOperators {
    
    std::unique_ptr<Variable> add(Variable* firstVariable, 
        Variable* secondVariable) {

        if(!VariableManagement::areOfSameType(firstVariable, secondVariable))
            throw std::string("Cannot perform addition: variables are not of "
                "the same type");

        if(SimpleVariable* simpleVariable1 = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            SimpleVariable* simpleVariable2 = dynamic_cast<SimpleVariable*>
                (secondVariable);

            if(INT == simpleVariable1->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<int>(simpleVariable1->value) + 
                    std::get<int>(simpleVariable2->value)
                ));
            }

            if(FLOAT == simpleVariable1->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<float>(simpleVariable1->value) + 
                    std::get<float>(simpleVariable2->value)
                ));
            }

            // string
            return std::make_unique<SimpleVariable>(SimpleVariable(
                std::get<std::string>(simpleVariable1->value) + 
                std::get<std::string>(simpleVariable2->value)
            ));
        }

        // vector and matrix
        throw std::string("Addition operator not supported for those types");
    }
}

