#pragma once

#include "Lexer.h"

#include "LanguageObjects.h"
// #include "LanguageObjects/Expression.h"
// #include "LanguageObjects/MatrixType.h"
// #include "LanguageObjects/SimpleType.h"
// #include "LanguageObjects/StringExpression.h"
// #include "LanguageObjects/Type.h"
// #include "LanguageObjects/VectorType.h"

class Parser {
    std::ostream& errStream;

    Token currentToken;

    void getNextToken();
    void generateError(std::string message);


public:
    Lexer lexer;

    // std::optional<Expression> parseExpression();
    // std::optional<StringExpression> parseStringExpression();
    // std::optional<SimpleType> parseSimpleType();
    // std::optional<VectorType> parseVectorType();
    // std::optional<MatrixType> parseMatrixType();
    // std::optional<Type> parseType();

    std::unique_ptr<PrimaryExpression> parsePrimaryExpression();
    std::unique_ptr<Operator> parseAdditionOperator();
    std::unique_ptr<Operator> parseAssignmentOperator();
    std::unique_ptr<Expression> parseAdditionExpression();
    std::unique_ptr<Expression> parseAssignmentExpression();
    std::unique_ptr<Program> parseProgram();

    Parser(std::unique_ptr<std::istream> inStream, std::ostream& errStream) : 
        errStream(errStream),
        lexer(std::move(inStream), errStream) {
            // getNextToken();
        }
};