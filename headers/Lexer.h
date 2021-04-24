#pragma once

#include <sstream>
#include <cmath>

#include "Token.h"

class Lexer {
    std::stringstream& inStream;
    std::stringstream& errStream;

    std::stringstream placeholderStringstream;
    
    int lineNumber = 1;
    int columnNumber = 1;
    char currentChar = '\0';

    char getNextChar() {
        currentChar = inStream.get();
        
        if('\n' == currentChar) {
            lineNumber++;
            columnNumber = 1;
            return currentChar;
        }

        columnNumber++;
        return currentChar;
    }
    
    void skipWhites() {
        while(isspace(currentChar))
            getNextChar();
    }

    Token* buildEOT() {
        if(-1 == currentChar)
            return new Token(EOT);
        return nullptr;
    }

    Token* buildIdentifierOrKeyword() {
        std::string identifierString;
        if(!isalpha(currentChar))
            return nullptr;

        do {
            identifierString += currentChar;
            getNextChar();
        } while(isalnum(currentChar) || '_' == currentChar);

        if("if"         == identifierString)    return new Token(IF);
        if("else"       == identifierString)    return new Token(ELSE);
        if("switch"     == identifierString)    return new Token(SWITCH);
        if("case"       == identifierString)    return new Token(CASE);
        if("default"    == identifierString)    return new Token(DEFAULT);
        if("for"        == identifierString)    return new Token(FOR);
        if("return"     == identifierString)    return new Token(RETURN);
        if("int"        == identifierString)    return new Token(INT);
        if("float"      == identifierString)    return new Token(FLOAT);
        if("string"     == identifierString)    return new Token(STRING);
        if("Vector"     == identifierString)    return new Token(VECTOR);
        if("Matrix"     == identifierString)    return new Token(MATRIX);

        return new Token(IDENTIFIER, identifierString);
    }

    Token* buildNumber() {
        if(!isdigit(currentChar))
            return nullptr;
        
        int integerPart = currentChar - '0';
        getNextChar();
        
        if(isdigit(currentChar) && 0 == integerPart) {
            errStream << "Line: " << lineNumber << " Column: " << columnNumber 
                << " Leading zeros not allowed!";
            return new Token(INCORRECT);
        }
        
        //TODO: limit int value
        while(isdigit(currentChar)) {
            integerPart = integerPart * 10 + currentChar - '0';
            getNextChar();
        }
        
        if('.' != currentChar)
            return new Token(INT_NUMBER, integerPart);
        
        //float part
        float floatingPointPart = 0.0;
        int decimalPlaces = 1;
        while(isdigit(currentChar)) {
            floatingPointPart += (currentChar - '0') * pow(10, -decimalPlaces);
            ++decimalPlaces;
            getNextChar();
        }

        float fullNumber = static_cast<float>(integerPart) + floatingPointPart;
        return new Token(FLOAT_NUMBER, fullNumber);

        
        
    }

public:
    Lexer(): 
        inStream(placeholderStringstream), errStream(placeholderStringstream) {}
    
    Lexer(std::stringstream& inStream, std::stringstream& errStream) : 
        inStream(inStream), errStream(errStream) {
            getNextChar();
        }

    Token* getToken() {
        Token* token;

        skipWhites();

        token = buildEOT();
        if(token) return token;

        token = buildNumber();
        if(token) return token;

        token = buildIdentifierOrKeyword();
        if(token) return token;      

        getNextChar();
        return new Token(UNKNOWN);
    }
    
};