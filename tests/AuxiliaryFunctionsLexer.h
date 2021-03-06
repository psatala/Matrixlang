#pragma once

#include <gtest/gtest.h>
#include "../headers/Interpreter.h"


//class for passing data to parametrised tests
class SimpleTestData {
public:
    std::string input;
    TokenType firstToken;
    SimpleTestData(std::string input, TokenType firstToken) :
        input(input), firstToken(firstToken) {}
};

inline void assertTokenTypeAndValue(Lexer& lexer, TokenType type,
    std::variant<int, float, std::string> value) {
    
    const std::optional<Token> token = lexer.getToken();
    GTEST_ASSERT_EQ(token->type, type);
    GTEST_ASSERT_EQ(token->value, value);
}

inline void assertTokenType(Lexer& lexer, TokenType type) {
    const std::optional<Token> token = lexer.getToken();
    GTEST_ASSERT_EQ(token->type, type);
}

inline void assertTokenPosition(Lexer& lexer, int lineNumber, int columnNumber) 
{
    const std::optional<Token> token = lexer.getToken();
    GTEST_ASSERT_EQ(token->lineNumber, lineNumber);
    GTEST_ASSERT_EQ(token->columnNumber, columnNumber);
}
