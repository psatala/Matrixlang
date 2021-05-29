#pragma once

#include <memory>

#include "Expression.h"
#include "../Operator.h"
#include "../../LanguageObjects.h"

class PostExpression: public Expression {
public:
    std::unique_ptr<Operator> postOperator;
    std::unique_ptr<Expression> expression;

    PostExpression(std::unique_ptr<Expression> expression, 
        std::unique_ptr<Operator> postOperator) :
        expression(std::move(expression)), 
        postOperator(std::move(postOperator)) {}

    std::string print(int identLevel) override {
        return std::string("Post expression")  + "\n" 
            + ident(identLevel) + "Expression: "
                 + expression->print(identLevel + 1)
            + ident(identLevel) + "Operator: " 
                + postOperator->print(identLevel + 1);
    }

    bool isLValue() const override {
        return false;
    }

    // post expression
    std::unique_ptr<Variable> value(ScopeManager* scopeManager) override {

        if(dynamic_cast<PostExpression*>(expression.get()))
            throw std::string("Nested post expressions not allowed");

        Variable* innerVariable = expression->rawValue(scopeManager);
        if(innerVariable->type != INT && innerVariable->type != FLOAT)
            throw std::string("Post expression can only be applied to variables"
                " of type int or float");

        std::unique_ptr<Variable> copy = 
            VariableManagement::copyVariable(innerVariable);

        SimpleVariable* simpleVariable = 
            dynamic_cast<SimpleVariable*>(innerVariable);
        

        VariableManagement::incrementValue(simpleVariable, postOperator.get());

        return std::move(copy);
    }
};
