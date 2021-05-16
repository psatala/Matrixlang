#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Declaration.h"
#include "Expression.h"
#include "Statement.h"

class For {
public:
    std::unique_ptr<Declaration> declaration;
    std::unique_ptr<Expression> conditionalExpression;
    std::unique_ptr<Expression> incrementalExpression;
    std::unique_ptr<Statement> statement;

    For(std::unique_ptr<Declaration> declaration,
        std::unique_ptr<Expression> conditionalExpression,
        std::unique_ptr<Expression> incrementalExpression,
        std::unique_ptr<Statement> statement) : 
            declaration(std::move(declaration)),
            conditionalExpression(std::move(conditionalExpression)),
            incrementalExpression(std::move(incrementalExpression)),
            statement(std::move(statement)) {}

    std::string print(int identLevel) { 
        return std::string("For") + "\n" + 
            ident(identLevel) + "Declaration: " + 
                declaration->print(identLevel + 1) + 
            ident(identLevel) + "Conditional expression: " + 
                conditionalExpression->print(identLevel + 1) + 
            ident(identLevel) + "Incremental expression: " + 
                incrementalExpression->print(identLevel + 1) + 
            ident(identLevel) + "Statement: " + 
                statement->print(identLevel + 1);
    }

};