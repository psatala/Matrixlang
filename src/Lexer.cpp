#include "../headers/Lexer.h"




////////////////////////////////////////////////////////////////////////////////
//                            PRIVATE METHODS                                 //
////////////////////////////////////////////////////////////////////////////////


Token* Lexer::generateError(std::string errorMessage, bool skipCharacter) {
    errStream << "Line: " << lineNumber << " Column: " << columnNumber 
        << " -> " << errorMessage << "\n";
    if(skipCharacter)
        getNextChar();
    return new Token(INCORRECT);
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



Token* Lexer::buildEOT() {
    while(-1 == currentChar) {
        inStreamStack.pop();
        
        if(inStreamStack.empty()) {
            isProcessed = true;
            return new Token(EOT);
        }

        getNextChar();
        skipWhites();
    }   
    return nullptr;
}

Token* Lexer::buildComment() {
    //single line
    if('#' == currentChar) {
        int currentLineNumber = lineNumber;
        std::string text;
        getNextChar();
        while(lineNumber == currentLineNumber && -1 != currentChar) {
            text += currentChar;
            getNextChar();
        }
        return new Token(COMMENT, text);
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
                return new Token(INCORRECT);
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
        return new Token(COMMENT, text);
    }

    //no comment
    return nullptr;
}



Token* Lexer::buildIdentifierOrKeyword() {
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
    if("void"       == identifierString)    return new Token(VOID);

    return new Token(IDENTIFIER, identifierString);
}



Token* Lexer::buildNumber() {
    if(!isdigit(currentChar))
        return nullptr;
    
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
        return new Token(INT_NUMBER, integerPart);
    
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
    return new Token(FLOAT_NUMBER, fullNumber);
}



Token* Lexer::buildStringConstant() {
    std::string text;
    char startChar = currentChar;
    if('\"' != currentChar && '$' != currentChar)
        return nullptr;

    text += currentChar;
    getNextChar();
    while('\"' != currentChar && '$' != currentChar) {
        text += currentChar;
        getNextChar();
    }
    text += currentChar;
    if('\"' == startChar && '\"' == currentChar) {
        getNextChar();
        return new Token(STRING_CONSTANT, text);
    }
    if('\"' == startChar && '$' == currentChar) {
        getNextChar();
        return new Token(STRING_CONSTANT_BEGIN, text);
    }
    if('$' == startChar && '$' == currentChar) {
        getNextChar();
        return new Token(STRING_CONSTANT_MID, text);
    }
    getNextChar();
    return new Token(STRING_CONSTANT_END, text);
    
}



Token* Lexer::buildBasicOperator(TokenType basicType, TokenType assignType,
    TokenType incrementType) {

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



Token* Lexer::buildAndOr(TokenType type, char targetChar) {
    if(targetChar != currentChar)
        return nullptr;

    getNextChar();
    if(targetChar == currentChar){
        getNextChar();
        return new Token(type);
    }
    return generateError("Got '" + std::string(1, targetChar) + 
        "' but another '"+ std::string(1, targetChar) + "' did not follow");      
}



Token* Lexer::buildSpecialOperator() {
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



Token* Lexer::buildOperator() {
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



Token* Lexer::buildLexerCommand() {
    if('@' != currentChar)
        return nullptr;

    getNextChar();
    Token* commandToken = buildIdentifierOrKeyword();
    if(IDENTIFIER != commandToken->type || 
        "include" != std::get<std::string>(commandToken->value)) {
        delete commandToken;
        return generateError("No such lexer command");
    }
    delete commandToken;

    skipWhites();
    Token* pathToken = buildStringConstant();
    if(STRING_CONSTANT != pathToken->type) {
        delete pathToken;
        return generateError("Expected path to file");
    }
    
    
    std::string path = std::get<std::string>(pathToken->value);
    path = path.substr(1, path.size() - 2);
    
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();
    fileStream->open(path, std::ifstream::in);

    if(!fileStream)
        return new Token(INCORRECT);
    
    inStreamStack.push(std::move(fileStream));

    delete pathToken;
    return new Token(LEXER_COMMAND);
}



////////////////////////////////////////////////////////////////////////////////
//                            PUBLIC METHODS                                  //
////////////////////////////////////////////////////////////////////////////////



bool Lexer::getIsProcessed() {
    return isProcessed;
}



Token* Lexer::getToken() {
    Token* token;

    skipWhites();

    int tokenLineNumber = lineNumber;
    int tokenColumnNumber = columnNumber;

    token = buildEOT();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    token = buildLexerCommand();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    token = buildComment();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    token = buildNumber();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    token = buildStringConstant();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    token = buildIdentifierOrKeyword();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    token = buildOperator();
    if(token) return token->setPosition(tokenLineNumber, tokenColumnNumber);

    getNextChar();
    return new Token(UNKNOWN);
}
