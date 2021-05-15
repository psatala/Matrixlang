#pragma once

#include "../LanguageObjects.h"

class Statement {
public:
    Statement() {}
    std::string print(int identLevel) {
        return std::string("Statement") + "\n";
    }
};