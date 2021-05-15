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


std::unique_ptr<Expression> Parser::constructLeftTreeFromExpressionVector(
    std::vector<std::unique_ptr<Expression>> expressionVector,
    std::vector<std::unique_ptr<Operator>> operatorVector) {
    
    std::unique_ptr<BinaryExpression> resultExpression;
    for(int i = 0; i < expressionVector.size() - 1; ++i) {
        resultExpression = std::make_unique<BinaryExpression>(BinaryExpression(
            std::move(expressionVector[i]), std::move(expressionVector[i + 1]),
            std::move(operatorVector[i])));
        expressionVector[i + 1] = std::move(resultExpression);
    }

    return std::move(expressionVector[expressionVector.size() - 1]);
}


std::unique_ptr<Expression> Parser::constructRightTreeFromExpressionVector(
    std::vector<std::unique_ptr<Expression>> expressionVector,
    std::vector<std::unique_ptr<Operator>> operatorVector) {

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




////////////////////////////////////////////////////////////////////////////////
//                                   types                                    //
////////////////////////////////////////////////////////////////////////////////



std::unique_ptr<SimpleType> Parser::parseSimpleType() {
    if( INT     != currentToken.type    &&
        FLOAT   != currentToken.type    &&
        STRING  != currentToken.type    )
        return std::unique_ptr<SimpleType>(nullptr);

    TokenType type = currentToken.type;
    getNextToken();
    return std::make_unique<SimpleType>(SimpleType(type));
}


std::unique_ptr<VectorType> Parser::parseVectorType() {
    if(VECTOR != currentToken.type)
        return std::unique_ptr<VectorType>(nullptr);
    getNextToken();

    if(LESS_THAN != currentToken.type)
        generateError("Parsing Vector, expected \"<\"");
    getNextToken();

    std::unique_ptr<Type> type = parseType();
    if(!type)
        generateError("Parsing Vector, expected Type");
    
    if(MORE_THAN != currentToken.type)
        generateError("Parsing Vector, expected \">\"");
    getNextToken();

    if(L_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Vector, expected \"[\"");
    getNextToken();

    std::unique_ptr<Expression> expression = parseExpression();
    if(!expression)
        generateError("Parsing Vector, expected Expression");
    
    if(R_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Vector, expected \"]\"");
    getNextToken();

    return std::make_unique<VectorType>(VectorType(std::move(type), 
        std::move(expression)));
}



std::unique_ptr<MatrixType> Parser::parseMatrixType() {
    if(MATRIX != currentToken.type)
        return std::unique_ptr<MatrixType>(nullptr);    
    getNextToken();

    if(LESS_THAN != currentToken.type)
        generateError("Parsing Matrix, expected \"<\"");
    getNextToken();

    std::unique_ptr<Type> type = parseType();
    if(!type)
        generateError("Parsing Matrix, expected Type");
    
    if(MORE_THAN != currentToken.type)
        generateError("Parsing Matrix, expected \">\"");
    getNextToken();
    
    if(L_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Matrix, expected \"[\"");
    getNextToken();
    
    std::unique_ptr<Expression> firstExpression = parseExpression();
    if(!firstExpression)
        generateError("Parsing Matrix, expected Expression");
    
    if(COMMA != currentToken.type)
        generateError("Parsing Matrix, expected \",\"");
    getNextToken();

    std::unique_ptr<Expression> secondExpression = parseExpression();
    if(!secondExpression)
        generateError("Parsing Matrix, expected Expression");
    
    if(R_SQUARE_BRACKET != currentToken.type)
        generateError("Parsing Matrix, expected \"]\"");
    getNextToken();

    return std::make_unique<MatrixType>(MatrixType(std::move(type), 
        std::move(firstExpression), std::move(secondExpression)));
}




std::unique_ptr<Type> Parser::parseType() {

    std::unique_ptr<SimpleType> simpleType = parseSimpleType();
    if(simpleType) return std::move(simpleType);

    std::unique_ptr<VectorType> vectorType = parseVectorType();
    if(vectorType) return std::move(vectorType);

    std::unique_ptr<MatrixType> matrixType = parseMatrixType();
    if(matrixType) return std::move(matrixType);
    
    return std::unique_ptr<Type>(nullptr);
}




////////////////////////////////////////////////////////////////////////////////
//                               operators                                    //
////////////////////////////////////////////////////////////////////////////////



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



std::unique_ptr<Operator> Parser::parsePostOperator() {
    return parseOperator(std::vector<TokenType> {INCREMENT, DECREMENT});
}


std::unique_ptr<Operator> Parser::parseUnaryRValueOperator() {
    return parseOperator(std::vector<TokenType> {PLUS, MINUS, NOT});
}


std::unique_ptr<Operator> Parser::parseUnaryLValueOperator() {
    return parseOperator(std::vector<TokenType> {INCREMENT, DECREMENT, PLUS, 
        MINUS, NOT});
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





////////////////////////////////////////////////////////////////////////////////
//                               expressions                                  //
////////////////////////////////////////////////////////////////////////////////



std::unique_ptr<Expression> Parser::parseStringExpression() {
    //parsing first string
    if(STRING_CONSTANT != currentToken.type)
        return std::unique_ptr<Expression>(nullptr);

    StringExpression stringExpression;
    stringExpression.stringLiteralsAndExpressions.push_back(
        std::get<std::string>(currentToken.value));
    getNextToken();
    
    while(true) {
        //parsing expression
        bool isExpressionParsed = false;
        if(std::unique_ptr<Expression> expression = parseExpression()) {
            stringExpression.stringLiteralsAndExpressions.push_back
                (std::move(expression));
            isExpressionParsed = true;
        }
    
        //parsing string
        if(STRING_CONSTANT != currentToken.type) {
            if(isExpressionParsed)
                generateError("String expression should end with string "
                    "literal, not expression");
            break;
        }
        stringExpression.stringLiteralsAndExpressions.push_back(
            std::get<std::string>(currentToken.value));
        getNextToken();
    }
    
    return std::make_unique<StringExpression>(std::move(stringExpression));
}



std::unique_ptr<Expression> Parser::parseLiteralExpression() {
    if( INT_NUMBER      == currentToken.type    ||
        FLOAT_NUMBER    == currentToken.type    ) {
            
        LiteralExpression literalExpression = LiteralExpression(currentToken);
        getNextToken();
        return std::make_unique<LiteralExpression>
            (std::move(literalExpression));
    }
    
    if(std::unique_ptr<Expression> stringExpression = parseStringExpression())
        return std::move(stringExpression);

    return std::unique_ptr<Expression>(nullptr);
}


std::unique_ptr<Expression> Parser::parsePrimaryExpression() {
    std::unique_ptr<Expression> expression = parseLiteralExpression();
    if(expression)
        return expression;

    if(L_PARENT != currentToken.type)
        return std::unique_ptr<Expression>(nullptr);

    //parsing expression in parenthesis
    getNextToken();
    expression = parseExpression();
    if(!expression)
        generateError("Parsing expression in parenthesis: expected an "
            "expression");
    if(R_PARENT != currentToken.type)
        generateError("Parsing expression in parenthesis: missing closing "
            "parenthesis");
    getNextToken();

    return expression;

}


std::unique_ptr<Expression> Parser::parseFuncallExpression() {
    if(IDENTIFIER != currentToken.type)
        return std::unique_ptr<Expression>(nullptr);

    std::string identifier = std::get<std::string>(currentToken.value);
    getNextToken();
    
    if(L_PARENT != currentToken.type)
        return std::make_unique<FuncallExpression>(identifier);
    getNextToken();

    std::unique_ptr<ExpressionList> expressionList = parseExpressionList();

    if(R_PARENT != currentToken.type)
        generateError("End of function call: expected \")\"");
    getNextToken();

    return std::make_unique<FuncallExpression>(identifier, 
        std::move(expressionList));
}


std::unique_ptr<Expression> Parser::parseLValueExpression() {
    std::unique_ptr<Expression> expression = parseFuncallExpression();
    if(!expression)
        return std::unique_ptr<Expression>(nullptr);
    
    while(true) {
        if(L_SQUARE_BRACKET != currentToken.type)
            break;
        getNextToken();

        std::unique_ptr<Expression> firstIndexExpression = parseExpression();
        if(!firstIndexExpression)
            generateError("Parsing Vector/Matrix index access: no expression "
            "after \"[\"");
        
        if(COMMA != currentToken.type) {
            
            if(R_SQUARE_BRACKET != currentToken.type)
                generateError("Parsing Vector index access: expected \"]\"");
            getNextToken();

            expression = std::make_unique<VectorIndexExpression>
                (VectorIndexExpression(std::move(expression), 
                std::move(firstIndexExpression)));    
            continue;
        }
        getNextToken();

        std::unique_ptr<Expression> secondIndexExpression = parseExpression();
        if(!secondIndexExpression)
            generateError("Parsing Matrix index access: expected another "
            "expression after \",\"");
        
        if(R_SQUARE_BRACKET != currentToken.type)
            generateError("Parsing Matrix index access: expected \"]\"");
        getNextToken();

        expression = std::make_unique<MatrixIndexExpression>
                (MatrixIndexExpression(std::move(expression), 
                std::move(firstIndexExpression), 
                std::move(secondIndexExpression)));
    }
    return std::move(expression);
}


std::unique_ptr<Expression> Parser::parsePostExpression() {
    std::unique_ptr<Expression> expression = parseLValueExpression();
    if(!expression)
        return std::unique_ptr<Expression>(nullptr);

    while(std::unique_ptr<Operator> postOperator = parsePostOperator()) {
        expression = std::make_unique<PostExpression>(std::move(expression), 
            std::move(postOperator));
    }
    return std::move(expression);
}



std::unique_ptr<Expression> Parser::parseUnaryExpression(
    std::function<std::unique_ptr<Expression>()> parseLowerExpression,
    std::function<std::unique_ptr<Operator>()> parseThisOperator) {

    std::vector<std::unique_ptr<Operator>> operatorVector;
    while(std::unique_ptr<Operator> unaryOperator = parseThisOperator())
        operatorVector.push_back(std::move(unaryOperator));
    
    std::unique_ptr<Expression> expression = parseLowerExpression();
    if(!expression) {
        if(operatorVector.empty())
            return std::unique_ptr<Expression>(nullptr);
        
        generateError("Parsing unary expression: got unary operators, but an "
        "expression did not follow");
    }

    for(int i = operatorVector.size() - 1; i >= 0; --i) {
        expression = std::make_unique<UnaryExpression>
        (UnaryExpression(std::move(operatorVector[i]), 
            std::move(expression)));
    }

    return expression;

}


std::unique_ptr<Expression> Parser::parseAllUnaryExpressions() {
    if(std::unique_ptr<Expression> expression = parseUnaryExpression(
        std::bind(&Parser::parsePrimaryExpression, this),
        std::bind(&Parser::parseUnaryRValueOperator, this)))
        return std::move(expression);

    return std::move(parseUnaryExpression(
        std::bind(&Parser::parsePostExpression, this),
        std::bind(&Parser::parseUnaryLValueOperator, this)));
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

    if(isRightAssociative) { // only assignment expression
        
        //for every but last expression
        for(int i = 0; i < expressionVector.size() - 1; ++i) {
            if(!expressionVector[i]->isLValue()) {
                generateError("Parsing assignment expression: expected lvalue "
                "expression, but got rvalue expression");
            }
        }

        return constructRightTreeFromExpressionVector(
            std::move(expressionVector), std::move(operatorVector));
    }

    return constructLeftTreeFromExpressionVector(
            std::move(expressionVector), std::move(operatorVector));
}




std::unique_ptr<Expression> Parser::parseMultiplicationExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseAllUnaryExpressions, this),
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


std::unique_ptr<Expression> Parser::parseRValueExpression() {
    return std::move(parseOrExpression());
}


std::unique_ptr<Expression> Parser::parseAssignmentExpression() {
    return parseBinaryExpression(
        std::bind(&Parser::parseRValueExpression, this),
        std::bind(&Parser::parseAssignmentOperator, this),
        "Parsing assignment expression: expected another operand",
        true);
}


std::unique_ptr<Expression> Parser::parseExpression() {
    return std::move(parseAssignmentExpression());
}


std::unique_ptr<ExpressionList> Parser::parseExpressionList() {
    ExpressionList expressionList;
    std::unique_ptr<Expression> expression = parseExpression();
    if(!expression)
        return std::make_unique<ExpressionList>(std::move(expressionList));
    
    expressionList.push_back(std::move(expression));

    while(true) {
        if(COMMA != currentToken.type)
            break;
        getNextToken();
        expression = parseExpression();
        if(!expression)
            generateError("Another expression after \",\" should follow");
        expressionList.push_back(std::move(expression));
    }
    return std::make_unique<ExpressionList>(std::move(expressionList));
}


std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>> 
    Parser::parseDeclarationOrFunction() {

    std::unique_ptr<Type> type = parseType();
    if(!type)
        return std::unique_ptr<Declaration>(nullptr);

    if(IDENTIFIER != currentToken.type)
        generateError("Expected an identifier");
    std::string identifier = std::get<std::string>(currentToken.value);
    getNextToken();
    
    if(L_PARENT == currentToken.type)
        return parseFunctionEnd(std::move(type), identifier);

    std::unique_ptr<Declaration> declaration = parseDeclarationEnd(
        std::move(type), identifier);
    if(declaration)
        return std::move(declaration);

    generateError("Parsing declaration or function: could not parse neither "
        "declaration nor function");
    return std::unique_ptr<Declaration>(nullptr);
}


std::unique_ptr<Declaration> Parser::parseDeclarationEnd(
    std::unique_ptr<Type> type, std::string identifier) {
    
    std::unique_ptr<Expression> expression = std::unique_ptr<Expression>
        (nullptr);
    if(ASSIGN == currentToken.type) {
        getNextToken();
        expression = parseExpression();
        if(!expression)
            generateError("Parsing declaration: parsed \"=\", but an expression"
            " did not follow");
    }
    if(SEMICOLON != currentToken.type)
        generateError("Parsing declaration: expected \";\" at the end of "
            "declaration");
    getNextToken();
    return std::make_unique<Declaration>(Declaration(std::move(type), 
        identifier, std::move(expression)));
}


std::unique_ptr<Function> Parser::parseFunctionEnd(std::unique_ptr<Type> type, 
    std::string identifier) {
    
    getNextToken();

    //can be null - then the list is empty
    std::unique_ptr<ArgumentList> argumentList = parseArgumentList();

    if(R_PARENT != currentToken.type)
        generateError("Parsing function: expected \")\"");
    getNextToken();
    
    std::unique_ptr<Statement> statement = parseStatement();
    if(!statement)
        generateError("Parsing function: function must have a body");

    return std::make_unique<Function>(Function(std::move(type), identifier, 
        std::move(argumentList), std::move(statement)));
}


std::unique_ptr<ArgumentList> Parser::parseArgumentList() {
    std::unique_ptr<ArgumentList> argumentList = 
        std::make_unique<ArgumentList>();

    std::unique_ptr<Type> type = parseType();
    if(!type)
        return std::unique_ptr<ArgumentList>(nullptr);
    argumentList->typeVector.push_back(std::move(type));

    if(IDENTIFIER != currentToken.type)
        generateError("Parsing argument list: expected an identifier");
    
    argumentList->identifierVector.push_back(std::get<std::string>
        (currentToken.value));
    getNextToken();

    while(COMMA == currentToken.type) {
        getNextToken();

        type = parseType();
        if(!type)
            generateError("Parsing argument list: expected type after \",\"");
        argumentList->typeVector.push_back(std::move(type));

        if(IDENTIFIER != currentToken.type)
            generateError("Parsing argument list: expected an identifier");
        argumentList->identifierVector.push_back(std::get<std::string>
            (currentToken.value));
        getNextToken();
    }

    return std::move(argumentList);
}


std::unique_ptr<Statement> Parser::parseStatement() {
    return std::make_unique<Statement>(Statement());
}


std::unique_ptr<Program> Parser::parseProgram() {
    getNextToken();
    std::unique_ptr<Expression> expression = parseExpression();
    if(!expression)
        return std::unique_ptr<Program>(nullptr);
    return std::make_unique<Program>(Program(std::move(expression)));
}


