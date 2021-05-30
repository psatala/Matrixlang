#include "AuxiliaryFunctionsLexer.h"
#include "TestPrograms.h"

TEST (LexerComplex, fibonacciRec) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << TestPrograms::fibonacciRec;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToString");
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
    *inStream << TestPrograms::fibonacciIter;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToString");
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
    *inStream << TestPrograms::findMax;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToString");
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
    *inStream << TestPrograms::concatStringMatrix;
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
    *inStream << TestPrograms::average;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToFloat");
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "floatToString");
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
    *inStream << TestPrograms::printAgeDescription;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "stringToInt");
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
    *inStream << TestPrograms::includeFile;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "currentYear");
    assertTokenTypeAndValue(interpreter.parser.lexer, STRING_CONSTANT, "");
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
    *inStream << TestPrograms::copyByValue;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToString");
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToString");
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
    *inStream << TestPrograms::copying;
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
    *inStream << TestPrograms::scope;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "intToString");
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
    *inStream << TestPrograms::divideByZero;
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

TEST (LexerComplex, strongTyping) {
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    *inStream << TestPrograms::strongTyping;
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
    assertTokenTypeAndValue(interpreter.parser.lexer, IDENTIFIER, 
        "floatToInt");
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
