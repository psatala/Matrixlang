#pragma once

#include <memory>
#include <functional>

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


    std::unique_ptr<Variable> subtract(Variable* firstVariable, 
        Variable* secondVariable) {

        if(!VariableManagement::areOfSameType(firstVariable, secondVariable))
            throw std::string("Cannot perform subtraction: variables are not of"
                " the same type");

        if(SimpleVariable* simpleVariable1 = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            SimpleVariable* simpleVariable2 = dynamic_cast<SimpleVariable*>
                (secondVariable);

            if(INT == simpleVariable1->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<int>(simpleVariable1->value) - 
                    std::get<int>(simpleVariable2->value)
                ));
            }

            if(FLOAT == simpleVariable1->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<float>(simpleVariable1->value) - 
                    std::get<float>(simpleVariable2->value)
                ));
            }

        }

        // vector, matrix, string
        throw std::string("Subtraction operator not supported for those types");
    }


    std::unique_ptr<Variable> multiply(Variable* firstVariable, 
        Variable* secondVariable) {

        if(!VariableManagement::areOfSameType(firstVariable, secondVariable))
            throw std::string("Cannot perform multiplication: variables are not"
                " of the same type");

        if(SimpleVariable* simpleVariable1 = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            SimpleVariable* simpleVariable2 = dynamic_cast<SimpleVariable*>
                (secondVariable);

            if(INT == simpleVariable1->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<int>(simpleVariable1->value) * 
                    std::get<int>(simpleVariable2->value)
                ));
            }

            if(FLOAT == simpleVariable1->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<float>(simpleVariable1->value) * 
                    std::get<float>(simpleVariable2->value)
                ));
            }

        }

        // vector, matrix, string
        throw std::string("Multiplication operator not supported for those "
            "types");
    }


    std::unique_ptr<Variable> divide(Variable* firstVariable, 
        Variable* secondVariable) {

        if(!VariableManagement::areOfSameType(firstVariable, secondVariable))
            throw std::string("Cannot perform division: variables are not"
                " of the same type");

        if(SimpleVariable* simpleVariable1 = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            SimpleVariable* simpleVariable2 = dynamic_cast<SimpleVariable*>
                (secondVariable);

            if(INT == simpleVariable1->type) {
                if(0 == std::get<int>(simpleVariable2->value))
                    throw std::string("Cannot divide by zero");

                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<int>(simpleVariable1->value) / 
                    std::get<int>(simpleVariable2->value)
                ));
            }

            if(FLOAT == simpleVariable1->type) {
                if(0 == std::get<float>(simpleVariable2->value))
                    throw std::string("Cannot divide by zero");

                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<float>(simpleVariable1->value) / 
                    std::get<float>(simpleVariable2->value)
                ));
            }

        }

        // vector, matrix, string
        throw std::string("Division operator not supported for those "
            "types");
    }


    std::unique_ptr<Variable> modulo(Variable* firstVariable, 
        Variable* secondVariable) {

        if(!VariableManagement::areOfSameType(firstVariable, secondVariable))
            throw std::string("Cannot perform modulo: variables are not"
                " of the same type");

        if(SimpleVariable* simpleVariable1 = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            SimpleVariable* simpleVariable2 = dynamic_cast<SimpleVariable*>
                (secondVariable);

            if(INT == simpleVariable1->type) {
                if(0 == std::get<int>(simpleVariable2->value))
                    throw std::string("Cannot divide (modulo) by zero");

                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<int>(simpleVariable1->value) % 
                    std::get<int>(simpleVariable2->value)
                ));
            }
        }

        // vector, matrix, string, float
        throw std::string("Modulo operator not supported for those "
            "types");
    }




    std::unique_ptr<Variable> comparisonOperator(Variable* firstVariable, 
        Variable* secondVariable, std::function<bool(int, int)> intComparer, 
        std::function<bool(float, float)> floatComparer, 
        std::function<bool(std::string, std::string)> stringComparer,
        std::string operatorName) {

        if(!VariableManagement::areOfSameType(firstVariable, secondVariable))
            throw std::string("Cannot perform comparison (") + operatorName + 
                std::string("): variables are not of the same type");

        if(SimpleVariable* simpleVariable1 = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            SimpleVariable* simpleVariable2 = dynamic_cast<SimpleVariable*>
                (secondVariable);

            if(INT == simpleVariable1->type) {
                return VariableManagement::createLogicalVariable(intComparer(
                    std::get<int>(simpleVariable1->value), 
                    std::get<int>(simpleVariable2->value)
                ));
            }
            
            if(FLOAT == simpleVariable1->type) {
                return VariableManagement::createLogicalVariable(floatComparer(
                    std::get<float>(simpleVariable1->value), 
                    std::get<float>(simpleVariable2->value)
                ));
            }

            if(STRING == simpleVariable1->type) {
                return VariableManagement::createLogicalVariable(stringComparer(
                    std::get<std::string>(simpleVariable1->value), 
                    std::get<std::string>(simpleVariable2->value)
                ));
            }

        }

        // vector, matrix
        throw std::string("Comparison operator (") + operatorName + 
            std::string(") not supported for those types");
    }



    std::unique_ptr<Variable> lessThan(Variable* firstVariable, 
        Variable* secondVariable) {

        return comparisonOperator(firstVariable, secondVariable, std::less<>(), 
            std::less<>(), std::less<>(), std::string("less than"));
    }

    std::unique_ptr<Variable> lessEqual(Variable* firstVariable, 
        Variable* secondVariable) {

        return comparisonOperator(firstVariable, secondVariable, 
            std::less_equal<>(), std::less_equal<>(), std::less_equal<>(), 
            std::string("less equal"));
    }

    std::unique_ptr<Variable> moreThan(Variable* firstVariable, 
        Variable* secondVariable) {

        return comparisonOperator(firstVariable, secondVariable, 
            std::greater<>(), std::greater<>(), std::greater<>(), 
            std::string("more than"));
    }

    std::unique_ptr<Variable> moreEqual(Variable* firstVariable, 
        Variable* secondVariable) {

        return comparisonOperator(firstVariable, secondVariable, 
            std::greater_equal<>(), std::greater_equal<>(), 
            std::greater_equal<>(), std::string("more equal"));
    }

    std::unique_ptr<Variable> equal(Variable* firstVariable, 
        Variable* secondVariable) {

        return comparisonOperator(firstVariable, secondVariable, 
            std::equal_to<>(), std::equal_to<>(), std::equal_to<>(), 
            std::string("equal"));
    }


    std::unique_ptr<Variable> notEqual(Variable* firstVariable, 
        Variable* secondVariable) {

        return comparisonOperator(firstVariable, secondVariable, 
            std::not_equal_to<>(), std::not_equal_to<>(), std::not_equal_to<>(), 
            std::string("not equal"));
    }



    std::unique_ptr<Variable> andOp(Variable* firstVariable, 
        Variable* secondVariable) {

        return VariableManagement::createLogicalVariable(
            firstVariable->getLogicalValue() &&
            secondVariable->getLogicalValue()
        );
    }

    std::unique_ptr<Variable> orOp(Variable* firstVariable, 
        Variable* secondVariable) {

        return VariableManagement::createLogicalVariable(
            firstVariable->getLogicalValue() ||
            secondVariable->getLogicalValue()
        );
    }

}

