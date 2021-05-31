#include "../../headers/ExecutionObjects/ScopeManager.h"
#include "../../headers/LanguageObjects/Function.h"
#include "../../headers/LanguageObjects/Expressions/Expression.h"

ScopeManager::ScopeManager() {
    EmbeddedFunctionsDeclarations::addAllEmbeddedFunctions(this);
}

void ScopeManager::init() {
    scopeStructure.push(std::move(std::vector<Scope>()));
}


void ScopeManager::addFunction(std::unique_ptr<Function> function) {
    
    if(functions[function->identifier])
        throw std::string("Function with name \"") + function->identifier + 
            std::string("\" already exists");
    functions[function->identifier] = std::move(function);
}


std::unique_ptr<Variable> ScopeManager::callFunction(std::string identifier, 
    ExpressionList* expressionList) {
    
    return functions[identifier]->execute(this, expressionList);
}


Function* ScopeManager::getFunction(std::string identifier) {
    if(functions[identifier])
        return functions[identifier].get();
    return nullptr;
}



void ScopeManager::addFuncall() {
    std::vector<Scope> blockVector;
    blockVector.push_back(std::move(Scope()));
    scopeStructure.push(std::move(blockVector));
}

void ScopeManager::endFuncall() {
    if(scopeStructure.empty())
        throw std::string("Scope stack already empty");
    scopeStructure.pop();
}

void ScopeManager::addBlock() {
    scopeStructure.top().push_back(Scope());
}

void ScopeManager::endBlock() {
    scopeStructure.top().pop_back();
}

bool ScopeManager::isStackEmpty() const {
    return scopeStructure.empty();
}

void ScopeManager::addLocalVariable(std::string identifier, 
    std::unique_ptr<Variable> variable) {
    
    if(scopeStructure.empty())
        throw std::string("Scope stack is empty");

    if(scopeStructure.top().back().getVariable(identifier))
        throw std::string("Local variable with name \"") + identifier + 
            std::string("\" already exists");
    
    scopeStructure.top().back().setVariable(identifier, 
        std::move(variable));
}

void ScopeManager::addGlobalVariable(std::string identifier, 
    std::unique_ptr<Variable> variable) {
    
    if(globalScope.getVariable(identifier))
        throw std::string("Global variable with name \"") + identifier + 
            std::string("\" already exists");
    globalScope.setVariable(identifier, std::move(variable));
}



Variable* ScopeManager::getVariable(std::string identifier, bool isThrowing) {

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

    if(isThrowing)
        throw std::string("Unknown identifier \"") + identifier + 
            std::string("\"");
    return nullptr;
}



void ScopeManager::setVariable(std::string identifier, 
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
