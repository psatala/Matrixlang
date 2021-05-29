#pragma once

#include <memory>

#include "Expression.h"
#include "../../LanguageObjects.h"

class MatrixIndexExpression : public Expression {
public:
    std::unique_ptr<Expression> innerExpression;
    std::unique_ptr<Expression> firstIndexExpression;
    std::unique_ptr<Expression> secondIndexExpression;
    MatrixIndexExpression(std::unique_ptr<Expression> innerExpression,
        std::unique_ptr<Expression> firstIndexExpression, 
        std::unique_ptr<Expression> secondIndexExpression) : 
        innerExpression(std::move(innerExpression)), 
        firstIndexExpression(std::move(firstIndexExpression)), 
        secondIndexExpression(std::move(secondIndexExpression)) {}

    std::string print(int identLevel) override {
        return std::string("Matrix index expression") + "\n" + 
            ident(identLevel) + "Inner expression: " + 
            innerExpression->print(identLevel + 1) + 
            ident(identLevel) + "First index expression: " + 
            firstIndexExpression->print(identLevel + 1) + 
            ident(identLevel) + "Second index expression: " + 
            secondIndexExpression->print(identLevel + 1);
    }

    bool isLValue() const override {
        return true;
    }

    std::unique_ptr<Variable> value(ScopeManager* scopeManager) override {
        return std::move(VariableManagement::copyVariable(
            rawValue(scopeManager)));
    }

    Variable* rawValue(ScopeManager* scopeManager) {
        Variable* innerVariable = 
            innerExpression->rawValue(scopeManager);
        if(innerVariable->type != MATRIX)
            throw std::string("Matrix index access can only be applied to a "
                "Matrix");
        
        MatrixVariable* innerMatrixVariable = 
            dynamic_cast<MatrixVariable*>(innerVariable);
        

        // unsigned int firstIndex = (unsigned int)indexExpression.value();
        // unsigned int secondIndex = (unsigned int)indexExpression.value();
        unsigned int firstIndex = 1; // placeholder
        unsigned int secondIndex = 1; // placeholder
        
        return innerMatrixVariable->values[firstIndex][secondIndex].get();
    }
};