#pragma once

#include <vector>
#include <variant>
#include <string>

#include "Token.h"

class Expression;
class StringExpression;
class SimpleType;
class VectorType;
class MatrixType;
class Type;


class Expression {
public:
    Expression() = default;
};


class StringExpression {
public:
    std::vector<std::variant<std::string, Expression>>
        stringLiteralsAndExpressions;
    StringExpression(std::vector<std::variant<std::string, Expression>>
        stringLiteralsAndExpressions): 
        stringLiteralsAndExpressions(stringLiteralsAndExpressions) {}
};

class SimpleType {
public:
    TokenType type;
    SimpleType(TokenType type): type(type) {}
};


class VectorType {
public:
    Type& type;
    Expression expression;
    VectorType(Type& type, Expression expression) : type(type), 
        expression(expression) {}
};


class MatrixType {
public:
    Type& type;
    Expression firstExpression;
    Expression secondExpression;
    MatrixType(Type& type, Expression firstExpression, 
        Expression secondExpression) : type(type), 
        firstExpression(firstExpression), secondExpression(secondExpression) {}
};


class Type {
public:
    std::variant<SimpleType, VectorType, MatrixType> containedType;
    Type(std::variant<SimpleType, VectorType, MatrixType> containedType) : 
        containedType(containedType) {}
};