#pragma once

#include <string>

class Expression {
public:
    virtual std::string print(int identationLevel) {
        return std::string("Expression") + "\n";
    }
};
