#pragma once

#include <string>

class Expression {
public:
    virtual std::string print(int identLevel) {
        return std::string("Expression") + "\n";
    }
};
