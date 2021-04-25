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

TEST(Lexer, basic) {
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    inStream << "int a = 10;";
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);
    

    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, IDENTIFIER);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, EOT);
}

TEST(Lexer, operators) {
    // This test does not test any real code in Matrixlang, but checks
    // if operators are parsed correctly.
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    inStream << "+ += ++ - -= -- * *= / /= % %= < <= > >= ! != = == && || \
    : ; , . { } [ ] ( )";
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);

    assertTokenType(interpreter.lexer, PLUS);
    assertTokenType(interpreter.lexer, PLUS_ASSIGN);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenType(interpreter.lexer, MINUS);
    assertTokenType(interpreter.lexer, MINUS_ASSIGN);
    assertTokenType(interpreter.lexer, DECREMENT);
    assertTokenType(interpreter.lexer, MULTIPLY);
    assertTokenType(interpreter.lexer, MULTIPLY_ASSIGN);
    assertTokenType(interpreter.lexer, DIVIDE);
    assertTokenType(interpreter.lexer, DIVIDE_ASSIGN);
    assertTokenType(interpreter.lexer, MODULO);
    assertTokenType(interpreter.lexer, MODULO_ASSIGN);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, LESS_EQUAL);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, MORE_EQUAL);
    assertTokenType(interpreter.lexer, NOT);
    assertTokenType(interpreter.lexer, NOT_EQUAL);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenType(interpreter.lexer, EQUAL);
    assertTokenType(interpreter.lexer, AND);
    assertTokenType(interpreter.lexer, OR);
    assertTokenType(interpreter.lexer, COLON);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenType(interpreter.lexer, DOT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, comments) {
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    inStream << "# This is a single line comment\n\
        ``` This is a multi\nline comment```\n\
        # This is yet another single line comment";
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "# This is a single line comment");
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "``` This is a multi\nline comment```");
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "# This is yet another single line comment");
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, stringConstants) {
    //No real Matrixlang code here either
    std::stringstream inStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    inStream << "\"String begin$ $string middle$ $string end\"\
        \"Full string\"";
    Interpreter interpreter = Interpreter(inStream, errStream, outStream);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_BEGIN, 
        "\"String begin$");
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_MID, 
        "$string middle$");
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_END, 
        "$string end\"");
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "\"Full string\"");
    assertTokenType(interpreter.lexer, EOT);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}