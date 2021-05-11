#include "../headers/Parser.h"

void Parser::getNextToken() {
    static bool isEOTProcessed = false;
    if(isEOTProcessed)
        generateError("EOT already processed");

    do {
        currentToken = lexer.getToken();
    } while(COMMENT == currentToken.type);
    if(EOT == currentToken.type)
        isEOTProcessed = true;
}

void Parser::generateError(std::string message) {
    std::string completeMessage = "Line: "
        + std::to_string(currentToken.lineNumber)
        + " Column: " + std::to_string(currentToken.columnNumber) + " -> " 
        + message + "\n";
    errStream << completeMessage;
    throw static_cast<std::string>("Parsing stopped, error: " 
        + completeMessage);

}

std::optional<Expression> Parser::parseExpression() {
    return Expression();
}

std::optional<StringExpression> Parser::parseStringExpression() {
    if(STRING_CONSTANT != currentToken.type)
        return std::nullopt;
    std::vector<std::variant<std::string, Expression>>
        stringLiteralsAndExpressions;
    stringLiteralsAndExpressions.push_back(
        std::get<std::string>(currentToken.value));
    getNextToken();
    while(true) {
        bool isExpressionParsed = false;
        if(std::optional<Expression> expression = parseExpression()) {
            stringLiteralsAndExpressions.push_back(expression.value());
            isExpressionParsed = true;
        }
        if(STRING_CONSTANT != currentToken.type) {
            if(isExpressionParsed)
                generateError("String expression should end with string "
                    "literal, not expression");
            break;
        }
        stringLiteralsAndExpressions.push_back(
            std::get<std::string>(currentToken.value));
        getNextToken();
    }
    return StringExpression(stringLiteralsAndExpressions);
}

std::optional<SimpleType> Parser::parseSimpleType() {
    if( INT     != currentToken.type    &&
        FLOAT   != currentToken.type    &&
        STRING  != currentToken.type    )
        return std::nullopt;

    TokenType type = currentToken.type;
    getNextToken();
    return SimpleType(type);
}

std::optional<VectorType> Parser::parseVectorType() {
    if(VECTOR != currentToken.type)
        return std::nullopt;
    getNextToken();

    if(LESS_THAN != currentToken.type)
        generateError("Parsing Vector, expected \"<\"");
    getNextToken();

    std::optional<Type> type = parseType();
    if(!type)
        generateError("Parsing Vector, expected Type");
    
    if(MORE_THAN != currentToken.type)
        generateError("Parsing Vector, expected \">\"");
    getNextToken();

    if(L_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Vector, expected \"[\"");
    getNextToken();

    std::optional<Expression> expression = parseExpression();
    if(!expression)
        generateError("Parsing Vector, expected Expression");
    
    if(R_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Vector, expected \"]\"");
    getNextToken();

    Type typeEnd = type.value();
    std::optional<VectorType> vectorType = VectorType(type.value(), expression.value());

    return VectorType(type.value(), expression.value());
}

std::optional<MatrixType> Parser::parseMatrixType() {
    if(MATRIX != currentToken.type)
        return std::nullopt;    
    getNextToken();

    if(LESS_THAN != currentToken.type)
        generateError("Parsing Vector, expected \"<\"");
    getNextToken();

    std::optional<Type> type = parseType();
    if(!type)
        generateError("Parsing Vector, expected Type");
    
    if(MORE_THAN != currentToken.type)
        generateError("Parsing Vector, expected \">\"");
    getNextToken();
    
    if(L_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Vector, expected \"[\"");
    getNextToken();
    
    std::optional<Expression> firstExpression = parseExpression();
    if(!firstExpression)
        generateError("Parsing Vector, expected Expression");
    
    if(COMMA != currentToken.type)
        generateError("Parsing Vector, expected \",\"");
    getNextToken();

    std::optional<Expression> secondExpression = parseExpression();
    if(!secondExpression)
        generateError("Parsing Vector, expected Expression");
    
    if(R_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Vector, expected \"]\"");
    getNextToken();

    return MatrixType(type.value(), firstExpression.value(), 
        secondExpression.value());
}

std::optional<Type> Parser::parseType() {
    std::optional<VectorType> vectorTypeOptional = parseVectorType();
    if(vectorTypeOptional) {
        VectorType vectorType = vectorTypeOptional.value();
        Type type = Type(vectorType);
        return type;
    }
    
    std::optional<SimpleType> simpleType = parseSimpleType();
    if(simpleType) return Type(simpleType.value());
    
    std::optional<MatrixType> matrixType = parseMatrixType();
    if(matrixType) return Type(matrixType.value());
    
    return std::nullopt;
}