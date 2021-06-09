#pragma once

#include <memory>
#include <string>

#include "Type.h"
#include "Expressions/Expression.h"
#include "../LanguageObjects.h"

class Declaration {

    void innerExecute(ScopeManager* scopeManager, bool isLocal) {
        std::unique_ptr<Variable> variable = 
            VariableManagement::createVariable(type.get(), scopeManager);
        if(isLocal) {
            scopeManager->addLocalVariable(identifier, std::move(variable));
            return;
        }
        scopeManager->addGlobalVariable(identifier, std::move(variable));
    }

public:
    std::unique_ptr<Type> type;
    const std::string identifier;
    std::unique_ptr<Expression> expression;
    Declaration(std::unique_ptr<Type> type, const std::string identifier, 
        std::unique_ptr<Expression> expression) :
        type(std::move(type)), identifier(identifier), 
        expression(std::move(expression)) {}

    std::string print(int identLevel) {
        std::string toPrintString = std::string("Declaration") + "\n" + 
            ident(identLevel) + "Type: " + type->print(identLevel + 1) + 
            ident(identLevel) + "Identifier: " + identifier + "\n";
        if(expression)
            toPrintString += ident(identLevel) + "Expression: " + 
                expression->print(identLevel + 1);
        return toPrintString;
    }

    std::unique_ptr<Variable> execute(ScopeManager* scopeManager, 
        bool isLocal = true) {
        
        innerExecute(scopeManager, isLocal);
        if(expression) {
            std::unique_ptr<Variable> expressionVariable = 
                expression->value(scopeManager);
            if(!VariableManagement::areOfSameType(scopeManager->
                getVariable(identifier), expressionVariable.get()))
                throw std::string("Cannot perform assignment: variables are "
                    "not of the same type");
            scopeManager->setVariable(identifier, 
                std::move(expressionVariable));
        }
        return std::unique_ptr<Variable>(nullptr);
    }
};