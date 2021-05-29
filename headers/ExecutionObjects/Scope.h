#pragma once

#include <map>
#include <memory>

#include "Variable.h"

class Scope {
public:
    std::map<std::string, std::unique_ptr<std::unique_ptr<Variable>> > 
        variablesMap;
    Scope() {}

    void setVariable(std::string identifier, 
        std::unique_ptr<Variable> variable) {

        std::unique_ptr<std::unique_ptr<Variable>> doublePointerVariable = 
            std::make_unique<std::unique_ptr<Variable>>(std::move(variable));
        variablesMap[identifier] = std::move(doublePointerVariable);
    }

    Variable* getVariable(std::string identifier) {
        if(!variablesMap[identifier])
            return nullptr;
        return (*variablesMap[identifier]).get();
    }

    // Variable** getVariableLocation(std::string identifier) {
    //     if(!variablesMap[identifier].get())
    //         return nullptr;
    //     return &variablesMap[identifier].get();
    // }
};