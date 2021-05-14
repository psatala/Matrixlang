#include "../headers/Parser.h"

void Parser::getNextToken() {
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


std::unique_ptr<PrimaryExpression> Parser::parsePrimaryExpression() {
    if( INT_NUMBER      != currentToken.type    && 
        FLOAT_NUMBER    != currentToken.type    &&
        IDENTIFIER      != currentToken.type     )
        return std::unique_ptr<PrimaryExpression>(nullptr);

    PrimaryExpression primaryExpression = PrimaryExpression(currentToken);
    getNextToken();
    return std::make_unique<PrimaryExpression>(primaryExpression);
}






std::unique_ptr<Operator> Parser::parseOperator(std::vector<TokenType> 
    acceptedOperators) {

    for(int i = 0; i < acceptedOperators.size(); ++i) {
        if(acceptedOperators[i] == currentToken.type) {
            Operator additionOperator = Operator(currentToken.type);
            getNextToken();
            return std::make_unique<Operator>(additionOperator);            
        }
    }

    return std::unique_ptr<Operator>(nullptr);
}



std::unique_ptr<Operator> Parser::parseMultiplicationOperator() {
    return parseOperator(std::vector<TokenType> {MULTIPLY, DIVIDE, MODULO});
}

std::unique_ptr<Operator> Parser::parseRelationOperator() {
    return parseOperator(std::vector<TokenType> {LESS_THAN, LESS_EQUAL, 
        MORE_THAN, MORE_EQUAL, EQUAL, NOT_EQUAL});
}

std::unique_ptr<Operator> Parser::parseAndOperator() {
    return parseOperator(std::vector<TokenType> {AND});
}

std::unique_ptr<Operator> Parser::parseOrOperator() {
    return parseOperator(std::vector<TokenType> {OR});
}

std::unique_ptr<Operator> Parser::parseAdditionOperator() {
    return parseOperator(std::vector<TokenType> {PLUS, MINUS});
}

std::unique_ptr<Operator> Parser::parseAssignmentOperator() {
    return parseOperator(std::vector<TokenType> {ASSIGN, PLUS_ASSIGN, 
        MINUS_ASSIGN, MULTIPLY_ASSIGN, DIVIDE_ASSIGN, MODULO_ASSIGN});
}




std::unique_ptr<Expression> Parser::parseBinaryExpression(
    std::function<std::unique_ptr<Expression>()> parseLowerExpression,
    std::function<std::unique_ptr<Operator>()> parseThisOperator,
    std::string errorMessage, bool isRightAssociative) {

    std::unique_ptr<Expression> leftExpression = parseLowerExpression();
    if(!leftExpression)
        return std::unique_ptr<Expression>(nullptr);

    std::vector<std::unique_ptr<Expression>> expressionVector;
    expressionVector.push_back(std::move(leftExpression));

    std::vector<std::unique_ptr<Operator>> operatorVector;
    
    while(true) {
        std::unique_ptr<Operator> currentOperator = 
            parseThisOperator();
        if(!currentOperator)
            break;
        std::unique_ptr<Expression> rightExpression = parseLowerExpression();
        if(!rightExpression)
            generateError(errorMessage);
        operatorVector.push_back(std::move(currentOperator));
        expressionVector.push_back(std::move(rightExpression));
    }

    if(isRightAssociative) {
        std::unique_ptr<BinaryExpression> resultExpression;
        for(int i = expressionVector.size() - 2; i >= 0; --i) {
            resultExpression = std::make_unique<BinaryExpression>
                (BinaryExpression(std::move(expressionVector[i]), 
                std::move(expressionVector[i + 1]),
                std::move(operatorVector[i])));
            expressionVector[i] = std::move(resultExpression);
        }

        return std::move(expressionVector[0]);

    }

    std::unique_ptr<BinaryExpression> resultExpression;
    for(int i = 0; i < expressionVector.size() - 1; ++i) {
        resultExpression = std::make_unique<BinaryExpression>(BinaryExpression(
            std::move(expressionVector[i]), std::move(expressionVector[i + 1]),
            std::move(operatorVector[i])));
        expressionVector[i + 1] = std::move(resultExpression);
    }

    return std::move(expressionVector[expressionVector.size() - 1]);

}




std::unique_ptr<Expression> Parser::parseMultiplicationExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parsePrimaryExpression, this),
        std::bind(&Parser::parseMultiplicationOperator, this),
        "Parsing multiplication expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseAdditionExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseMultiplicationExpression, this),
        std::bind(&Parser::parseAdditionOperator, this),
        "Parsing addition expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseRelationExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseAdditionExpression, this),
        std::bind(&Parser::parseRelationOperator, this),
        "Parsing relation expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseAndExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseRelationExpression, this),
        std::bind(&Parser::parseAndOperator, this),
        "Parsing and expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseOrExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseAndExpression, this),
        std::bind(&Parser::parseOrOperator, this),
        "Parsing or expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseAssignmentExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseOrExpression, this),
        std::bind(&Parser::parseAssignmentOperator, this),
        "Parsing assignment expression: expected another operand",
        true);
}




std::unique_ptr<Program> Parser::parseProgram() {
    getNextToken();
    std::unique_ptr<Expression> expression = parseAssignmentExpression();
    if(!expression)
        return std::unique_ptr<Program>(nullptr);
    return std::make_unique<Program>(Program(std::move(expression)));
}

























// std::optional<Expression> Parser::parseExpression() {
//     return Expression();
// }

// std::optional<StringExpression> Parser::parseStringExpression() {
//     if(STRING_CONSTANT != currentToken.type)
//         return std::nullopt;
//     std::vector<std::variant<std::string, Expression>>
//         stringLiteralsAndExpressions;
//     stringLiteralsAndExpressions.push_back(
//         std::get<std::string>(currentToken.value));
//     getNextToken();
//     while(true) {
//         bool isExpressionParsed = false;
//         if(std::optional<Expression> expression = parseExpression()) {
//             stringLiteralsAndExpressions.push_back(expression.value());
//             isExpressionParsed = true;
//         }
//         if(STRING_CONSTANT != currentToken.type) {
//             if(isExpressionParsed)
//                 generateError("String expression should end with string "
//                     "literal, not expression");
//             break;
//         }
//         stringLiteralsAndExpressions.push_back(
//             std::get<std::string>(currentToken.value));
//         getNextToken();
//     }
//     return StringExpression(stringLiteralsAndExpressions);
// }

// std::optional<SimpleType> Parser::parseSimpleType() {
//     if( INT     != currentToken.type    &&
//         FLOAT   != currentToken.type    &&
//         STRING  != currentToken.type    )
//         return std::nullopt;

//     TokenType type = currentToken.type;
//     getNextToken();
//     return SimpleType(type);
// }

// std::optional<VectorType> Parser::parseVectorType() {
//     if(VECTOR != currentToken.type)
//         return std::nullopt;
//     getNextToken();

//     if(LESS_THAN != currentToken.type)
//         generateError("Parsing Vector, expected \"<\"");
//     getNextToken();

//     std::optional<Type> type = parseType();
//     if(!type)
//         generateError("Parsing Vector, expected Type");
    
//     if(MORE_THAN != currentToken.type)
//         generateError("Parsing Vector, expected \">\"");
//     getNextToken();

//     if(L_SQUARE_BRACKET != currentToken.type)
//         generateError("Parsing Vector, expected \"[\"");
//     getNextToken();

//     std::optional<Expression> expression = parseExpression();
//     if(!expression)
//         generateError("Parsing Vector, expected Expression");
    
//     if(R_SQUARE_BRACKET != currentToken.type)
//         generateError("Parsing Vector, expected \"]\"");
//     getNextToken();

//     Type typeEnd = type.value();
//     std::optional<VectorType> vectorType = VectorType(type.value(), expression.value());

//     return VectorType(type.value(), expression.value());
// }

// std::optional<MatrixType> Parser::parseMatrixType() {
//     if(MATRIX != currentToken.type)
//         return std::nullopt;    
//     getNextToken();

//     if(LESS_THAN != currentToken.type)
//         generateError("Parsing Vector, expected \"<\"");
//     getNextToken();

//     std::optional<Type> type = parseType();
//     if(!type)
//         generateError("Parsing Vector, expected Type");
    
//     if(MORE_THAN != currentToken.type)
//         generateError("Parsing Vector, expected \">\"");
//     getNextToken();
    
//     if(L_SQUARE_BRACKET != currentToken.type)
//         generateError("Parsing Vector, expected \"[\"");
//     getNextToken();
    
//     std::optional<Expression> firstExpression = parseExpression();
//     if(!firstExpression)
//         generateError("Parsing Vector, expected Expression");
    
//     if(COMMA != currentToken.type)
//         generateError("Parsing Vector, expected \",\"");
//     getNextToken();

//     std::optional<Expression> secondExpression = parseExpression();
//     if(!secondExpression)
//         generateError("Parsing Vector, expected Expression");
    
//     if(R_SQUARE_BRACKET != currentToken.type)
//         generateError("Parsing Vector, expected \"]\"");
//     getNextToken();

//     return MatrixType(type.value(), firstExpression.value(), 
//         secondExpression.value());
// }

// std::optional<Type> Parser::parseType() {
//     std::optional<VectorType> vectorTypeOptional = parseVectorType();
//     if(vectorTypeOptional) {
//         VectorType vectorType = vectorTypeOptional.value();
//         // std::size_t variantIndex = vectorType.type.containedType.index();
//         std::get<SimpleType>(vectorType.type.containedType);
//         // VectorType vt = vectorType;
//         Type type = Type(vectorType);
//         // std::size_t variantIndex2 = vectorType.type.containedType.index();
//         std::get<SimpleType>(vectorType.type.containedType);
//         return type;
//     }
    
//     std::optional<SimpleType> simpleType = parseSimpleType();
//     if(simpleType) return Type(simpleType.value());
    
//     std::optional<MatrixType> matrixType = parseMatrixType();
//     if(matrixType) return Type(matrixType.value());
    
//     return std::nullopt;
// }