#pragma once

#include <memory>

#include "Expression.h"
#include "../../LanguageObjects.h"

class VectorIndexExpression : public Expression {
public:
    std::unique_ptr<Expression> innerExpression;
    std::unique_ptr<Expression> indexExpression;
    VectorIndexExpression(std::unique_ptr<Expression> innerExpression,
        std::unique_ptr<Expression> indexExpression) : 
        innerExpression(std::move(innerExpression)), 
        indexExpression(std::move(indexExpression)) {}

    std::string print(int identLevel) override {
        return std::string("Vector index expression") + "\n" + 
            ident(identLevel) + "Inner expression: " + 
            innerExpression->print(identLevel + 1) + 
            ident(identLevel) + "Index expression: " + 
            indexExpression->print(identLevel + 1);
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
        if(innerVariable->type != VECTOR)
            throw std::string("Vector index access can only be applied to a "
                "Vector");
        
        VectorVariable* innerVectorVariable = 
            dynamic_cast<VectorVariable*>(innerVariable);
        

        unsigned int index = VariableManagement::getUnsignedIntValueFromVariable
            (indexExpression->value(scopeManager).get());
        
        if(index >= innerVectorVariable->values.size())
            throw std::string("Index out of range");
        
        return innerVectorVariable->values[index].get();
    }

};