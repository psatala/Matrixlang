#pragma once

#include <memory>

class Statement;

#include "../LanguageObjects.h"
#include "Declaration.h"
#include "Expression.h"

class For {

    std::string getStatementInfo(int identLevel);

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

    std::string print(int identLevel);
};