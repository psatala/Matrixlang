#include "AuxiliaryFunctionsLexer.h"

TEST (LexerSimple, basic) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "int a = 10;";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (LexerSimple, operatorSequence) {
    // This test does not test any real code in Matrixlang, but checks
    // if a sequence of operators is parsed correctly.
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "+ += ++ - -= -- * *= / /= % %= < <= > >= ! != = == && || \
    : ; , . { } [ ] ( )";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);

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

TEST (LexerSimple, comments) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "# This is a single line comment\n\
        ``` This is a multi\nline comment```\n\
        ``` Multiline with `` in the middle```\n\
        # This is yet another single line comment";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        " This is a single line comment");
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        " This is a multi\nline comment");
    assertTokenTypeAndValue(interpreter.lexer, COMMENT,
        " Multiline with `` in the middle");
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        " This is yet another single line comment");
    assertTokenType(interpreter.lexer, EOT);
}

TEST (LexerSimple, stringConstants) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "\"My string literal\"";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "My string literal");
    assertTokenType(interpreter.lexer, EOT);
}

TEST (LexerSimple, unterminatedString)
{
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "\"abc";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INCORRECT);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (LexerSimple, escapingCharacters)
{
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << R"("\" \\ \n")";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, "\" \\ \n");
    assertTokenType(interpreter.lexer, EOT);
}

TEST (LexerSimple, numbers) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(1234
        24.
        3.5
        103.23
    )";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1234);
    assertTokenTypeAndValue(interpreter.lexer, FLOAT_NUMBER, 24.0f);
    assertTokenTypeAndValue(interpreter.lexer, FLOAT_NUMBER, 3.5f);
    assertTokenTypeAndValue(interpreter.lexer, FLOAT_NUMBER, 103.23f);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (LexerSimple, leadingZeroError) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "01";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    while(!interpreter.lexer.getIsProcessed())
        const std::optional<Token> token = interpreter.lexer.getToken();
    GTEST_ASSERT_EQ(errStream.str(), 
        "Line: 1 Column: 2 -> Leading zeros not allowed\n");
}


TEST (LexerSimple, numberTooBigError) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "999999999999999999999999";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    
    interpreter.lexer.getToken();
    
    GTEST_ASSERT_EQ(errStream.str(), 
        "Line: 1 Column: 10 -> Number too big\n");
}

TEST (LexerSimple, andError) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "\n\nif(1 == 1 & 3 > 2);\nprint(\"OK\");";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    while(!interpreter.lexer.getIsProcessed())
        const std::optional<Token> token = interpreter.lexer.getToken();
    GTEST_ASSERT_EQ(errStream.str(), 
        "Line: 3 Column: 12 -> Got '&' but another '&' did not follow\n");
}

TEST (LexerSimple, tokenPosition) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "int a = \n10;";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenPosition(interpreter.lexer, 1, 1);
    assertTokenPosition(interpreter.lexer, 1, 5);
    assertTokenPosition(interpreter.lexer, 1, 7);
    assertTokenPosition(interpreter.lexer, 2, 1);
    assertTokenPosition(interpreter.lexer, 2, 3);
    assertTokenPosition(interpreter.lexer, 2, 4);
}

