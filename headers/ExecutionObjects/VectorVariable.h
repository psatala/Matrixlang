#pragma once

#include <vector>
#include <memory>

#include "Variable.h"
#include "../LanguageObjects/VectorType.h"

// namespace definition in Execution.h
namespace VariableManagement {
    std::unique_ptr<Variable> createVariable(Type* type);
}


class VectorVariable : public Variable {
public:
    std::vector<std::unique_ptr<Variable>> values;
    unsigned int length;

    VectorVariable(VectorType* vectorType) {
        type = VECTOR;
        length = 2; // placeholder
        for(unsigned int i = 0; i < length; ++i) {
            values.push_back(std::move(
                VariableManagement::createVariable(vectorType->type.get())));
        }
    }


    void overrideMe() override {}
};