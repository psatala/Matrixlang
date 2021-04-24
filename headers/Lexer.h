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
                << " Leading zeros not allowed";
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

    Token* buildBasicOperator(TokenType basicType, TokenType assignType,
        TokenType incrementType = UNKNOWN) {

            if(currentChar != basicType)
                return nullptr;

            getNextChar();
            if('=' == currentChar) {
                getNextChar();
                return new Token(assignType);
            }
            if(incrementType != UNKNOWN && currentChar == basicType) {
                getNextChar();
                return new Token(incrementType);
            }
            return new Token(basicType);
        }

    Token* buildAndOr(TokenType type, char targetChar) {
        if(targetChar != currentChar)
            return nullptr;

        getNextChar();
        if(targetChar == currentChar){
            getNextChar();
            return new Token(type);
        }
        errStream << "Line: " << lineNumber << " Column: " << columnNumber 
            << " Got '" << targetChar << "' but another '" << targetChar 
            << "' did not follow";
        return new Token(INCORRECT);
        
    }

    Token* buildSpecialOperator() {
        if( currentChar == COLON            ||
            currentChar == SEMICOLON        ||
            currentChar == COMMA            ||
            currentChar == DOT              ||
            currentChar == L_BRACKET        ||
            currentChar == R_BRACKET        ||
            currentChar == L_SQUARE_BRACKET ||
            currentChar == R_SQUARE_BRACKET ||
            currentChar == L_PARENT         ||
            currentChar == R_PARENT         ) {
            
            TokenType type = static_cast<TokenType>(currentChar);
            getNextChar();
            return new Token(type);
        }
            

        return nullptr;
    }

    Token* buildOperator() {
        Token* token;
        token = buildBasicOperator(PLUS, PLUS_ASSIGN, INCREMENT);
        if(token) return token;
        token = buildBasicOperator(MINUS, MINUS_ASSIGN, DECREMENT);
        if(token) return token;
        token = buildBasicOperator(MULTIPLY, MULTIPLY_ASSIGN);
        if(token) return token;
        token = buildBasicOperator(DIVIDE, DIVIDE_ASSIGN);
        if(token) return token;
        token = buildBasicOperator(MODULO, MODULO_ASSIGN);
        if(token) return token;
        token = buildBasicOperator(LESS_THAN, LESS_EQUAL);
        if(token) return token;
        token = buildBasicOperator(MORE_THAN, MORE_EQUAL);
        if(token) return token;
        token = buildBasicOperator(NOT, NOT_EQUAL);
        if(token) return token;
        token = buildBasicOperator(ASSIGN, EQUAL);
        if(token) return token;
        
        token = buildAndOr(AND, '&');
        if(token) return token;
        token = buildAndOr(OR, '|');
        if(token) return token;

        token = buildSpecialOperator();
        if(token) return token;

        return nullptr;
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

        token = buildOperator();
        if(token) return token;

        getNextChar();
        return new Token(UNKNOWN);
    }
    
};