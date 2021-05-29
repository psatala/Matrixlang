#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Type.h"

class Expression;

class MatrixType : public Type {
public:
    std::unique_ptr<Type> type;
    std::unique_ptr<Expression> firstExpression;
    std::unique_ptr<Expression> secondExpression;
    MatrixType(std::unique_ptr<Type> type, 
        std::unique_ptr<Expression> firstExpression, 
        std::unique_ptr<Expression> secondExpression);
    std::string print(int identLevel) override;
};
