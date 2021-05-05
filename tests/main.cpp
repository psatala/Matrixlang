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

void assertTokenPosition(Lexer& lexer, int lineNumber, int columnNumber) {
    Token* token = lexer.getToken();
    GTEST_ASSERT_EQ(token->lineNumber, lineNumber);
    GTEST_ASSERT_EQ(token->columnNumber, columnNumber);
    delete token;
}

TEST (Lexer, basic) {
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

TEST (Lexer, operators) {
    // This test does not test any real code in Matrixlang, but checks
    // if operators are parsed correctly.
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

TEST (Lexer, comments) {
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

TEST (Lexer, stringConstants) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "\"String begin$ $string middle$ $string end\"\
        \"Full string\"";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
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

TEST (Lexer, numbers) {
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

TEST (Lexer, leadingZeroError) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "01";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    while(!interpreter.lexer.getIsProcessed()) {
        Token* token = interpreter.lexer.getToken();
        delete token;
    }
    GTEST_ASSERT_EQ(errStream.str(), 
        "Line: 1 Column: 2 -> Leading zeros not allowed\n");
}


TEST (Lexer, numberTooBigError) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "999999999999999999999999";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    
    delete interpreter.lexer.getToken();
    
    GTEST_ASSERT_EQ(errStream.str(), 
        "Line: 1 Column: 10 -> Number too big\n");
}

TEST (Lexer, andError) {
    //No real Matrixlang code here either
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << "\n\nif(1 == 1 & 3 > 2);\nprint(\"OK\");";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    while(!interpreter.lexer.getIsProcessed()) {
        Token* token = interpreter.lexer.getToken();
        delete token;
    }
    GTEST_ASSERT_EQ(errStream.str(), 
        "Line: 3 Column: 12 -> Got '&' but another '&' did not follow\n");
}

TEST (Lexer, tokenPosition) {
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


TEST (Lexer, fibonacciRec) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int fibonacciRec(int n) {
	    if(n == 0) { return 0; }
	    if(n == 1) { return 1; }
	    return fibonacciRec(n - 1) + fibonacciRec(n - 2);
    }
    
    int main() {
	    print(string(fibonacciRec(10))); #prints 55
	    return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "fibonacciRec");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    
    assertTokenType(interpreter.lexer, IF);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, IF);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "fibonacciRec");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, PLUS);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "fibonacciRec");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "fibonacciRec");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "prints 55");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, fibonacciIter) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int fibonacciIter(int n) {
	    #special cases
        if(n == 0) { return 0; }
	    if(n == 1) { return 1; }
	    
	    #declare variables
        int prevprev = 0;
	    int prev = 1;
	    int current;
	    
	    #main loop
        for(int i = 2; i < n; ++i) {
		    current = prev + prevprev;
		    prevprev = prev;
		    prev = current;
	    }
        
	    return current;
    }
    
    int main() {
	    print(string(fibonacciIter(10))); #prints 55
	    return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "fibonacciIter");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "special cases");

    assertTokenType(interpreter.lexer, IF);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, IF);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "declare variables");

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prevprev");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "main loop");

    assertTokenType(interpreter.lexer, FOR);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.lexer, PLUS);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prevprev");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prevprev");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "fibonacciIter");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "prints 55");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, findMax) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int findMax(Matrix<int>[n_cols, n_rows] matrix) {
    	#n_cols and n_rows always an int
        
        int max = INT_MIN; #environmental constant
	    for(int i = 0; i < n_cols; ++i) {
		    for(int j = 0; j < n_rows; ++j) {
			    if(matrix[i, j] > max) { max = matrix[i, j]; }
		    }
	    }
	    return max;
	    
    }
    
    int main() {
	    Matrix<int>[2, 2] matrix;
    	matrix[0, 0] = -3;
	    matrix[0, 1] = 3;
	    matrix[1, 0] = 14;
	    matrix[1, 1] = -14;
	    print(string(findMax(matrix))); #prints 14
	    return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "findMax");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, MATRIX);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "n_cols and n_rows always an int");
    
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "INT_MIN");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "environmental constant");

    assertTokenType(interpreter.lexer, FOR);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, FOR);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, IF);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, MATRIX);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenType(interpreter.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 14);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenType(interpreter.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 14);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "findMax");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "prints 14");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, concatStringMatrix) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(string concatStringMatrix(Matrix<string>[n_cols, n_rows] matrix) {
        string concatString = "";
        for(int i = 0; i < n_cols; ++i) {
		    for(int j = 0; j < n_rows; ++j) {
			    concatString += matrix[i, j];
		    }
	    }
	    return concatString;
    }
    
    int main() {
	    Matrix<string>[2, 2] matrix;
	    matrix[0, 0] = "ala ";
	    matrix[0, 1] = "ma ";
	    matrix[1, 0] = "kota ";
	    matrix[1, 1] = "i psa";
	    print(concatStringMatrix(matrix)); #prints "ala ma kota i psa"
	    return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, 
        "concatStringMatrix");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, MATRIX);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
  
    assertTokenType(interpreter.lexer, STRING);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "concatString");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, "\"\"");
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenType(interpreter.lexer, FOR);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
   
    assertTokenType(interpreter.lexer, FOR);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "concatString");
    assertTokenType(interpreter.lexer, PLUS_ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "concatString");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, MATRIX);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, "\"ala \"");
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, "\"ma \"");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, "\"kota \"");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, "\"i psa\"");    
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, 
        "concatStringMatrix");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "prints \"ala ma kota i psa\"");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, average) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(float average(Vector<float>[n] vector) {
    	float sum = 0.0;
    	for(int i = 0; i < n; ++i) {
    		sum += vector[i];
    	}
    	return sum / float(n);
    }

    int main() {
    	Vector<float>[2] vector;
    	vector[0] = 2;
    	vector[1] = 3;
    	print(string(average(vector))); #prints 2.5
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, FLOAT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "average");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, VECTOR);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, FLOAT);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, FLOAT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "sum");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, FLOAT_NUMBER, 0.0f);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, FOR);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "sum");
    assertTokenType(interpreter.lexer, PLUS_ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "sum");
    assertTokenType(interpreter.lexer, DIVIDE);
    assertTokenType(interpreter.lexer, FLOAT);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, VECTOR);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, FLOAT);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "average");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "prints 2.5");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);   
}

TEST (Lexer, printAgeDescription) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(void printAgeDescription(int age) {
    	```
    	In this function a switch statement is used to print information about 
        your age.
    	```
    	switch {
    	case age < 0:
    		print("Your age is incorrect");
    	case age < 18:
    		print("You are a kid.");
    	case age < 60:
    		print("You are an adult.");
    	default:
    		print("You are a pensioner.");
    	}
    }
    
    int main() {
    	int age = int(input());
    	printAgeDescription(age);
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, VOID);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, 
        "printAgeDescription");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
    R"(
    	In this function a switch statement is used to print information about 
        your age.
    	)");

    assertTokenType(interpreter.lexer, SWITCH);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, CASE);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, COLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "\"Your age is incorrect\"");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, CASE);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 18);
    assertTokenType(interpreter.lexer, COLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "\"You are a kid.\"");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, CASE);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 60);
    assertTokenType(interpreter.lexer, COLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "\"You are an adult.\"");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, DEFAULT);
    assertTokenType(interpreter.lexer, COLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "\"You are a pensioner.\"");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "input");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, 
        "printAgeDescription");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);   
}

TEST (Lexer, includeFile) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(@include "../examples/YearInfo.ml"

    int main() {
    	printYearInfo(2021);
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, LEXER_COMMAND);
    assertTokenType(interpreter.lexer, VOID);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "printYearInfo");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "currentYear");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);
    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT, 
        "\"Hello from year \"");
    assertTokenType(interpreter.lexer, PLUS);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "currentYear");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "printYearInfo");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2021);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);   
}

TEST (Lexer, copyByValue) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int addOne(int x) {
	    x++;
    	return x;
    }

    int main() {
    	int a = 3;

    	addOne(a);
    	print(string(a)); #prints 3
    
        a = addOne(a);
    	print(string(a)); #prints 4
    
    return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "addOne");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "x");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "x");
    assertTokenType(interpreter.lexer, INCREMENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "x");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "addOne");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "prints 3");

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "addOne");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "prints 4");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, copying) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int main() {
    	Vector<int>[2] vector;
    	print("0: $vector[0]$, 1: $vector[1]$\n"); #prints "0: 0, 1: 0"
    	vector[0] = 3;
    	vector[1] = 5;
    
    	Vector<int>[2] vectorCopy = vector;
    	print("0: $vectorCopy[0]$, 1: $vectorCopy[1]$\n"); #prints "0: 3, 1: 5"
        return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, VECTOR);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_BEGIN, "\"0: $");
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_MID, "$, 1: $");
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_END, R"($\n")");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        R"(prints "0: 0, 1: 0")");

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 5);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, VECTOR);
    assertTokenType(interpreter.lexer, LESS_THAN);
    assertTokenType(interpreter.lexer, INT);
    assertTokenType(interpreter.lexer, MORE_THAN);
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vectorCopy");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.lexer, SEMICOLON);
   
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_BEGIN, "\"0: $");
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vectorCopy");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_MID, "$, 1: $");
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "vectorCopy");
    assertTokenType(interpreter.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_END, R"($\n")");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        R"(prints "0: 3, 1: 5")");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, scope) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int main() {
    	{
    		int a = 10;
    	}
    	print(string(a));	#error - no such variable "a"
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "error - no such variable \"a\"");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, divideByZero) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int main() {
    	int a = 1 / 0;	#error - cannot divide by 0
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.lexer, DIVIDE);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "error - cannot divide by 0");
    
    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);

    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}

TEST (Lexer, strongTyping) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int main() {
    	int a = 0;
    	print(string(a)); #ok
    	print("$a$"); #ok
    	print(a);	#error - value to print must be of type string
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, L_BRACKET);

    assertTokenType(interpreter.lexer, INT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenType(interpreter.lexer, STRING);
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "ok");

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_BEGIN, "\"$");
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenTypeAndValue(interpreter.lexer, STRING_CONSTANT_END, "$\"");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, "ok");

    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.lexer, R_PARENT);
    assertTokenType(interpreter.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.lexer, COMMENT, 
        "error - value to print must be of type string");

    assertTokenType(interpreter.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.lexer, SEMICOLON);
    
    assertTokenType(interpreter.lexer, R_BRACKET);
    assertTokenType(interpreter.lexer, EOT);
}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}