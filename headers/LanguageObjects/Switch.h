#pragma once

#include <string>

#include "../LanguageObjects.h"

class Switch {
public:
    Switch() {}
    virtual std::string print(int identLevel) { 
        return std::string("Switch") + "\n";
    }
};