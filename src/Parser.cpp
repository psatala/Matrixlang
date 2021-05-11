#include "../headers/Parser.h"

void Parser::getNextToken() {
    static bool isEOTProcessed = false;
    if(isEOTProcessed)
        throw "EOT already processed!";

    do {
        currentToken = lexer.getToken();
    } while(COMMENT == currentToken.type);
    if(EOT == currentToken.type)
        isEOTProcessed = true;
}

std::optional<Expression> Parser::parseExpression() {
    return Expression();
}

std::optional<StringExpression> Parser::parseStringExpression() {
    if(STRING_CONSTANT != currentToken.type)
        return std::nullopt;
    std::vector<std::variant<std::string, Expression>>
        stringLiteralsAndExpressions;
    stringLiteralsAndExpressions.push_back(
        std::get<std::string>(currentToken.value));
    getNextToken();
    std::optional<Expression> expression;
    while(true) {
        bool isExpressionParsed = false;
        if(expression = parseExpression()) {
            stringLiteralsAndExpressions.push_back(expression.value());
            isExpressionParsed = true;
        }
        if(STRING_CONSTANT != currentToken.type) {
            if(isExpressionParsed)
                throw "String expression should end with string literal, \
                    not expression";
            break;
        }
    }
    return StringExpression(stringLiteralsAndExpressions);
}