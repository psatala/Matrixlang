#include "../../headers/ExecutionObjects/Execution.h"
#include "../../headers/LanguageObjects/Expressions/VariableExpression.h"

namespace VariableManagement{

    std::unique_ptr<Variable> createVariable(Type* type, 
        ScopeManager* scopeManager) {

        if(SimpleType* simpleType = dynamic_cast<SimpleType*>(type))
            return std::make_unique<SimpleVariable>(SimpleVariable(simpleType));
        if(VectorType* vectorType = dynamic_cast<VectorType*>(type))
            return std::make_unique<VectorVariable>(VectorVariable(vectorType, 
                scopeManager));
        if(MatrixType* matrixType = dynamic_cast<MatrixType*>(type))
            return std::make_unique<MatrixVariable>(MatrixVariable(matrixType, 
                scopeManager));
        return std::unique_ptr<Variable>(nullptr);
    }


    std::unique_ptr<Variable> copyVariable(Variable* variable) {
        if(SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
            (variable))
            return std::make_unique<SimpleVariable>(SimpleVariable
                (simpleVariable));
        if(VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>
            (variable))
            return std::make_unique<VectorVariable>(VectorVariable
                (vectorVariable));
        if(MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>
            (variable))
            return std::make_unique<MatrixVariable>(MatrixVariable
                (matrixVariable));
        return std::unique_ptr<Variable>(nullptr);
    }


    void copyVariableContent(Variable* changedVariable, 
        Variable* targetVariable) {
        
        if(VECTOR == changedVariable->type) {
            VectorVariable* changedVectorVariable = 
                dynamic_cast<VectorVariable*>(changedVariable);
            VectorVariable* targetVectorVariable = dynamic_cast<VectorVariable*>
                (targetVariable);
            changedVectorVariable->length = targetVectorVariable->length;
            changedVectorVariable->values.clear();
            for(int i = 0; i < changedVectorVariable->length; ++i) {
                changedVectorVariable->values.push_back(std::move(
                    copyVariable(targetVectorVariable->values[i].get())));
            }
            return;
        }

        if(MATRIX == changedVariable->type) {
            MatrixVariable* changedMatrixVariable = 
                dynamic_cast<MatrixVariable*>(changedVariable);
            MatrixVariable* targetMatrixVariable = dynamic_cast<MatrixVariable*>
                (targetVariable);
            changedMatrixVariable->firstLength = 
                targetMatrixVariable->firstLength;
            changedMatrixVariable->secondLength = 
                targetMatrixVariable->secondLength;
            changedMatrixVariable->values.clear();
            for(unsigned int i = 0; i < changedMatrixVariable->firstLength; 
                ++i) {
                std::vector<std::unique_ptr<Variable>> innerValues;
                for(unsigned int j = 0; j < changedMatrixVariable->secondLength; 
                    ++j) {
                    
                    innerValues.push_back(std::move(copyVariable((
                        targetMatrixVariable->values[i][j]).get())));
                }
                changedMatrixVariable->values.push_back(std::move(innerValues));
            }
            return;
        }
        SimpleVariable* changedSimpleVariable = dynamic_cast<SimpleVariable*>
            (changedVariable);
        SimpleVariable* targetSimpleVariable = dynamic_cast<SimpleVariable*>
            (targetVariable);
        changedSimpleVariable->value = targetSimpleVariable->value;
    }


    bool areOfSameType(Variable* firstVariable, 
        Variable* secondVariable) {
        
        if(firstVariable->type != secondVariable->type)
            return false;
        
        if(VECTOR == firstVariable->type) {
            VectorVariable* firstVectorVariable = dynamic_cast<VectorVariable*>
                (firstVariable);
            VectorVariable* secondVectorVariable = dynamic_cast<VectorVariable*>
                (secondVariable);
            if(firstVectorVariable->length != secondVectorVariable->length)
                return false;
            return areOfSameType((firstVectorVariable->values[0]).get(), 
                (secondVectorVariable->values[0]).get());
        }

        if(MATRIX == firstVariable->type) {
            MatrixVariable* firstMatrixVariable = dynamic_cast<MatrixVariable*>
                (firstVariable);
            MatrixVariable* secondMatrixVariable = dynamic_cast<MatrixVariable*>
                (secondVariable);
            if(firstMatrixVariable->firstLength != 
                secondMatrixVariable->firstLength)
                return false;
            if(firstMatrixVariable->secondLength != 
                secondMatrixVariable->secondLength)
                return false;
            return areOfSameType((firstMatrixVariable->values[0][0]).get(), 
                (secondMatrixVariable->values[0][0]).get());
        }

        return true; // int, float, string, void
    }


    std::unique_ptr<Variable> createLogicalVariable(bool isTrue) {
        return std::make_unique<SimpleVariable>
            (SimpleVariable(static_cast<int>(isTrue)));
    }


    std::unique_ptr<Variable> variablePtrToUniquePtr(Variable* 
        variable) {

        SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
            (variable);
        if(simpleVariable)
            return std::make_unique<SimpleVariable>(std::move(*simpleVariable));

        VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>
            (variable);
        if(vectorVariable)
            return std::make_unique<VectorVariable>(std::move(*vectorVariable));

        MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>
            (variable);
        if(matrixVariable)
            return std::make_unique<MatrixVariable>(std::move(*matrixVariable));

        return std::unique_ptr<Variable>(nullptr);
    }

    void incrementValue(SimpleVariable* simpleVariable, 
        Operator* incrementalOperator) {

        if(INT == simpleVariable->type) {
            if(incrementalOperator->type == INCREMENT) {
                simpleVariable->value = 
                    std::get<int>(simpleVariable->value) + 1;
                return;
            }
            simpleVariable->value = std::get<int>(simpleVariable->value) - 1;
            return;
        }

        if(incrementalOperator->type == INCREMENT) {
            simpleVariable->value = std::get<float>(simpleVariable->value) + 1;
            return;
        }
        simpleVariable->value = std::get<float>(simpleVariable->value) - 1;
        return;
    }

    std::string getStringFromVariable(Variable* variable) {
        SimpleVariable* simpleVariable = 
            dynamic_cast<SimpleVariable*>(variable);
        if(!simpleVariable)
            throw std::string("Cannot get string value for Vector or Matrix");

        if(INT == simpleVariable->type)
            return std::to_string(std::get<int>(simpleVariable->value));
        if(FLOAT == simpleVariable->type)
            return std::to_string(std::get<float>(simpleVariable->value));
        return std::get<std::string>(simpleVariable->value);
    }

    unsigned int getUnsignedIntValueFromVariable(Variable* variable) {
        SimpleVariable* simpleVariable = 
            dynamic_cast<SimpleVariable*>(variable);
        if(!simpleVariable)
            throw std::string("Cannot get unsigned int value for "
                "Vector or Matrix");

        if(INT != simpleVariable->type)
            throw std::string("Cannot get unsigned int value for "
                "float or string");

        int value = std::get<int>(simpleVariable->value);
        if(value < 0)
            throw std::string("Value must not be negative");
        
        return static_cast<unsigned int>(value);
    }

    bool isVariableMatchingLiteral(Variable* variable, Token literal) {
        if(SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
            (variable)) {
            
            if(INT == simpleVariable->type && INT_NUMBER == literal.type) {
                if(std::get<int>(simpleVariable->value) == 
                    std::get<int>(literal.value))
                    return true;
                return false;
            }
            if(FLOAT == simpleVariable->type && FLOAT_NUMBER == literal.type) {
                if(std::get<float>(simpleVariable->value) == 
                    std::get<float>(literal.value))
                    return true;
                return false;
            }
            if(STRING == simpleVariable->type && 
                STRING_CONSTANT == literal.type) {
                if(std::get<std::string>(simpleVariable->value) == 
                    std::get<std::string>(literal.value))
                    return true;
                return false;
            }

            return false; // type mismatch
        }

        // vector or matrix
        throw std::string("Cannot match to a variable of type vector or "
            "matrix");
    }



    void addParameterListVariables(Type* type, Variable* variable, 
        ScopeManager* scopeManager) {
        
        VectorType* vectorType = dynamic_cast<VectorType*>(type);
        VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>
            (variable);
        if(vectorType && vectorVariable) {
            
            // recursive call
            addParameterListVariables(vectorType->type.get(), 
                vectorVariable->values[0].get(), scopeManager);
            
            VariableExpression* variableExpression = dynamic_cast
                <VariableExpression*>(vectorType->expression.get());

            if(!variableExpression)
                return;
            if(scopeManager->getVariable(variableExpression->identifier, false))
                return;
            
            scopeManager->addLocalVariable(variableExpression->identifier, 
                std::make_unique<SimpleVariable>(SimpleVariable(
                    static_cast<int>(vectorVariable->length))));

        }

        MatrixType* matrixType = dynamic_cast<MatrixType*>(type);
        MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>
            (variable);
        if(matrixType && matrixVariable) {
            
            // recursive call
            addParameterListVariables(matrixType->type.get(), 
                matrixVariable->values[0][0].get(), scopeManager);
            
            VariableExpression* firstVariableExpression = dynamic_cast
                <VariableExpression*>(matrixType->firstExpression.get());

            if(firstVariableExpression) {
                if(!scopeManager->getVariable(firstVariableExpression->
                    identifier, false)) {
                    
                    scopeManager->addLocalVariable(firstVariableExpression->
                        identifier, std::make_unique<SimpleVariable>(
                        SimpleVariable(
                        static_cast<int>(matrixVariable->firstLength))));
                }
            }
            
            VariableExpression* secondVariableExpression = dynamic_cast
                <VariableExpression*>(matrixType->secondExpression.get());

            if(secondVariableExpression) {
                if(!scopeManager->getVariable(secondVariableExpression->
                    identifier, false)) {
                    
                    scopeManager->addLocalVariable(secondVariableExpression->
                        identifier, std::make_unique<SimpleVariable>(
                        SimpleVariable(
                        static_cast<int>(matrixVariable->secondLength))));
                }
            }

        }
    }
}
