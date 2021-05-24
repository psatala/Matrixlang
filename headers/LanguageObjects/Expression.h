#pragma once

#include <string>

class Expression {
public:
    virtual std::string print(int identLevel) = 0;
    virtual bool isLValue() const {
        return false;
    }
    virtual ~Expression() {}
};
