#pragma once

#include <variant>
#include <string>

#include "Variable.h"
#include "../LanguageObjects/SimpleType.h"

class SimpleVariable : public Variable {
public:
    std::variant<int, float, std::string> value;

    SimpleVariable(std::variant<int, float, std::string> value) : value(value) {
        if(std::get_if<int>         (&this->value)) type = INT;
        if(std::get_if<float>       (&this->value)) type = FLOAT;
        if(std::get_if<std::string> (&this->value)) type = STRING;
    }

    SimpleVariable(SimpleType* simpleType) {
        type = simpleType->type;
        if(INT      == type)    value = 0;
        if(FLOAT    == type)    value = 0.0f;
        if(STRING   == type)    value = "";
    }

    SimpleVariable(const SimpleVariable* simpleVariable) {
        type = simpleVariable->type;
        value = simpleVariable->value;

        // resolve ambiguity
        // if(int* intValue = std::get_if<int>(&this->value)) {
        //     if(FLOAT == type)
        //         value = static_cast<float>(*intValue);
        // }
    }


    bool getLogicalValue() override {
        if(INT == type) {
            if(0 == std::get<int>(value))
                return false;
            return true;
        }

        if(FLOAT == type) {
            if(0.0f == std::get<float>(value))
                return false;
            return true;
        }

        // string
        if("" == std::get<std::string>(value))
            return false;
        return true;

    }
};