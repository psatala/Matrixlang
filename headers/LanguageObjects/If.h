#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Expressions/Expression.h"
class Statement;


class If {
    std::string getTrueStatementInfo(int identLevel);
    std::string getFalseStatementInfo(int identLevel);
public:
    std::unique_ptr<Expression> conditionalExpression;
    std::unique_ptr<Statement> trueStatement;
    std::unique_ptr<Statement> falseStatement;
    If(std::unique_ptr<Expression> conditionalExpression,
        std::unique_ptr<Statement> trueStatement,
        std::unique_ptr<Statement> falseStatement);

    std::string print(int identLevel);
    
    std::unique_ptr<Variable> execute(ScopeManager* scopeManager);
};