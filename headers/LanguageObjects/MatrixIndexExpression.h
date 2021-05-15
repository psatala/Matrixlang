#pragma once

#include <memory>

#include "Expression.h"
#include "../LanguageObjects.h"

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
};