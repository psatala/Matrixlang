#pragma once

#include <string>

class Type {
public:
    Type() {}
    virtual std::string print(int identLevel) {
        return std::string("Type") + "\n";
    }
};