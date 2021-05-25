#include "AuxiliaryFunctionsLexer.h"

TEST (LexerSimple, basic) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "int a = 10;";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, EOT);
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

    assertTokenType(interpreter.parser.lexer, PLUS);
    assertTokenType(interpreter.parser.lexer, PLUS_ASSIGN);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenType(interpreter.parser.lexer, MINUS);
    assertTokenType(interpreter.parser.lexer, MINUS_ASSIGN);
    assertTokenType(interpreter.parser.lexer, DECREMENT);
    assertTokenType(interpreter.parser.lexer, MULTIPLY);
    assertTokenType(interpreter.parser.lexer, MULTIPLY_ASSIGN);
    assertTokenType(interpreter.parser.lexer, DIVIDE);
    assertTokenType(interpreter.parser.lexer, DIVIDE_ASSIGN);
    assertTokenType(interpreter.parser.lexer, MODULO);
    assertTokenType(interpreter.parser.lexer, MODULO_ASSIGN);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, LESS_EQUAL);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, MORE_EQUAL);
    assertTokenType(interpreter.parser.lexer, NOT);
    assertTokenType(interpreter.parser.lexer, NOT_EQUAL);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenType(interpreter.parser.lexer, EQUAL);
    assertTokenType(interpreter.parser.lexer, AND);
    assertTokenType(interpreter.parser.lexer, OR);
    assertTokenType(interpreter.parser.lexer, COLON);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenType(interpreter.parser.lexer, DOT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, EOT);
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
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        " This is a single line comment");
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        " This is a multi\nline comment");
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT,
        " Multiline with `` in the middle");
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        " This is yet another single line comment");
    assertTokenType(interpreter.parser.lexer, EOT);
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
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "My string literal");
    assertTokenType(interpreter.parser.lexer, EOT);
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
    assertTokenType(interpreter.parser.lexer, INCORRECT);
    assertTokenType(interpreter.parser.lexer, EOT);
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
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "\" \\ \n");
    assertTokenType(interpreter.parser.lexer, EOT);
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
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1234);
    assertTokenTypeAndValue(interpreter.parser.lexer, FLOAT_NUMBER, 24.0f);
    assertTokenTypeAndValue(interpreter.parser.lexer, FLOAT_NUMBER, 3.5f);
    assertTokenTypeAndValue(interpreter.parser.lexer, FLOAT_NUMBER, 103.23f);
    assertTokenType(interpreter.parser.lexer, EOT);
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
    while(!interpreter.parser.lexer.getIsProcessed())
        const std::optional<Token> token = interpreter.parser.lexer.getToken();
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
    
    interpreter.parser.lexer.getToken();
    
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
    while(!interpreter.parser.lexer.getIsProcessed())
        const std::optional<Token> token = interpreter.parser.lexer.getToken();
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
    assertTokenPosition(interpreter.parser.lexer, 1, 1);
    assertTokenPosition(interpreter.parser.lexer, 1, 5);
    assertTokenPosition(interpreter.parser.lexer, 1, 7);
    assertTokenPosition(interpreter.parser.lexer, 2, 1);
    assertTokenPosition(interpreter.parser.lexer, 2, 3);
    assertTokenPosition(interpreter.parser.lexer, 2, 4);
}

