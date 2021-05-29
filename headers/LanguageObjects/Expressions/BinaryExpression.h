#pragma once

#include <memory>

#include "../Operator.h"
#include "Expression.h"
#include "../../LanguageObjects.h"

class BinaryExpression : public Expression {
public:    
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
    std::unique_ptr<Operator> op;
    BinaryExpression(std::unique_ptr<Expression> lhs, 
        std::unique_ptr<Expression> rhs, std::unique_ptr<Operator> op) :
        lhs(std::move(lhs)), rhs(std::move(rhs)), op(std::move(op)) {}
    
    std::string print(int identLevel) override {
        return std::string("Binary expression")  + "\n" 
            + ident(identLevel) + "Left: " +        lhs->print(identLevel + 1)
            + ident(identLevel) + "Right: " +       rhs->print(identLevel + 1)
            + ident(identLevel) + "Operator: " +     op->print(identLevel + 1);
    }

    bool isLValue() const override {
        return false;
    }
};
