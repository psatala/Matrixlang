#pragma once

#include <vector>
#include <variant>
#include <string>
#include <memory>

#include "Token.h"

class Expression {
    
};

class Operator {
public:
    TokenType type;
    int precedenceLevel;
    bool isRightAssociative;
    bool isBinary;
    Operator(TokenType type) : type(type) { setAttributes(); }
    void setAttributes() {
        //TODO: refactor
        if(type == PLUS) {
            precedenceLevel = 4;
            isRightAssociative = false;
            isBinary = true;
            return;
        }
        if(type == ASSIGN) {
            precedenceLevel = 0;
            isRightAssociative = true;
            isBinary = true;
        }
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
};

class PrimaryExpression : public Expression {
public:
    Token token;
    PrimaryExpression(Token token) : token(token) {}
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