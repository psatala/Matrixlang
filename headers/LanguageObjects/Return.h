#pragma once

#include <memory>
#include <string>

#include "../LanguageObjects.h"
#include "Expressions/Expression.h"

class Return {
public:
    std::unique_ptr<Expression> expression;
    Return(std::unique_ptr<Expression> expression) : 
        expression(std::move(expression)) {}

    std::string print(int identLevel) {
        return std::string("Return") + "\n" + 
            ident(identLevel) + "Expression: " + 
            expression->print(identLevel + 1);
    }

    std::unique_ptr<Variable> execute(ScopeManager* scopeManager) {
        if(expression)
            return expression->value(scopeManager);
        return std::make_unique<VoidVariable>(VoidVariable());
    }
};