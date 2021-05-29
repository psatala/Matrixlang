#pragma once

#include <map>
#include <memory>

#include "Variable.h"

class Scope {
public:
    std::map<std::string, std::unique_ptr<Variable>> variablesMap;
    Scope() {}

    void setVariable(std::string identifier, 
        std::unique_ptr<Variable> variable) {

        variablesMap[identifier] = std::move(variable);
    }

    Variable* getVariable(std::string identifier) {
        return variablesMap[identifier].get();
    }
};
