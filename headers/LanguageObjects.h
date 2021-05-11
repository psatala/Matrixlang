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