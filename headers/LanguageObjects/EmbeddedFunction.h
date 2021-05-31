#pragma once

#include <iostream>

#include "Function.h"
#include "../ExecutionObjects/EmbeddedFunctionsDefinitions.h"

class EmbeddedFunction : public Function {
public:
    static std::istream* userInputStream;
    static std::ostream* outputStream;

    EmbeddedFunction(std::unique_ptr<Type> type, 
        std::string identifier, 
        std::unique_ptr<ArgumentList> argumentList, 
        std::unique_ptr<Statement> statement);

    std::unique_ptr<Variable> executeInnerStatement(ScopeManager* scopeManager);
};