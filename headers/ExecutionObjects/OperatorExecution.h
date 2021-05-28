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



    std::unique_ptr<Variable> logicalAnd(Variable* firstVariable, 
        Variable* secondVariable) {

        return VariableManagement::createLogicalVariable(
            firstVariable->getLogicalValue() &&
            secondVariable->getLogicalValue()
        );
    }

    std::unique_ptr<Variable> logicalOr(Variable* firstVariable, 
        Variable* secondVariable) {

        return VariableManagement::createLogicalVariable(
            firstVariable->getLogicalValue() ||
            secondVariable->getLogicalValue()
        );
    }

    std::unique_ptr<Variable> logicalNot(Variable* firstVariable) {

        return VariableManagement::createLogicalVariable(
            !firstVariable->getLogicalValue()
        );
    }
    

    std::unique_ptr<Variable> unaryPlus(Variable* firstVariable) {
        
        if(SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            if(INT == simpleVariable->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<int>(simpleVariable->value)
                ));
            }

            if(FLOAT == simpleVariable->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    std::get<float>(simpleVariable->value)
                ));
            }

        }

        // vector, matrix, string
        throw std::string("Unary plus operator not supported for those "
            "types");
    }

    std::unique_ptr<Variable> unaryMinus(Variable* firstVariable) {
        
        if(SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
            (firstVariable)) {
            
            if(INT == simpleVariable->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    -std::get<int>(simpleVariable->value)
                ));
            }

            if(FLOAT == simpleVariable->type) {
                return std::make_unique<SimpleVariable>(SimpleVariable(
                    -std::get<float>(simpleVariable->value)
                ));
            }

        }

        // vector, matrix, string
        throw std::string("Unary minus operator not supported for those "
            "types");
    }

    std::unique_ptr<Variable> vectorIndexAccess(Variable* firstVariable, 
        unsigned int position) {

        if(VECTOR != firstVariable->type)
            throw std::string("Vector index access can only be applied to a "
                "Vector");
        
        VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>
            (firstVariable);
        
        return VariableManagement::copyVariable(
            vectorVariable->values[position].get());
    }


    std::unique_ptr<Variable> matrixIndexAccess(Variable* firstVariable, 
        unsigned int firstPosition, unsigned int secondPosition) {

        if(MATRIX != firstVariable->type)
            throw std::string("Matrix index access can only be applied to a "
                "Matrix");
        
        MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>
            (firstVariable);
        
        return VariableManagement::copyVariable(
            matrixVariable->values[firstPosition][secondPosition].get());
    }

}

