#pragma once

#include <memory>
#include "SimpleVariable.h"
#include "VectorVariable.h"
#include "MatrixVariable.h"

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
}
