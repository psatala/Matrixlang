#pragma once

#include <vector>
#include <memory>

#include "Variable.h"
#include "../LanguageObjects/VectorType.h"

// namespace definition in Execution.h
namespace VariableManagement {
    std::unique_ptr<Variable> createVariable(Type* type, 
        ScopeManager* scopeManager);
    std::unique_ptr<Variable> copyVariable(Variable* variable);
}


class VectorVariable : public Variable {
public:
    std::vector<std::unique_ptr<Variable>> values;
    unsigned int length;

    VectorVariable(VectorType* vectorType, ScopeManager* scopeManager) {
        type = VECTOR;
        length = vectorType->getExpressionPosition(scopeManager);
        for(unsigned int i = 0; i < length; ++i) {
            values.push_back(std::move(VariableManagement::
                createVariable(vectorType->type.get(), scopeManager)));
        }
    }

    VectorVariable(const VectorVariable* vectorVariable) {
        type = vectorVariable->type;
        length = vectorVariable->length;
        for(unsigned int i = 0; i < length; ++i) {
            values.push_back(std::move(VariableManagement::
                copyVariable(vectorVariable->values[i].get())));
        }
    }


    bool getLogicalValue() override { return true; }
};