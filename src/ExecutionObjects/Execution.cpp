#include "../../headers/ExecutionObjects/Execution.h"

namespace VariableManagement{

    std::unique_ptr<Variable> createVariable(Type* type) {
        if(SimpleType* simpleType = dynamic_cast<SimpleType*>(type))
            return std::make_unique<SimpleVariable>(SimpleVariable(simpleType));
        if(VectorType* vectorType = dynamic_cast<VectorType*>(type))
            return std::make_unique<VectorVariable>(VectorVariable(vectorType));
        if(MatrixType* matrixType = dynamic_cast<MatrixType*>(type))
            return std::make_unique<MatrixVariable>(MatrixVariable(matrixType));
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
            return areOfSameType((firstVectorVariable->values[0]).get(), 
                (secondVectorVariable->values[0]).get());
        }

        if(MATRIX == firstVariable->type) {
            MatrixVariable* firstMatrixVariable = dynamic_cast<MatrixVariable*>
                (firstVariable);
            MatrixVariable* secondMatrixVariable = dynamic_cast<MatrixVariable*>
                (secondVariable);
            return areOfSameType((firstMatrixVariable->values[0][0]).get(), 
                (secondMatrixVariable->values[0][0]).get());
        }

        return true; // int, float, string
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
}
