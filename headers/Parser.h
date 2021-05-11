#pragma once

#include "Lexer.h"
#include "LanguageObjects.h"

class Parser {
    std::ostream& errStream;

    Token currentToken;

    void getNextToken();

    std::optional<Expression> parseExpression();
    std::optional<StringExpression> parseStringExpression();

public:
    Lexer lexer;

    Parser(std::unique_ptr<std::istream> inStream, std::ostream& errStream) : 
        errStream(errStream),
        lexer(std::move(inStream), errStream) {}
};