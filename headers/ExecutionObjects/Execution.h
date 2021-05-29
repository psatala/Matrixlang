#pragma once

#include <memory>
#include "SimpleVariable.h"
#include "VectorVariable.h"
#include "MatrixVariable.h"

namespace VariableManagement{

    std::unique_ptr<Variable> createVariable(Type* type);
    std::unique_ptr<Variable> copyVariable(Variable* variable);
    void copyVariableContent(Variable* changedVariable, 
        Variable* targetVariable);
    bool areOfSameType(Variable* firstVariable, Variable* secondVariable);
    std::unique_ptr<Variable> createLogicalVariable(bool isTrue);
    std::unique_ptr<Variable> variablePtrToUniquePtr(Variable* variable);
}
