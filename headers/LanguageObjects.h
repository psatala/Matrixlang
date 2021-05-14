#pragma once

#include <vector>
#include <variant>
#include <string>
#include <memory>

#include "Token.h"

inline std::string ident(int identationLevel) {
    const int identationMultiplier = 2;
    return std::string(identationMultiplier * identationLevel, ' ');
}

class Expression {
public:
    virtual std::string print(int identationLevel) {
        return std::string("Expression") + "\n";
    }
};



class Program {
public:
    std::unique_ptr<Expression> expression;
    Program(std::unique_ptr<Expression> expression) : 
        expression(std::move(expression)) {}
    std::string print() {
        return std::string("Program") + "\n"
            + ident(1) + expression->print(2);
    }
};


class Operator {
public:
    TokenType type;
    Operator(TokenType type) : type(type) {}

    std::string print(int identationLevel) {
        return std::string("code ") + std::to_string(type) + "\n";
    }
};

class BinaryExpression : public Expression {
public:    
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
    std::unique_ptr<Operator> op;
    BinaryExpression(std::unique_ptr<Expression> lhs, 
        std::unique_ptr<Expression> rhs, std::unique_ptr<Operator> op) :
        lhs(std::move(lhs)), rhs(std::move(rhs)), op(std::move(op)) {}
    
    std::string print(int identLevel) override {
        return std::string("Binary expression")  + "\n" 
            + ident(identLevel) + "Left: " +        lhs->print(identLevel + 1)
            + ident(identLevel) + "Right: " +       rhs->print(identLevel + 1)
            + ident(identLevel) + "Operator: " +     op->print(identLevel + 1);
    }
};

class PrimaryExpression : public Expression {
public:
    Token token;
    PrimaryExpression(Token token) : token(token) {}
    
    std::string print(int identationLevel) override {
        return std::string("Primary expression: ") + getTokenInfo() + "\n";
    }

    std::string getTokenInfo() {
        if(INT_NUMBER == token.type)
            return "int number: " + std::to_string(std::get<int>(token.value));
        if(FLOAT_NUMBER == token.type)
            return "float number: " + 
                std::to_string(std::get<float>(token.value));
        if(IDENTIFIER == token.type)
            return "identifier: " + std::get<std::string>(token.value);
        return "unexpected token type";
    }
};







































// class Expression;
// class StringExpression;
// class SimpleType;
// class VectorType;
// class MatrixType;
// class Type;


// class Expression {
// public:
//     Expression() = default;
// };


// class StringExpression {
// public:
//     std::vector<std::variant<std::string, Expression>>
//         stringLiteralsAndExpressions;
//     StringExpression(std::vector<std::variant<std::string, Expression>>
//         stringLiteralsAndExpressions): 
//         stringLiteralsAndExpressions(stringLiteralsAndExpressions) {}
// };

// class SimpleType {
// public:
//     TokenType type;
//     SimpleType(TokenType type): type(type) {}
// };


// class VectorType {
// public:
//     std::unique_ptr<Token> type;
//     Expression expression;
//     VectorType(std::unique_ptr<Token> type, Expression expression) : type(type), 
//         expression(expression) {}
// };


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