#pragma once

#include <vector>
#include <memory>

#include "Variable.h"
#include "../LanguageObjects/MatrixType.h"

// namespace definition in Execution.h
namespace VariableManagement {
    std::unique_ptr<Variable> createVariable(Type* type);
}


class MatrixVariable : public Variable {
public:
    std::vector<std::vector <std::unique_ptr<Variable> >> values;
    unsigned int firstLength;
    unsigned int secondLength;

    MatrixVariable(MatrixType* matrixType) {
        type = MATRIX;
        firstLength = 2; // placeholder
        secondLength = 2; // placeholder
        for(unsigned int i = 0; i < firstLength; ++i) {
            std::vector<std::unique_ptr<Variable>> innerValues;
            for(unsigned int j = 0; j < secondLength; ++j) {
                innerValues.push_back(std::move(VariableManagement::
                    createVariable(matrixType->type.get())));
            }
            values.push_back(std::move(innerValues));
        }
    }


    void overrideMe() override {}
};