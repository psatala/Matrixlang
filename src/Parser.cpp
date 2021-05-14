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


std::unique_ptr<PrimaryExpression> Parser::parsePrimaryExpression() {
    if( INT         != currentToken.type    && 
        FLOAT       != currentToken.type    &&
        IDENTIFIER  != currentToken.type     )
        return std::unique_ptr<PrimaryExpression>(nullptr);

    PrimaryExpression primaryExpression = PrimaryExpression(currentToken);
    getNextToken();
    return std::make_unique<PrimaryExpression>(primaryExpression);
}

std::unique_ptr<Operator> Parser::parseAdditionOperator() {
    if( PLUS    != currentToken.type    &&
        MINUS   != currentToken.type    )
        return std::unique_ptr<Operator>(nullptr);
    
    Operator additionOperator = Operator(currentToken.type);
    getNextToken();
    return std::make_unique<Operator>(additionOperator);
}

std::unique_ptr<Operator> Parser::parseAssignmentOperator() {
    if( ASSIGN          != currentToken.type    &&
        PLUS_ASSIGN     != currentToken.type    &&
        MINUS_ASSIGN    != currentToken.type    &&
        MULTIPLY_ASSIGN != currentToken.type    &&
        DIVIDE_ASSIGN   != currentToken.type    &&
        MODULO_ASSIGN   != currentToken.type    )
        return std::unique_ptr<Operator>(nullptr);
    
    Operator assignmentOperator = Operator(currentToken.type);
    getNextToken();
    return std::make_unique<Operator>(assignmentOperator);
}


std::unique_ptr<Expression> Parser::parseAdditionExpression() {
    std::unique_ptr<Expression> leftExpression = parsePrimaryExpression();
    if(!leftExpression)
        return std::unique_ptr<Expression>(nullptr);


    std::unique_ptr<Operator> additionOperator = parseAdditionOperator();
    if(!additionOperator)
        return leftExpression;


    std::unique_ptr<Expression> rightExpression = parsePrimaryExpression();
    if(!rightExpression)
        generateError("Parsing addition expression: expected another "
            "operand");
    std::unique_ptr<BinaryExpression> resultExpression = 
        std::make_unique<BinaryExpression>(BinaryExpression
        (std::move(leftExpression), std::move(rightExpression), 
        std::move(additionOperator)));


    while(true) {
        std::unique_ptr<Operator> additionOperator = parseAdditionOperator();
        if(!additionOperator)
            break;
        std::unique_ptr<Expression> rightExpression = parsePrimaryExpression();
        if(!rightExpression)
            generateError("Parsing addition expression: expected another "
                "operand");
        resultExpression = std::make_unique<BinaryExpression>(BinaryExpression
            (std::move(resultExpression), std::move(rightExpression), 
            std::move(additionOperator)));
    }
    return resultExpression;
}


std::unique_ptr<Expression> Parser::parseAssignmentExpression() {
    std::unique_ptr<Expression> leftExpression = parseAdditionExpression();
    if(!leftExpression)
        return std::unique_ptr<Expression>(nullptr);

    std::vector<std::unique_ptr<Expression>> expressionVector;
    expressionVector.push_back(std::move(leftExpression));

    std::vector<std::unique_ptr<Operator>> operatorVector;
    
    while(true) {
        std::unique_ptr<Operator> assignmentOperator = 
            parseAssignmentOperator();
        if(!assignmentOperator)
            break;
        std::unique_ptr<Expression> rightExpression = parseAdditionExpression();
        if(!rightExpression)
            generateError("Parsing assignment expression: expected another "
                "operand");
        operatorVector.push_back(std::move(assignmentOperator));
        expressionVector.push_back(std::move(rightExpression));
    }

    std::unique_ptr<BinaryExpression> resultExpression;
    for(int i = expressionVector.size() - 2; i >= 0; --i) {
        resultExpression = std::make_unique<BinaryExpression>(BinaryExpression(
            std::move(expressionVector[i]), std::move(expressionVector[i + 1]),
            std::move(operatorVector[i])));
        expressionVector[i] = std::move(resultExpression);
    }

    return std::move(expressionVector[0]);

        
    


    // std::unique_ptr<Operator> assignmentOperator = parseAssignmentOperator();
    // if(!assignmentOperator)
    //     return leftExpression;


    // std::unique_ptr<Expression> rightExpression = parseAdditionExpression();
    // if(!rightExpression)
    //     generateError("Parsing addition expression: expected another "
    //         "operand");
    // std::unique_ptr<BinaryExpression> resultExpression = 
    //     std::make_unique<BinaryExpression>(BinaryExpression
    //     (std::move(leftExpression), std::move(rightExpression), 
    //     std::move(assignmentOperator)));


    // while(true) {
    //     std::unique_ptr<Operator> assignmentOperator = 
    //         parseAssignmentOperator();
    //     if(!assignmentOperator)
    //         break;
    //     std::unique_ptr<Expression> rightExpression = parseAdditionExpression();
    //     if(!rightExpression)
    //         generateError("Parsing assignment expression: expected another "
    //             "operand");
    //     resultExpression = std::make_unique<BinaryExpression>(BinaryExpression
    //         (std::move(resultExpression), std::move(rightExpression), 
    //         std::move(assignmentOperator)));
    // }
    // return resultExpression;
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