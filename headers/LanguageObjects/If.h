#pragma once

#include <memory>

class Statement;

#include "../LanguageObjects.h"
#include "Expressions/Expression.h"

class If {

    std::string getTrueStatementInfo(int identLevel);
    std::string getFalseStatementInfo(int identLevel);

public:
    std::unique_ptr<Expression> conditionalExpression;
    std::unique_ptr<Statement> trueStatement;
    std::unique_ptr<Statement> falseStatement;
    If(std::unique_ptr<Expression> conditionalExpression,
        std::unique_ptr<Statement> trueStatement,
        std::unique_ptr<Statement> falseStatement) : 
        conditionalExpression(std::move(conditionalExpression)),
        trueStatement(std::move(trueStatement)),
        falseStatement(std::move(falseStatement)) {}

    std::string print(int identLevel);
    
};