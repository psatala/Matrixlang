#pragma once

#include <sstream>
#include <fstream>
#include <memory>
#include <cmath>
#include <stack>
#include <limits>
#include <optional>

#include "Token.h"

class Lexer {
    std::stack< std::unique_ptr<std::istream> > inStreamStack;
    std::ostream& errStream;

    std::stringstream placeholderStringstream;
    
    int lineNumber = 1;
    int columnNumber = 0;
    char currentChar = '\0';
    bool isProcessed = false;

    Token* generateError(std::string errorMessage, bool skipCharacter = false);
    char getNextChar();
    void skipWhites();
    std::optional<char> escapeCharacter(char previousCharacter, 
        char currentCharacter);
    
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
    
    Lexer(std::unique_ptr<std::istream> inStream, std::ostream& errStream) : 
        errStream(errStream) {
            inStreamStack.push(std::move(inStream));
            getNextChar();
        }

    bool getIsProcessed() const;
    Token* getToken();
};