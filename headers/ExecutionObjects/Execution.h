#pragma once

#include <memory>
#include "SimpleVariable.h"
#include "VectorVariable.h"
#include "MatrixVariable.h"
#include "VoidVariable.h"
#include "../LanguageObjects/Operator.h"

namespace VariableManagement{

    std::unique_ptr<Variable> createVariable(Type* type, 
        ScopeManager* scopeManager);
    std::unique_ptr<Variable> copyVariable(Variable* variable);
    void copyVariableContent(Variable* changedVariable, 
        Variable* targetVariable);
    bool areOfSameType(Variable* firstVariable, Variable* secondVariable);
    std::unique_ptr<Variable> createLogicalVariable(bool isTrue);
    std::unique_ptr<Variable> variablePtrToUniquePtr(Variable* variable);
    void incrementValue(SimpleVariable* simpleVariable, 
        Operator* incrementalOperator);
    std::string getStringFromVariable(Variable* variable);
    unsigned int getUnsignedIntValueFromVariable(Variable* variable);
    bool isVariableMatchingLiteral(Variable* variable, Token literal);
}
