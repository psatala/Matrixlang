#pragma once

#include <vector>
#include <stack>

#include "Scope.h"
#include "EmbeddedFunctionsDeclarations.h"
#include "EnvironmentalConstants.h"

class Function;
class Expression;

using ExpressionList = std::vector<std::unique_ptr<Expression>>;

class ScopeManager {

    std::stack<std::vector<Scope>> scopeStructure;
    std::map<std::string, std::unique_ptr<Function>> functions;
    Scope globalScope;

public:
    static unsigned int MAX_STACK_DEPTH;

    ScopeManager();
    void init();
    
    void addFunction(std::unique_ptr<Function> function);
    std::unique_ptr<Variable> callFunction(std::string identifier, 
        ExpressionList* expressionList);
    Function* getFunction(std::string identifier);

    void addFuncall();
    void endFuncall();
    void addBlock();
    void endBlock();
    bool isStackEmpty() const;
    
    void addLocalVariable(std::string identifier, 
        std::unique_ptr<Variable> variable);
    void addGlobalVariable(std::string identifier, 
        std::unique_ptr<Variable> variable);
    
    Variable* getVariable(std::string identifier, bool isThrowing = true);
    void setVariable(std::string identifier, 
        std::unique_ptr<Variable> variable);
};