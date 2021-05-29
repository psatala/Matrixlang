#pragma once

#include <memory>

#include "Expressions/Expression.h"
#include "../LanguageObjects.h"
#include "Type.h"


class VectorType : public Type {
public:
    std::unique_ptr<Type> type;
    std::unique_ptr<Expression> expression;
    VectorType(std::unique_ptr<Type> type, 
        std::unique_ptr<Expression> expression) : type(std::move(type)), 
        expression(std::move(expression)) {}
    std::string print(int identLevel) override {
        return std::string("Vector type") + "\n" + 
            ident(identLevel) + "Contained type: " + 
                type->print(identLevel + 1) + 
            ident(identLevel) + "Expression: " + 
                expression->print(identLevel + 1);
    }
};
