#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Expression.h"
#include "Statement.h"

class If {
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

    std::string print(int identLevel) { 
        return std::string("If") + "\n" + 
            ident(identLevel) + "Conditional expression: " + 
                conditionalExpression->print(identLevel + 1) + 
            ident(identLevel) + "True statement: " + 
                trueStatement->print(identLevel + 1) + 
            ident(identLevel) + "False statement: " + 
                falseStatement->print(identLevel + 1);
    }
};