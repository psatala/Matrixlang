#pragma once

#include <variant>
#include <memory>

#include "Expression.h"
#include "../LanguageObjects.h"
#include "Type.h"


class MatrixType : public Type {
public:
    std::unique_ptr<Type> type;
    std::unique_ptr<Expression> firstExpression;
    std::unique_ptr<Expression> secondExpression;
    MatrixType(std::unique_ptr<Type> type, 
        std::unique_ptr<Expression> firstExpression, 
        std::unique_ptr<Expression> secondExpression) : type(std::move(type)), 
        firstExpression(std::move(firstExpression)), 
        secondExpression(std::move(secondExpression)) {}
    std::string print(int identLevel) override {
        return std::string("Matrix type") + "\n" + 
            ident(identLevel) + "Contained type: " + 
                type->print(identLevel + 1) + 
            ident(identLevel) + "First expression: " + 
                firstExpression->print(identLevel + 1) + 
            ident(identLevel) + "Second expression" + 
                secondExpression->print(identLevel + 1);
    }
};
