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

    std::optional<Token> generateError(std::string errorMessage, 
        bool skipCharacter = false);
    char getNextChar();
    void skipWhites();
    std::optional<char> escapeCharacter(char previousCharacter, 
        char currentCharacter);
    
    std::optional<Token> buildEOT();
    std::optional<Token> buildComment();
    std::optional<Token> buildIdentifierOrKeyword();
    std::optional<Token> buildNumber();
    std::optional<Token> buildStringConstant();
    std::optional<Token> buildBasicOperator(TokenType basicType, 
        TokenType assignType, TokenType incrementType = UNKNOWN);
    std::optional<Token> buildAndOr(TokenType type, char targetChar);
    std::optional<Token> buildSpecialOperator();
    std::optional<Token> buildOperator();
    std::optional<Token> buildLexerCommand();

public:
    Lexer(): 
        errStream(placeholderStringstream) {}
    
    Lexer(std::unique_ptr<std::istream> inStream, std::ostream& errStream) : 
        errStream(errStream) {
            inStreamStack.push(std::move(inStream));
            getNextChar();
        }

    bool getIsProcessed() const;
    std::optional<Token> getToken();
};