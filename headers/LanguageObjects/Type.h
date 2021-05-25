#pragma once

#include <string>

class Type {
public:
    Type() {}
    virtual std::string print(int identLevel) = 0;
    virtual ~Type() {}
};