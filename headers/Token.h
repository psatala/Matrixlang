#include <variant>
#include <string>

enum TokenType {
    //basic
    IDENTIFIER,
    INT_NUMBER,
    FLOAT_NUMBER,
    STRING_CONSTANT,
    STRING_CONSTANT_BEGIN,
    STRING_CONSTANT_MID,
    STRING_CONSTANT_END,
    COMMENT,
    EOT,
    UNKNOWN,
    INCORRECT,
    LEXER_COMMAND,

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
    VOID,

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
    int lineNumber = -1;
    int columnNumber = -1;

    Token() {}
    Token(TokenType type): type(type) {}
    Token(TokenType type, std::variant<int, float, std::string> value):
        type(type), value(value) {}

    Token* setPosition(int lineNumber, int columnNumber) {
        this->lineNumber = lineNumber;
        this->columnNumber = columnNumber;
        return this;
    }
};