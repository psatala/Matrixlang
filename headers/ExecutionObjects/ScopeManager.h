#pragma once

#include <vector>
#include <stack>

#include "Scope.h"

class ScopeManager {

    std::stack<std::vector<Scope>> scopeStructure;
    Scope globalScope;

public:
    ScopeManager() {}
    
    void addFuncall() {
        std::vector<Scope> blockVector;
        blockVector.push_back(std::move(Scope()));
        scopeStructure.push(std::move(blockVector));
    }
    
    void endFuncall() {
        if(scopeStructure.empty())
            throw std::string("Scope stack already empty");
        scopeStructure.pop();
    }

    void addBlock() {
        scopeStructure.top().push_back(Scope());
    }

    void endBlock() {
        scopeStructure.top().pop_back();
        if(scopeStructure.top().empty())
            endFuncall();
    }

    bool isStackEmpty() const {
        return scopeStructure.empty();
    }

    void addLocalVariable(std::string identifier, 
        std::unique_ptr<Variable> variable) {
        
        if(scopeStructure.empty())
            throw std::string("Scope stack is empty");

        scopeStructure.top().back().setVariable(identifier, 
            std::move(variable));
    }

    void addGlobalVariable(std::string identifier, 
        std::unique_ptr<Variable> variable) {
        
        globalScope.setVariable(identifier, std::move(variable));
    }

    

    Variable* getVariable(std::string identifier) {

        if(!scopeStructure.empty()) {
            
            for(std::vector<Scope>::reverse_iterator iterator = 
                scopeStructure.top().rbegin(); 
                iterator != scopeStructure.top().rend(); 
                ++iterator) {

                if(Variable* variable = iterator->getVariable(identifier))
                    return variable;
            }

        }
        if(Variable* variable = globalScope.getVariable(identifier))
            return variable;

        throw std::string("Unknown identifier \"") + identifier + 
            std::string("\"");
    }



    void setVariable(std::string identifier, 
        std::unique_ptr<Variable> variable) {

        if(!scopeStructure.empty()) {
            
            for(std::vector<Scope>::reverse_iterator iterator = 
                scopeStructure.top().rbegin(); 
                iterator != scopeStructure.top().rend(); 
                ++iterator) {

                if(iterator->getVariable(identifier)) {
                    iterator->setVariable(identifier, std::move(variable));
                    return;
                }
            }

        }
        
        if (globalScope.getVariable(identifier)) {
            globalScope.setVariable(identifier, std::move(variable));
            return;
        }

        throw std::string("Unknown identifier \"") + identifier + 
            std::string("\"");
    }
    
};