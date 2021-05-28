#pragma once

#include <memory>
#include "SimpleVariable.h"
#include "VectorVariable.h"
#include "MatrixVariable.h"

namespace VariableManagement{

    inline std::unique_ptr<Variable> createVariable(Type* type) {
        if(SimpleType* simpleType = dynamic_cast<SimpleType*>(type))
            return std::make_unique<SimpleVariable>(SimpleVariable(simpleType));
        if(VectorType* vectorType = dynamic_cast<VectorType*>(type))
            return std::make_unique<VectorVariable>(VectorVariable(vectorType));
        if(MatrixType* matrixType = dynamic_cast<MatrixType*>(type))
            return std::make_unique<MatrixVariable>(MatrixVariable(matrixType));
        return std::unique_ptr<Variable>(nullptr);
    }

    inline std::unique_ptr<Variable> copyVariable(Variable* variable) {
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

    inline bool areOfSameType(Variable* firstVariable, 
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

    inline std::unique_ptr<Variable> createLogicalVariable(bool isTrue) {
        return std::make_unique<SimpleVariable>
            (SimpleVariable(static_cast<int>(isTrue)));
    }
    
}
