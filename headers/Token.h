#include <variant>
#include <string>

enum TokenType {
    //basic
    IDENTIFIER,
    INT_NUMBER,
    FLOAT_NUMBER,
    STRING_CONSTANT,
    COMMENT,
    EOT,
    UNKNOWN,
    INCORRECT,

    //keywords
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

    //special
    COLON = ':',
    SEMICOLON = ';',
    COMMA = ',',
    DOT = '.',
    L_BRACKET = '{',
    R_BRACKET = '}',
    L_SQUARE_BRACKET = '[',
    R_SQUARE_BRACKET = ']',
    L_PARENT = '(',
    R_PARENT = ')',
    
    //operators
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    MODULO = '%',

    INCREMENT,
    DECREMENT,
    
    LESS_THAN = '<',
    LESS_EQUAL,
    MORE_THAN = '>',
    MORE_EQUAL,
    EQUAL,
    NOT_EQUAL,

    AND,
    OR,
    NOT = '!',

    ASSIGN = '=',
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

    Token() {}
    Token(TokenType type): type(type) {}
    Token(TokenType type, std::variant<int, float, std::string> value):
        type(type), value(value) {}
};