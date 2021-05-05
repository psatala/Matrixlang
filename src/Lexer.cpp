#include "../headers/Lexer.h"




////////////////////////////////////////////////////////////////////////////////
//                            PRIVATE METHODS                                 //
////////////////////////////////////////////////////////////////////////////////


std::optional<Token> Lexer::generateError(std::string errorMessage, 
    bool skipCharacter) {
    
    errStream << "Line: " << lineNumber << " Column: " << columnNumber 
        << " -> " << errorMessage << "\n";
    if(skipCharacter)
        getNextChar();
    return Token(INCORRECT);
}



char Lexer::getNextChar() {
    currentChar = inStreamStack.top()->get();
    
    if('\n' == currentChar) {
        lineNumber++;
        columnNumber = 0;
        return currentChar;
    }

    columnNumber++;
    return currentChar;
}
    


void Lexer::skipWhites() {
    while(isspace(currentChar))
        getNextChar();
}



// converts current char into an escaped character based on previous character
// used in string parsing
std::optional<char> Lexer::escapeCharacter(char previousCharacter, 
    char currentCharacter) {
    if('\\' != previousCharacter)
        return std::nullopt;
    
    if('\\' == currentCharacter)
        return '\\';
    if('n' == currentCharacter)
        return '\n';
    if('\"' == currentCharacter)
        return '\"';

    return std::nullopt;
}



std::optional<Token> Lexer::buildEOT() {
    while(-1 == currentChar) {
        inStreamStack.pop();
        
        if(inStreamStack.empty()) {
            isProcessed = true;
            return Token(EOT);
        }

        getNextChar();
        skipWhites();
    }   
    return std::nullopt;
}

std::optional<Token> Lexer::buildComment() {
    //single line
    if('#' == currentChar) {
        int currentLineNumber = lineNumber;
        std::string text;
        getNextChar();
        while(lineNumber == currentLineNumber && -1 != currentChar) {
            text += currentChar;
            getNextChar();
        }
        return Token(COMMENT, text);
    }

    //multi line
    if('`' == currentChar){
        std::string text;
        for(int i = 0; i < 2; ++i) {
            getNextChar();
            if('`' != currentChar)
                return generateError("Beginning of comment: expected a '`'",
                    true);
        }
        //comment now opened
        getNextChar();
        bool isClosed = false;
        int backtickCount = 0;
        while(!isClosed) {
            text += currentChar;
            if(-1 == currentChar)
                return Token(INCORRECT);
            if('`' != currentChar) {
                backtickCount = 0;
                getNextChar();
                continue;
            }
            ++backtickCount;
            getNextChar();
            if(3 == backtickCount)
                isClosed = true;
        }

        //eliminate backtics from comment
        text = text.substr(0, text.size() - 3);

        getNextChar();
        return Token(COMMENT, text);
    }

    //no comment
    return std::nullopt;
}



std::optional<Token> Lexer::buildIdentifierOrKeyword() {
    std::string identifierString;
    if(!isalpha(currentChar))
        return std::nullopt;

    do {
        identifierString += currentChar;
        getNextChar();
    } while(isalnum(currentChar) || '_' == currentChar);

    if("if"         == identifierString)    return Token(IF);
    if("else"       == identifierString)    return Token(ELSE);
    if("switch"     == identifierString)    return Token(SWITCH);
    if("case"       == identifierString)    return Token(CASE);
    if("default"    == identifierString)    return Token(DEFAULT);
    if("for"        == identifierString)    return Token(FOR);
    if("return"     == identifierString)    return Token(RETURN);
    if("int"        == identifierString)    return Token(INT);
    if("float"      == identifierString)    return Token(FLOAT);
    if("string"     == identifierString)    return Token(STRING);
    if("Vector"     == identifierString)    return Token(VECTOR);
    if("Matrix"     == identifierString)    return Token(MATRIX);
    if("void"       == identifierString)    return Token(VOID);

    return Token(IDENTIFIER, identifierString);
}



std::optional<Token> Lexer::buildNumber() {
    if(!isdigit(currentChar))
        return std::nullopt;
    
    int integerPart = currentChar - '0';
    getNextChar();
    
    if(isdigit(currentChar) && 0 == integerPart)
        return generateError("Leading zeros not allowed");
    
    while(isdigit(currentChar)) {
        if((std::numeric_limits<int>::max() - (currentChar - '0')) / 10 
            < integerPart)
            return generateError("Number too big");
        integerPart = integerPart * 10 + currentChar - '0';
        getNextChar();
    }
    
    if('.' != currentChar)
        return Token(INT_NUMBER, integerPart);
    
    //float part
    int floatingPointPart = 0;
    int decimalPlaces = 0;
    bool isOverflown = false;
    getNextChar();
    while(isdigit(currentChar)) {
        
        if((std::numeric_limits<int>::max() - (currentChar - '0')) / 10 
            < floatingPointPart)
            isOverflown = true;
        
        if(!isOverflown) {
            floatingPointPart = floatingPointPart * 10 + currentChar - '0';
            ++decimalPlaces;
        }
        getNextChar();
    }
    float fullNumber = static_cast<float>(integerPart) 
        + static_cast<float>(floatingPointPart) 
        / pow(10, static_cast<float>(decimalPlaces));
    return Token(FLOAT_NUMBER, fullNumber);
}



std::optional<Token> Lexer::buildStringConstant() {
    std::string text;
    
    if('\"' != currentChar)
        return std::nullopt;

    getNextChar();

    // process first char - this is separate from the main loop to simplify
    // escaping code
    if(-1 == currentChar)
        return Token(INCORRECT);
    if('\"' == currentChar) {
        getNextChar();
        return Token(STRING_CONSTANT, "");
    }

    text += currentChar;
    getNextChar();

    while(true) {
        if(-1 == currentChar)
            return Token(INCORRECT);

        //if unescaped quote then end of string
        if('\"' == currentChar && '\\' != text.back())
            break;

        std::optional<char> tempChar = escapeCharacter(text.back(), 
            currentChar);
        if(tempChar) {
            text.pop_back();
            currentChar = tempChar.value();
        }

        text += currentChar;
        getNextChar();
    }
    
    getNextChar();
    return Token(STRING_CONSTANT, text);
}



std::optional<Token> Lexer::buildBasicOperator(TokenType basicType, 
    TokenType assignType, TokenType incrementType) {

        if(currentChar != basicType)
            return std::nullopt;

        getNextChar();
        if('=' == currentChar) {
            getNextChar();
            return Token(assignType);
        }
        if(incrementType != UNKNOWN && currentChar == basicType) {
            getNextChar();
            return Token(incrementType);
        }
        return Token(basicType);
    }



std::optional<Token> Lexer::buildAndOr(TokenType type, char targetChar) {
    if(targetChar != currentChar)
        return std::nullopt;

    getNextChar();
    if(targetChar == currentChar){
        getNextChar();
        return Token(type);
    }
    return generateError("Got '" + std::string(1, targetChar) + 
        "' but another '"+ std::string(1, targetChar) + "' did not follow");      
}



std::optional<Token> Lexer::buildSpecialOperator() {
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
        return Token(type);
    }
        
    return std::nullopt;
}



std::optional<Token> Lexer::buildOperator() {
    std::optional<Token> token;

    if(
        (token = buildBasicOperator(PLUS, PLUS_ASSIGN, INCREMENT))    ||
        (token = buildBasicOperator(MINUS, MINUS_ASSIGN, DECREMENT))  ||
        (token = buildBasicOperator(MULTIPLY, MULTIPLY_ASSIGN))       ||
        (token = buildBasicOperator(DIVIDE, DIVIDE_ASSIGN))           ||
        (token = buildBasicOperator(MODULO, MODULO_ASSIGN))           ||
        (token = buildBasicOperator(LESS_THAN, LESS_EQUAL))           ||
        (token = buildBasicOperator(MORE_THAN, MORE_EQUAL))           ||
        (token = buildBasicOperator(NOT, NOT_EQUAL))                  ||
        (token = buildBasicOperator(ASSIGN, EQUAL))                   ||
        (token = buildAndOr(AND, '&'))                                ||
        (token = buildAndOr(OR, '|'))                                 ||
        (token = buildSpecialOperator())                              
    )
        return token;

    return std::nullopt;
}



std::optional<Token> Lexer::buildLexerCommand() {
    if('@' != currentChar)
        return std::nullopt;

    getNextChar();
    std::optional<Token> commandToken = buildIdentifierOrKeyword();
    if(!commandToken)
        return generateError("Expected a lexer command");
    if(IDENTIFIER != commandToken->type || 
        "include" != std::get<std::string>(commandToken->value)) {
        return generateError("No such lexer command");
    }

    skipWhites();
    std::optional<Token> pathToken = buildStringConstant();
    if(!pathToken)
        return generateError("Expected path to file");
    if(STRING_CONSTANT != pathToken->type)
        return generateError("Expected path to file");
    
    
    std::string path = std::get<std::string>(pathToken->value);
    
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();
    fileStream->open(path, std::ifstream::in);

    if(!fileStream)
        return Token(INCORRECT);
    
    inStreamStack.push(std::move(fileStream));

    return Token(LEXER_COMMAND);
}



////////////////////////////////////////////////////////////////////////////////
//                            PUBLIC METHODS                                  //
////////////////////////////////////////////////////////////////////////////////



bool Lexer::getIsProcessed() const {
    return isProcessed;
}



std::optional<Token> Lexer::getToken() {
    std::optional<Token> token;

    skipWhites();

    const int tokenLineNumber = lineNumber;
    const int tokenColumnNumber = columnNumber;

    if (
        (token = buildEOT())                   ||
        (token = buildLexerCommand())          ||
        (token = buildComment())               ||
        (token = buildNumber())                ||
        (token = buildStringConstant())        ||
        (token = buildIdentifierOrKeyword())   ||
        (token = buildOperator())
    ) {
        token->setPosition(tokenLineNumber, tokenColumnNumber);
        return token;
    }

    getNextChar();
    return Token(UNKNOWN);
}
