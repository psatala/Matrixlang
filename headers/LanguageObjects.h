#pragma once

#include <vector>
#include <map>
#include <variant>
#include <string>
#include <memory>

#include "Token.h"
#include "LanguageObjects/SimpleType.h"


inline std::string ident(int identationLevel) {
    const int identationMultiplier = 2;
    return std::string(identationMultiplier * identationLevel, ' ');
}














// class MatrixType {
// public:
//     std::unique_ptr<Token> type;
//     Expression firstExpression;
//     Expression secondExpression;
//     MatrixType(std::unique_ptr<Token> type, Expression firstExpression, 
//         Expression secondExpression) : type(type), 
//         firstExpression(firstExpression), secondExpression(secondExpression) {}
// };


// class Type {
// public:
//     std::variant<SimpleType, VectorType, MatrixType> containedType;
//     Type(std::variant<SimpleType, VectorType, MatrixType> containedType) : 
//         containedType(containedType) {}
// };