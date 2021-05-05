#ifndef AUXILIARY_FUNCTIONS_LEXER_H
#define AUXILIARY_FUNCTIONS_LEXER_H

#include <gtest/gtest.h>
#include "../headers/Interpreter.h"

inline void assertTokenTypeAndValue(Lexer& lexer, TokenType type,
    std::variant<int, float, std::string> value) {
    
    Token* token = lexer.getToken();
    GTEST_ASSERT_EQ(token->type, type);
    GTEST_ASSERT_EQ(token->value, value);
    delete token;
}

inline void assertTokenType(Lexer& lexer, TokenType type) {
    Token* token = lexer.getToken();
    GTEST_ASSERT_EQ(token->type, type);
    delete token;
}

inline void assertTokenPosition(Lexer& lexer, int lineNumber, int columnNumber) 
{
    Token* token = lexer.getToken();
    GTEST_ASSERT_EQ(token->lineNumber, lineNumber);
    GTEST_ASSERT_EQ(token->columnNumber, columnNumber);
    delete token;
}

#endif //AUXILIARY_FUNCTIONS_LEXER_H