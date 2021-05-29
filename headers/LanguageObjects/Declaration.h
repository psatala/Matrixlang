#pragma once

#include <memory>
#include <string>

#include "Type.h"
#include "Expressions/Expression.h"
#include "../LanguageObjects.h"

class Declaration {
public:
    std::unique_ptr<Type> type;
    const std::string identifier;
    std::unique_ptr<Expression> expression;
    Declaration(std::unique_ptr<Type> type, const std::string identifier, 
        std::unique_ptr<Expression> expression) :
        type(std::move(type)), identifier(identifier), 
        expression(std::move(expression)) {}

    std::string print(int identLevel) {
        std::string toPrintString = std::string("Declaration") + "\n" + 
            ident(identLevel) + "Type: " + type->print(identLevel + 1) + 
            ident(identLevel) + "Identifier: " + identifier + "\n";
        if(expression)
            toPrintString += ident(identLevel) + "Expression: " + 
                expression->print(identLevel + 1);
        return toPrintString;
    }
};