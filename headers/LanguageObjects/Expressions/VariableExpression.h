#pragma once

#include "../../LanguageObjects.h"
#include "Expression.h"

class VariableExpression : public Expression {
public:
    std::string identifier;
    VariableExpression(std::string identifier) : identifier(identifier) {}
    
    std::string print(int identLevel) override {
        return std::string("Variable expression") + "\n" + 
            ident(identLevel) + "Identifier: " + identifier + "\n";
    }
    
    bool isLValue() const override {
        return true;
    }

    std::unique_ptr<Variable> value(ScopeManager* scopeManager) override {
        return std::move(VariableManagement::copyVariable(
            rawValue(scopeManager)));
    }
    
    Variable* rawValue(ScopeManager* scopeManager) override {
        return scopeManager->getVariable(identifier);
    }
};
