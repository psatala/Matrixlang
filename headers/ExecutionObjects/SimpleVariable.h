#pragma once

#include <variant>
#include <string>

#include "Variable.h"
#include "../LanguageObjects/SimpleType.h"

class SimpleVariable : public Variable {
public:
    std::variant<int, float, std::string> value;

    SimpleVariable(SimpleType* simpleType) {
        type = simpleType->type;
        if(INT      == type)    value = 0;
        if(FLOAT    == type)    value = 0.0f;
        if(STRING   == type)    value = "";
    }

    void overrideMe() override {}
};