#include <gtest/gtest.h>
#include "../headers/Interpreter.h"

void assertTokenTypeAndValue(Lexer& lexer, TokenType type,
    std::variant<int, float, std::string> value) {
    
    Token* token = lexer.getToken();
    GTEST_ASSERT_EQ(token->type, type);
    GTEST_ASSERT_EQ(token->value, value);
    delete token;
}

void assertTokenType(Lexer& lexer, TokenType type) {
    Token* token = lexer.getToken();
    GTEST_ASSERT_EQ(token->type, type);
    delete token;
}

TEST(Lexer, basic)
{
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    inStream << "int a = 10;";
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);
    

    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, IDENTIFIER);
    assertTokenType(interpreter.lexer, UNKNOWN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.lexer, UNKNOWN);
    assertTokenType(interpreter.lexer, EOT);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}