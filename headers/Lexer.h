#pragma once

#include <sstream>
#include <fstream>
#include <cmath>
#include <stack>
#include "Token.h"

class Lexer {
    std::stack<std::stringstream*> inStreamStack;
    std::stringstream& errStream;

    std::stringstream placeholderStringstream;
    
    int lineNumber = 1;
    int columnNumber = 0;
    char currentChar = '\0';
    bool isProcessed = false;

    Token* generateError(std::string errorMessage, bool skipCharacter = false);
    char getNextChar();
    void skipWhites();
    
    Token* buildEOT();
    Token* buildComment();
    Token* buildIdentifierOrKeyword();
    Token* buildNumber();
    Token* buildStringConstant();
    Token* buildBasicOperator(TokenType basicType, TokenType assignType,
        TokenType incrementType = UNKNOWN);
    Token* buildAndOr(TokenType type, char targetChar);
    Token* buildSpecialOperator();
    Token* buildOperator();
    Token* buildLexerCommand();

public:
    Lexer(): 
        errStream(placeholderStringstream) {}
    
    Lexer(std::stringstream& inStream, std::stringstream& errStream) : 
        errStream(errStream) {
            inStreamStack.push(new std::stringstream(std::move(inStream)));
            getNextChar();
        }

    bool getIsProcessed();    
    Token* getToken();
};