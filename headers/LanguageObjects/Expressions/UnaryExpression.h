#pragma once

#include <memory>

#include "Expression.h"
#include "../Operator.h"
#include "../../LanguageObjects.h"

class UnaryExpression: public Expression {
public:
    std::unique_ptr<Operator> unaryOperator;
    std::unique_ptr<Expression> expression;

    UnaryExpression(std::unique_ptr<Operator> unaryOperator,
        std::unique_ptr<Expression> expression) :
        unaryOperator(std::move(unaryOperator)),
        expression(std::move(expression)) {}

    std::string print(int identLevel) override {
        return std::string("Unary expression")  + "\n" 
            + ident(identLevel) + "Operator: " 
                + unaryOperator->print(identLevel + 1)
            + ident(identLevel) + "Expression: "
                 + expression->print(identLevel + 1);
    }

    bool isLValue() const override {
        return false;
    }

    std::unique_ptr<Variable> value(ScopeManager* scopeManager) {
        std::unique_ptr<Variable> innerVariable = 
            expression->value(scopeManager);
        
        switch(unaryOperator->type) {

        case PLUS:
            return VariableOperators::unaryPlus(innerVariable.get());
        case MINUS:
            return VariableOperators::unaryMinus(innerVariable.get());
        case NOT:
            return VariableOperators::logicalNot(innerVariable.get());
        default:
            throw std::string("Unexpected operator in unary expression");
        }
        
    }

};
