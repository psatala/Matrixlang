#pragma once

#include <string>

#include "../LanguageObjects.h"

class Switch {
public:
    Switch() {}
    virtual std::string print(int identLevel) { 
        return std::string("Switch") + "\n";
    }
    virtual std::unique_ptr<Variable> execute(ScopeManager* scopeManager) {
        throw std::string("Not implemented error");
    }
};