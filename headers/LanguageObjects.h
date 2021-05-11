#pragma once

#include <variant>
#include <vector>
#include <string>

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
    SimpleType type;
    Expression expression;
    VectorType(SimpleType type, Expression expression) : type(type), 
        expression(expression) {}
};

class MatrixType {
public:
    SimpleType type;
    Expression firstExpression;
    Expression secondExpression;
    MatrixType(SimpleType type, Expression firstExpression, 
        Expression secondExpression) : type(type), 
        firstExpression(firstExpression), secondExpression(secondExpression) {}
};

class Type {
public:
    std::variant<SimpleType, VectorType, MatrixType> type;
    Type(std::variant<SimpleType, VectorType, MatrixType> type) : type(type) {}
};