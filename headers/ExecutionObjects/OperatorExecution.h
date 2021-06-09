#pragma once

#include <memory>
#include <functional>

#include "Variable.h"
#include "Execution.h"

namespace VariableOperators {
    
    std::unique_ptr<Variable> add(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> subtract(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> multiply(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> divide(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> modulo(Variable* firstVariable, 
        Variable* secondVariable);


    std::unique_ptr<Variable> comparisonOperator(Variable* firstVariable, 
        Variable* secondVariable, std::function<bool(int, int)> intComparer, 
        std::function<bool(float, float)> floatComparer, 
        std::function<bool(std::string, std::string)> stringComparer,
        std::string operatorName);

    std::unique_ptr<Variable> lessThan(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> lessEqual(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> moreThan(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> moreEqual(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> equal(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> notEqual(Variable* firstVariable, 
        Variable* secondVariable);



    std::unique_ptr<Variable> logicalAnd(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> logicalOr(Variable* firstVariable, 
        Variable* secondVariable);
    std::unique_ptr<Variable> logicalNot(Variable* firstVariable);


    std::unique_ptr<Variable> unaryPlus(Variable* firstVariable);
    std::unique_ptr<Variable> unaryMinus(Variable* firstVariable);


    std::unique_ptr<Variable> vectorIndexAccess(Variable* firstVariable, 
        unsigned int position);
    std::unique_ptr<Variable> matrixIndexAccess(Variable* firstVariable, 
        unsigned int firstPosition, unsigned int secondPosition);
}

