#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Declaration.h"
#include "Expressions/Expression.h"

class Statement;


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
        std::unique_ptr<Statement> statement);

    std::string print(int identLevel);
};