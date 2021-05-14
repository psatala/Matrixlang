#pragma once

#include <variant>
#include <string>

enum TokenType {
    // one character operators
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    MODULO = '%',
    LESS_THAN = '<',
    MORE_THAN = '>',
    NOT = '!',
    ASSIGN = '=',

    // special
    COLON = ':',
    SEMICOLON = ';',
    COMMA = ',',
    DOT = '.',
    L_SQUARE_BRACKET = '[',
    R_SQUARE_BRACKET = ']',
    L_PARENT = '(',
    R_PARENT = ')',
    L_BRACKET = '{',
    R_BRACKET = '}',

    // make the rest non printable
    UNUSED = 128,

    // basic
    IDENTIFIER,
    INT_NUMBER,
    FLOAT_NUMBER,
    STRING_CONSTANT,
    COMMENT,
    EOT,
    UNKNOWN,
    INCORRECT,
    LEXER_COMMAND,

    // keywords
    IF,
    ELSE,
    SWITCH,
    CASE,
    DEFAULT,
    FOR,
    RETURN,
    INT,
    FLOAT,
    STRING,
    VECTOR,
    MATRIX,
    VOID,

    // other operators
    INCREMENT,
    DECREMENT,
    
    LESS_EQUAL,
    MORE_EQUAL,
    EQUAL,
    NOT_EQUAL,

    AND,
    OR,
    
    PLUS_ASSIGN,
    MINUS_ASSIGN,
    MULTIPLY_ASSIGN,
    DIVIDE_ASSIGN,
    MODULO_ASSIGN

};

class Token {
public:
    TokenType type;
    std::variant<int, float, std::string> value;
    int lineNumber = -1;
    int columnNumber = -1;

    Token() {}
    Token(TokenType type): type(type) {}
    Token(TokenType type, std::variant<int, float, std::string> value):
        type(type), value(value) {}

    void setPosition(const int& lineNumber, const int& columnNumber) {
        this->lineNumber = lineNumber;
        this->columnNumber = columnNumber;
    }
};