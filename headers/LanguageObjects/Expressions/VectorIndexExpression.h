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
};