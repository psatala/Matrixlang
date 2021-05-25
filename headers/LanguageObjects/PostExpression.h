#pragma once

#include <memory>

#include "Expression.h"
#include "Operator.h"
#include "../LanguageObjects.h"

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
        return true;
    }
};
