#include "AuxiliaryFunctionsLexer.h"

TEST (LexerComplex, strongTyping) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int main() {
        int a = 0;
        float b = int(a); #ok
        float c = a; #error
    	return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "b");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "ok");

    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "c");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "error");
    
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, fibonacciRec) {
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
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "fibonacciRec");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    
    assertTokenType(interpreter.parser.lexer, IF);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, IF);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "fibonacciRec");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, PLUS);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "fibonacciRec");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "fibonacciRec");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "prints 55");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, fibonacciIter) {
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
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "fibonacciIter");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "special cases");

    assertTokenType(interpreter.parser.lexer, IF);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, IF);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, EQUAL);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        "declare variables");

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prevprev");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "main loop");

    assertTokenType(interpreter.parser.lexer, FOR);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.parser.lexer, PLUS);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prevprev");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prevprev");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "prev");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "current");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "fibonacciIter");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "prints 55");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, findMax) {
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
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "findMax");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, MATRIX);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        "n_cols and n_rows always an int");
    
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "INT_MIN");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        "environmental constant");

    assertTokenType(interpreter.parser.lexer, FOR);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, FOR);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, IF);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "max");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, MATRIX);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenType(interpreter.parser.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 14);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenType(interpreter.parser.lexer, MINUS);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 14);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "findMax");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "prints 14");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, concatStringMatrix) {
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
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "concatStringMatrix");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, MATRIX);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
  
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "concatString");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenType(interpreter.parser.lexer, FOR);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_cols");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
   
    assertTokenType(interpreter.parser.lexer, FOR);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n_rows");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "concatString");
    assertTokenType(interpreter.parser.lexer, PLUS_ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "j");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "concatString");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, MATRIX);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "ala ");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "ma ");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "kota ");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, COMMA);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "i psa");    
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "concatStringMatrix");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "matrix");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        "prints \"ala ma kota i psa\"");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, average) {
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
    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "average");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, VECTOR);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "sum");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, FLOAT_NUMBER, 0.0f);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, FOR);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "sum");
    assertTokenType(interpreter.parser.lexer, PLUS_ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "i");
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "sum");
    assertTokenType(interpreter.parser.lexer, DIVIDE);
    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "n");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, VECTOR);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, FLOAT);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "average");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "prints 2.5");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);   
}

TEST (LexerComplex, printAgeDescription) {
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
    assertTokenType(interpreter.parser.lexer, VOID);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "printAgeDescription");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
    R"(
    	In this function a switch statement is used to print information about 
        your age.
    	)");

    assertTokenType(interpreter.parser.lexer, SWITCH);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, CASE);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, COLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "Your age is incorrect");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, CASE);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 18);
    assertTokenType(interpreter.parser.lexer, COLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "You are a kid.");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, CASE);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 60);
    assertTokenType(interpreter.parser.lexer, COLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "You are an adult.");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, DEFAULT);
    assertTokenType(interpreter.parser.lexer, COLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "You are a pensioner.");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "input");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "printAgeDescription");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "age");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);   
}

TEST (LexerComplex, includeFile) {
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
    assertTokenType(interpreter.parser.lexer, LEXER_COMMAND);
    assertTokenType(interpreter.parser.lexer, VOID);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "printYearInfo");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "currentYear");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);
    
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, 
        "Hello from year ");
    assertTokenType(interpreter.parser.lexer, PLUS);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "currentYear");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "printYearInfo");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2021);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);   
}

TEST (LexerComplex, copyByValue) {
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
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "addOne");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "x");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "x");
    assertTokenType(interpreter.parser.lexer, INCREMENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "x");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "addOne");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "prints 3");

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "addOne");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, "prints 4");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, copying) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << 
    R"(int main() {
    	Vector<int>[2] vector;
    	print("0: "vector[0]", 1: "vector[1]"\n"); #prints "0: 0, 1: 0"
    	vector[0] = 3;
    	vector[1] = 5;
    
    	Vector<int>[2] vectorCopy = vector;
    	print("0: "vectorCopy[0]", 1: "vectorCopy[1]"\n"); #prints "0: 3, 1: 5"
        return 0;
    })";
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, VECTOR);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "0: ");
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, ", 1: ");
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "\n");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        R"(prints "0: 0, 1: 0")");

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 3);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 5);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, VECTOR);
    assertTokenType(interpreter.parser.lexer, LESS_THAN);
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenType(interpreter.parser.lexer, MORE_THAN);
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 2);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vectorCopy");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vector");
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
   
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "0: ");
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vectorCopy");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, ", 1: ");
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "vectorCopy");
    assertTokenType(interpreter.parser.lexer, L_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, R_SQUARE_BRACKET);
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "\n");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        R"(prints "0: 3, 1: 5")");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, scope) {
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
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 10);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);

    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "print");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, STRING);
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        "error - no such variable \"a\"");

    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

TEST (LexerComplex, divideByZero) {
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
    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "main");
    assertTokenType(interpreter.parser.lexer, L_PARENT);
    assertTokenType(interpreter.parser.lexer, R_PARENT);
    assertTokenType(interpreter.parser.lexer, L_BRACKET);

    assertTokenType(interpreter.parser.lexer, INT);
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, "a");
    assertTokenType(interpreter.parser.lexer, ASSIGN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 1);
    assertTokenType(interpreter.parser.lexer, DIVIDE);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);
    assertTokenTypeAndValue(interpreter.parser.lexer, COMMENT, 
        "error - cannot divide by 0");
    
    assertTokenType(interpreter.parser.lexer, RETURN);
    assertTokenTypeAndValue(interpreter.parser.lexer, INT_NUMBER, 0);
    assertTokenType(interpreter.parser.lexer, SEMICOLON);

    assertTokenType(interpreter.parser.lexer, R_BRACKET);
    assertTokenType(interpreter.parser.lexer, EOT);
}

