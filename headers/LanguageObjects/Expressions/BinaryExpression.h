#pragma once

#include <memory>

#include "../Operator.h"
#include "Expression.h"
#include "../../LanguageObjects.h"

class BinaryExpression : public Expression {

    bool isAssignmentOperator() {
        if( ASSIGN          == op->type ||
            PLUS_ASSIGN     == op->type ||
            MINUS_ASSIGN    == op->type ||
            MULTIPLY_ASSIGN == op->type ||
            DIVIDE_ASSIGN   == op->type ||
            MODULO_ASSIGN   == op->type )
            return true;
        return false;
    }

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

    std::unique_ptr<Variable> value(ScopeManager* scopeManager) override {
        if(isAssignmentOperator()) {
            
            Variable* leftVar = lhs->rawValue(scopeManager);
            std::unique_ptr<Variable> rightVar = rhs->value(scopeManager);

            if(!VariableManagement::areOfSameType(leftVar, rightVar.get()))
                throw std::string("Cannot perform assignment: variables are "
                    "not of the same type");

            switch(op->type) {

            case PLUS_ASSIGN:
                rightVar = VariableOperators::add(leftVar, rightVar.get());
                break;

            case MINUS_ASSIGN:
                rightVar = VariableOperators::subtract(leftVar, rightVar.get());
                break;

            case MULTIPLY_ASSIGN:
                rightVar = VariableOperators::multiply(leftVar, rightVar.get());
                break;

            case DIVIDE_ASSIGN:
                rightVar = VariableOperators::divide(leftVar, rightVar.get());
                break;

            case MODULO_ASSIGN:
                rightVar = VariableOperators::modulo(leftVar, rightVar.get());
                break;

            default:
                break;
            }

            VariableManagement::copyVariableContent(leftVar, rightVar.get());
            return std::move(rightVar);
        }

        // non-assignment operators
        std::unique_ptr<Variable> leftVar = lhs->value(scopeManager);
        std::unique_ptr<Variable> rightVar = rhs->value(scopeManager);

        switch (op->type) {

        case PLUS:
            return VariableOperators::add(leftVar.get(), rightVar.get());
        case MINUS:
            return VariableOperators::subtract(leftVar.get(), rightVar.get());
        case MULTIPLY:
            return VariableOperators::multiply(leftVar.get(), rightVar.get());
        case DIVIDE:
            return VariableOperators::divide(leftVar.get(), rightVar.get());
        case MODULO:
            return VariableOperators::modulo(leftVar.get(), rightVar.get());

        case LESS_THAN:
            return VariableOperators::lessThan(leftVar.get(), rightVar.get());
        case LESS_EQUAL:
            return VariableOperators::lessEqual(leftVar.get(), rightVar.get());
        case MORE_THAN:
            return VariableOperators::moreThan(leftVar.get(), rightVar.get());
        case MORE_EQUAL:
            return VariableOperators::moreEqual(leftVar.get(), rightVar.get());
        case EQUAL:
            return VariableOperators::equal(leftVar.get(), rightVar.get());
        case NOT_EQUAL:
            return VariableOperators::notEqual(leftVar.get(), rightVar.get());

        case AND:
            return VariableOperators::logicalAnd(leftVar.get(), rightVar.get());
        case OR:
            return VariableOperators::logicalOr(leftVar.get(), rightVar.get());

        default:
            return std::unique_ptr<Variable>(nullptr);
        }
    }
};
