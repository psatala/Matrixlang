#pragma once

#include <memory>

#include "Expression.h"
#include "../Operator.h"
#include "../../LanguageObjects.h"

class UnaryIncrementalExpression: public Expression {
public:
    std::unique_ptr<Operator> unaryOperator;
    std::unique_ptr<Expression> expression;

    UnaryIncrementalExpression(std::unique_ptr<Operator> unaryOperator,
        std::unique_ptr<Expression> expression) :
        unaryOperator(std::move(unaryOperator)),
        expression(std::move(expression)) {}

    std::string print(int identLevel) override {
        return std::string("Unary incremental expression")  + "\n" 
            + ident(identLevel) + "Operator: " 
                + unaryOperator->print(identLevel + 1)
            + ident(identLevel) + "Expression: "
                 + expression->print(identLevel + 1);
    }

    bool isLValue() const override {
        return false;
    }


    std::unique_ptr<Variable> value(ScopeManager* scopeManager) {
        return VariableManagement::copyVariable(rawValue(scopeManager));
    }

    Variable* rawValue(ScopeManager* scopeManager) {

        Variable* innerVariable = 
            expression->rawValue(scopeManager);
        if(innerVariable->type != INT && innerVariable->type != FLOAT)
            throw std::string("Unary incremental expression can only be "
                "applied to variables of type int or float");
        
        SimpleVariable* simpleVariable = 
            dynamic_cast<SimpleVariable*>(innerVariable);
            
        VariableManagement::incrementValue(simpleVariable, unaryOperator.get());
        return innerVariable;
    }


};
