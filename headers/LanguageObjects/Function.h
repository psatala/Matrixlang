#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Type.h"
#include "ArgumentList.h"
#include "Statement.h"

class Function {

public:
    std::unique_ptr<Type> type;
    std::string identifier;
    std::unique_ptr<ArgumentList> argumentList;
    std::unique_ptr<Statement> statement;
    

    Function(std::unique_ptr<Type> type, std::string identifier, 
        std::unique_ptr<ArgumentList> argumentList, 
        std::unique_ptr<Statement> statement) : type(std::move(type)), 
        identifier(identifier), argumentList(std::move(argumentList)), 
        statement(std::move(statement)) {
        
        if(!this->argumentList)
            this->argumentList = std::make_unique<ArgumentList>(ArgumentList());
    }

    std::string print(int identLevel) { 
        return std::string("Function") + "\n" + 
            ident(identLevel) + "Type: " + type->print(identLevel + 1) + 
            ident(identLevel) + "Identifier: " + identifier + "\n" + 
            ident(identLevel) + "Argument list: " + 
                argumentList->print(identLevel + 1) + 
            ident(identLevel) + "Statement: " + 
                statement->print(identLevel + 1);
    }



    std::unique_ptr<Variable> execute(ScopeManager* scopeManager, 
        ExpressionList* expressionList) {
        
        // execute expressions in funcall
        std::vector<std::unique_ptr<Variable>> expressionVariables;
        for(int i = 0; i < expressionList->size(); ++i) {
            expressionVariables.push_back(std::move(
                (*expressionList)[i]->value(scopeManager)));
        }

        scopeManager->addFuncall();
        
        // checking number of arguments
        if(argumentList->typeVector.size() != expressionList->size())
            throw std::string("Expected ") + 
                std::to_string(argumentList->typeVector.size()) + 
                std::string(" arguments, but got ")  +
                std::to_string(expressionList->size());
        

        // checking types
        for(int i = 0; i < expressionVariables.size(); ++i) {
            std::unique_ptr<Variable> expectedVariable = VariableManagement::
                createVariable(argumentList->typeVector[i].get(), scopeManager);
            if(!VariableManagement::areOfSameType(expectedVariable.get(), 
                expressionVariables[i].get())) {
                
                throw std::string("Type mismatch on position ") + 
                    std::to_string(i);
            }

            // type checking ok, add to scope manager
            scopeManager->addLocalVariable(argumentList->identifierVector[i], 
                std::move(expressionVariables[i]));
        }

        // execute statement inside
        std::unique_ptr<Variable> returnedVariable = 
            statement->execute(scopeManager);

        scopeManager->endFuncall();

        std::unique_ptr<Variable> expectedReturnVariable = VariableManagement::
            createVariable(type.get(), scopeManager);

        if(!VariableManagement::areOfSameType(returnedVariable.get(), 
            expectedReturnVariable.get()))
            throw std::string("Type mismatch of return variable");

        return std::move(returnedVariable);
    }

};