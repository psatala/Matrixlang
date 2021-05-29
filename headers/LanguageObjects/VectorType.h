#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Type.h"

class Expression;

class VectorType : public Type {
public:
    std::unique_ptr<Type> type;
    std::unique_ptr<Expression> expression;
    VectorType(std::unique_ptr<Type> type, 
        std::unique_ptr<Expression> expression);
    std::string print(int identLevel) override;
};
