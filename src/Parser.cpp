#include "../headers/Parser.h"

void Parser::getNextToken() {
    // special case
    if(EOT == peekedToken.type && EOT != currentToken.type) {
        currentToken = peekedToken;
        return;
    }

    currentToken = peekedToken;

    if(isEOTProcessed)
        generateError("EOT already processed");

    do {
        peekedToken = lexer.getToken();
    } while(COMMENT == peekedToken.type || LEXER_COMMAND == peekedToken.type);
    if(EOT == peekedToken.type)
        isEOTProcessed = true;
}


void Parser::setUpPeekedToken() {
    getNextToken();
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


void Parser::expectToken(TokenType type, std::string errorMessage) {
    if(type != currentToken.type)
        generateError(errorMessage);
    getNextToken();
}



////////////////////////////////////////////////////////////////////////////////
//                                   types                                    //
////////////////////////////////////////////////////////////////////////////////



std::unique_ptr<SimpleType> Parser::parseSimpleType() {
    if( INT     != currentToken.type    &&
        FLOAT   != currentToken.type    &&
        STRING  != currentToken.type    &&
        VOID    != currentToken.type    )
        return std::unique_ptr<SimpleType>(nullptr);

    TokenType type = currentToken.type;
    getNextToken();
    return std::make_unique<SimpleType>(SimpleType(type));
}


std::unique_ptr<VectorType> Parser::parseVectorType() {
    if(VECTOR != currentToken.type)
        return std::unique_ptr<VectorType>(nullptr);
    getNextToken();

    expectToken(LESS_THAN, "Parsing Vector, expected \"<\"");

    std::unique_ptr<Type> type = parseType();
    if(!type)
        generateError("Parsing Vector, expected Type");
    
    expectToken(MORE_THAN, "Parsing Vector, expected \">\"");
    expectToken(L_SQUARE_BRACKET, "Parsing Vector, expected \"[\"");
    
    std::unique_ptr<Expression> expression = parseExpression();
    if(!expression)
        generateError("Parsing Vector, expected Expression");
    
    expectToken(R_SQUARE_BRACKET, "Parsing Vector, expected \"]\"");

    return std::make_unique<VectorType>(VectorType(std::move(type), 
        std::move(expression)));
}



std::unique_ptr<MatrixType> Parser::parseMatrixType() {
    if(MATRIX != currentToken.type)
        return std::unique_ptr<MatrixType>(nullptr);    
    getNextToken();

    expectToken(LESS_THAN, "Parsing Matrix, expected \"<\"");
    
    std::unique_ptr<Type> type = parseType();
    if(!type)
        generateError("Parsing Matrix, expected Type");
    
    expectToken(MORE_THAN, "Parsing Matrix, expected \">\"");
    expectToken(L_SQUARE_BRACKET, "Parsing Matrix, expected \"[\"");
    
    std::unique_ptr<Expression> firstExpression = parseExpression();
    if(!firstExpression)
        generateError("Parsing Matrix, expected Expression");
    
    expectToken(COMMA, "Parsing Matrix, expected \",\"");
    
    std::unique_ptr<Expression> secondExpression = parseExpression();
    if(!secondExpression)
        generateError("Parsing Matrix, expected Expression");
    
    expectToken(R_SQUARE_BRACKET, "Parsing Matrix, expected \"]\"");
    
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

    expression = parseFuncallExpression();
    if(expression)
        return std::move(expression);

    if(L_PARENT != currentToken.type)
        return std::unique_ptr<Expression>(nullptr);
    getNextToken();

    //parsing expression in parenthesis
    expression = parseExpression();
    if(!expression)
        generateError("Parsing expression in parenthesis: expected an "
            "expression");
    
    expectToken(R_PARENT, "Parsing expression in parenthesis: missing closing "
            "parenthesis");
    
    return expression;

}


std::variant<std::unique_ptr<VariableExpression>, 
    std::unique_ptr<FuncallExpression>, std::monostate> 
    Parser::parseVariableOrFuncallExpression(){
    
    if(IDENTIFIER != currentToken.type)
        return std::monostate();

    std::string identifier = std::get<std::string>(currentToken.value);
    getNextToken();
    
    if(L_PARENT != currentToken.type)
        return std::make_unique<VariableExpression>(identifier);
    getNextToken();

    std::unique_ptr<ExpressionList> expressionList = parseExpressionList();

    expectToken(R_PARENT, "End of function call: expected \")\"");
    
    return std::make_unique<FuncallExpression>(identifier, 
        std::move(expressionList));
}


std::unique_ptr<Expression> Parser::parseVariableExpression() {
    if(IDENTIFIER != currentToken.type || L_PARENT == peekedToken.type)
        return std::unique_ptr<Expression>(nullptr);

    std::variant<std::unique_ptr<VariableExpression>, 
        std::unique_ptr<FuncallExpression>, std::monostate> variant = 
        parseVariableOrFuncallExpression();
    
    std::unique_ptr<VariableExpression> expression = 
        std::move(std::get<std::unique_ptr<VariableExpression>>(variant));
    return std::move(expression);
}


std::unique_ptr<Expression> Parser::parseFuncallExpression() {
    if(IDENTIFIER != currentToken.type || L_PARENT != peekedToken.type)
        return std::unique_ptr<Expression>(nullptr);

    std::variant<std::unique_ptr<VariableExpression>, 
        std::unique_ptr<FuncallExpression>, std::monostate> variant = 
        parseVariableOrFuncallExpression();
    
    std::unique_ptr<FuncallExpression> expression = 
        std::move(std::get<std::unique_ptr<FuncallExpression>>(variant));
    return std::move(expression);
}


std::unique_ptr<Expression> Parser::parseLValueExpression() {
    std::unique_ptr<Expression> expression = parseVariableExpression();
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
            
            expectToken(R_SQUARE_BRACKET, 
                "Parsing Vector index access: expected \"]\"");
            
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
        
        expectToken(R_SQUARE_BRACKET, 
            "Parsing Matrix index access: expected \"]\"");
        
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

    std::unique_ptr<Operator> unaryOperator = parseThisOperator();
    if(!unaryOperator)
        return parseLowerExpression();

    std::unique_ptr<Expression> expression = 
        parseUnaryExpression(parseLowerExpression, parseThisOperator);
        
    if(!expression)
        generateError("Parsing unary expression: got unary operators, "
            "but an expression did not follow");
    
    return std::make_unique<UnaryExpression>(UnaryExpression(
        std::move(unaryOperator), std::move(expression)));        
}


std::unique_ptr<Expression> Parser::parseAllUnaryExpressions() {
    if(std::unique_ptr<Expression> expression = parseUnaryExpression(
        std::bind_front(&Parser::parsePrimaryExpression, this),
        std::bind_front(&Parser::parseUnaryRValueOperator, this)))
        return std::move(expression);

    return std::move(parseUnaryExpression(
        std::bind_front(&Parser::parsePostExpression, this),
        std::bind_front(&Parser::parseUnaryLValueOperator, this)));
}


std::unique_ptr<Expression> Parser::parseBinaryExpression(
    std::function<std::unique_ptr<Expression>()> parseLowerExpression,
    std::function<std::unique_ptr<Operator>()> parseThisOperator,
    std::string errorMessage) {

    std::unique_ptr<Expression> leftExpression = parseLowerExpression();
    if(!leftExpression)
        return std::unique_ptr<Expression>(nullptr);

    while(true) {
        std::unique_ptr<Operator> currentOperator = parseThisOperator();
        if(!currentOperator)
            break;
        std::unique_ptr<Expression> rightExpression = parseLowerExpression();
        if(!rightExpression)
            generateError(errorMessage);

        leftExpression = std::make_unique<BinaryExpression>(BinaryExpression(
            std::move(leftExpression), std::move(rightExpression), 
            std::move(currentOperator)));
    }

    return std::move(leftExpression);
}




std::unique_ptr<Expression> Parser::parseMultiplicationExpression() {
    return parseBinaryExpression(
        std::bind_front(&Parser::parseAllUnaryExpressions, this),
        std::bind_front(&Parser::parseMultiplicationOperator, this),
        "Parsing multiplication expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseAdditionExpression() {
    return parseBinaryExpression(
        std::bind_front(&Parser::parseMultiplicationExpression, this),
        std::bind_front(&Parser::parseAdditionOperator, this),
        "Parsing addition expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseRelationExpression() {
    return parseBinaryExpression(
        std::bind_front(&Parser::parseAdditionExpression, this),
        std::bind_front(&Parser::parseRelationOperator, this),
        "Parsing relation expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseAndExpression() {
    return parseBinaryExpression(
        std::bind_front(&Parser::parseRelationExpression, this),
        std::bind_front(&Parser::parseAndOperator, this),
        "Parsing and expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseOrExpression() {
    return parseBinaryExpression(
        std::bind_front(&Parser::parseAndExpression, this),
        std::bind_front(&Parser::parseOrOperator, this),
        "Parsing or expression: expected another operand");
}


std::unique_ptr<Expression> Parser::parseRValueExpression() {
    return parseOrExpression();
}


std::unique_ptr<Expression> Parser::parseAssignmentExpression() {
    
    std::unique_ptr<Expression> leftExpression = parseRValueExpression();
    if(!leftExpression)
        return std::unique_ptr<Expression>(nullptr);

    std::unique_ptr<Operator> assignmentOperator = parseAssignmentOperator();
    if(!assignmentOperator)
        return leftExpression;

    if(!leftExpression->isLValue())
        generateError("Parsing assignment expression: expected lvalue operand "
            "before assignment operator");

    std::unique_ptr<Expression> rightExpression = parseAssignmentExpression();

    if(!rightExpression)
        generateError("Parsing assignment expression: expected another "
            "operand");
        
    return std::make_unique<BinaryExpression>(BinaryExpression(
        std::move(leftExpression), std::move(rightExpression), 
        std::move(assignmentOperator)));
}


std::unique_ptr<Expression> Parser::parseExpression() {
    return parseAssignmentExpression();
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


std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>, 
    std::monostate> Parser::parseDeclarationOrFunction() {

    std::unique_ptr<Type> type = parseType();
    if(!type)
        return std::monostate();

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

    return std::monostate();
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
    return std::make_unique<Declaration>(Declaration(std::move(type), 
        identifier, std::move(expression)));
}


std::unique_ptr<Function> Parser::parseFunctionEnd(std::unique_ptr<Type> type, 
    std::string identifier) {
    
    getNextToken();

    //can be null - then the list is empty
    std::unique_ptr<ArgumentList> argumentList = parseArgumentList();

    expectToken(R_PARENT, "Parsing function: expected \")\"");
    
    std::unique_ptr<Statement> statement = parseStatement();
    if(!statement)
        generateError("Parsing function: function must have a body");

    return std::make_unique<Function>(Function(std::move(type), identifier, 
        std::move(argumentList), std::move(statement)));
}


std::unique_ptr<Declaration> Parser::parseDeclarationInstruction() {
    std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>, 
        std::monostate> declarationVariant = parseDeclarationOrFunction();
    if(!std::get_if<std::unique_ptr<Declaration>>(&declarationVariant))
        return std::unique_ptr<Declaration>(nullptr);
    
    std::unique_ptr<Declaration> declaration = 
        std::move(std::get<std::unique_ptr<Declaration>>(declarationVariant));
    if(!declaration)
        return std::unique_ptr<Declaration>(nullptr);

    expectToken(SEMICOLON, "Parsing declaration instruction: expected \";\"");
    
    return std::move(declaration);
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


std::unique_ptr<Return> Parser::parseReturn() {
    if(RETURN != currentToken.type)
        return std::unique_ptr<Return>(nullptr);
    getNextToken();
    
    //empty expression allowed
    std::unique_ptr<Expression> expression = parseExpression();

    expectToken(SEMICOLON, "Parsing return instruction: expected a \";\"");
    
    return std::make_unique<Return>(Return(std::move(expression)));
}


std::unique_ptr<Instruction> Parser::parseInstruction() {
    std::unique_ptr<If> ifInstruction = parseIf();
    if(ifInstruction)
        return std::make_unique<Instruction>
            (Instruction(std::move(ifInstruction)));
    
    std::unique_ptr<Switch> switchInstruction = parseSwitch();
    if(switchInstruction)
        return std::make_unique<Instruction>
            (Instruction(std::move(switchInstruction)));

    std::unique_ptr<For> forInstruction = parseFor();
    if(forInstruction)
        return std::make_unique<Instruction>
            (Instruction(std::move(forInstruction)));

    std::unique_ptr<Return> returnInstruction = parseReturn();
    if(returnInstruction)
        return std::make_unique<Instruction>
            (Instruction(std::move(returnInstruction)));

    std::unique_ptr<Declaration> declarationInstruction = 
        parseDeclarationInstruction();
    if(declarationInstruction)
        return std::make_unique<Instruction>
            (Instruction(std::move(declarationInstruction)));
    
    std::unique_ptr<Expression> expressionInstruction = parseExpression();
    if(expressionInstruction) {
        expectToken(SEMICOLON, "Parsing instruction: expected \";\"");
        return std::make_unique<Instruction>
            (Instruction(std::move(expressionInstruction)));
    }
    
    // empty expresion, only semicolon
    if(SEMICOLON == currentToken.type) {
        getNextToken();
        return std::make_unique<Instruction>
            (Instruction(std::move(expressionInstruction)));
    }

    return std::unique_ptr<Instruction>(nullptr);
}


std::unique_ptr<InstructionList> Parser::parseInstructionList() {
    std::unique_ptr<Instruction> instruction = parseInstruction();
    std::unique_ptr<InstructionList> instructionList = 
        std::make_unique<InstructionList>(InstructionList());
    while(instruction) {
        instructionList->instructions.push_back(std::move(instruction));
        instruction = parseInstruction();
    }
    return std::move(instructionList);
}


std::unique_ptr<InstructionList> Parser::parseBlock() {
    if(L_BRACKET != currentToken.type)
        return std::unique_ptr<InstructionList>(nullptr);
    getNextToken();

    // cannot be null, but may be empty
    std::unique_ptr<InstructionList> instructionList = parseInstructionList();

    expectToken(R_BRACKET, "Parsing block: expected \"}\"");
    
    return std::move(instructionList);
}


std::unique_ptr<Statement> Parser::parseStatement() {
    std::unique_ptr<InstructionList> instructionList = 
        std::make_unique<InstructionList>(InstructionList());
    if(std::unique_ptr<Instruction> instruction = parseInstruction()) {
        instructionList->instructions.push_back(std::move(instruction));
        return std::make_unique<Statement>(
            Statement(std::move(instructionList)));
    }
        
    if(instructionList = parseBlock())
        return std::make_unique<Statement>(
            Statement(std::move(instructionList)));

    generateError("Parsing statement: expected instruction or block");
    return std::unique_ptr<Statement>(nullptr);
}



std::unique_ptr<If> Parser::parseIf() {
    if(IF != currentToken.type)
        return std::unique_ptr<If>(nullptr);
    getNextToken();

    expectToken(L_PARENT, "Parsing if instruction: expected \"(\"");
    
    std::unique_ptr<Expression> conditionalExpression = parseExpression();
    if(!conditionalExpression)
        generateError("Parsing if instruction: expected expression");

    expectToken(R_PARENT, "Parsing if instruction: expected \")\"");

    std::unique_ptr<Statement> trueStatement = parseStatement();
    if(!trueStatement)
        generateError("Parsing if instruction: expected statement");

    std::unique_ptr<Statement> falseStatement = 
        std::unique_ptr<Statement>(nullptr);
    
    if(ELSE == currentToken.type) {
        getNextToken();
        falseStatement = parseStatement();
        if(!falseStatement)
            generateError("Parsing if instruction: expected statement");
    }
    return std::make_unique<If>(If(std::move(conditionalExpression), 
            std::move(trueStatement), std::move(falseStatement)));
}


std::unique_ptr<For> Parser::parseFor() {
    if(FOR != currentToken.type)
        return std::unique_ptr<For>(nullptr);
    getNextToken();

    expectToken(L_PARENT, "Parsing for instruction: expected \"(\"");
    
    std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>, 
        std::monostate> declarationVariant = parseDeclarationOrFunction();
    if(!std::get_if<std::unique_ptr<Declaration>>(&declarationVariant))
        generateError("Parsing for instruction: expected declaration");
    // may be null
    std::unique_ptr<Declaration> declaration = 
        std::move(std::get<std::unique_ptr<Declaration>>(declarationVariant));
    
    expectToken(SEMICOLON, "Parsing for instruction: expected \";\"");

    // may be null
    std::unique_ptr<Expression> conditionalExpression = parseExpression();
    
    expectToken(SEMICOLON, "Parsing for instruction: expected \";\"");

    // may be null
    std::unique_ptr<Expression> incrementalExpression = parseExpression();
    
    expectToken(R_PARENT, "Parsing for instruction: expected \")\"");

    std::unique_ptr<Statement> statement = parseStatement();
    if(!statement)
        generateError("Parsing for instruction: expected a statement");

    return std::make_unique<For>(For(std::move(declaration), 
        std::move(conditionalExpression), std::move(incrementalExpression),
        std::move(statement)));
}


std::unique_ptr<CaseGo> Parser::parseCaseGo() {
    if(CASE != currentToken.type)
        return std::unique_ptr<CaseGo>(nullptr);
    getNextToken();

    std::unique_ptr<Expression> expression = parseExpression();
    if(!expression)
        generateError("Parsing case go: expected expression");

    expectToken(COLON, "Parsing case go: expected \":\"");
    
    std::unique_ptr<InstructionList> instructionList = parseInstructionList();

    return std::make_unique<CaseGo>(CaseGo(std::move(expression), 
        std::move(instructionList)));
}


std::unique_ptr<CaseC> Parser::parseCaseC() { 
    if(CASE != currentToken.type)
        return std::unique_ptr<CaseC>(nullptr);
    getNextToken();

    if( INT_NUMBER      != currentToken.type &&
        FLOAT_NUMBER    != currentToken.type &&
        STRING_CONSTANT != currentToken.type )
        generateError("Parsing case c: expected a literal");

    Token token = currentToken;
    getNextToken();

    expectToken(COLON, "Parsing case c: expected \":\"");
    
    std::unique_ptr<InstructionList> instructionList = parseInstructionList();

    return std::make_unique<CaseC>(CaseC(token, std::move(instructionList)));
}



std::unique_ptr<Default> Parser::parseDefault() {
    if(DEFAULT != currentToken.type)
        return std::unique_ptr<Default>(nullptr);
    getNextToken();

    expectToken(COLON, "Parsing default: expected \":\"");

    return std::make_unique<Default>(Default(parseInstructionList()));
}



std::unique_ptr<Switch> Parser::parseSwitch() {
    if(SWITCH != currentToken.type)
        return std::unique_ptr<Switch>(nullptr);
    getNextToken();

    if(std::unique_ptr<SwitchGo> switchGo = parseSwitchGoEnd())
        return std::move(switchGo);

    if(std::unique_ptr<SwitchC> switchC = parseSwitchCEnd())
        return std::move(switchC);

    generateError("Parsing switch: could not parse switch go nor switch c");
    return std::unique_ptr<Switch>(nullptr);
}



std::unique_ptr<SwitchGo> Parser::parseSwitchGoEnd() {
    if(L_BRACKET != currentToken.type)
        return std::unique_ptr<SwitchGo>(nullptr);
    getNextToken();

    std::unique_ptr<SwitchGo> switchGo = std::make_unique<SwitchGo>(SwitchGo());
    
    std::unique_ptr<CaseGo> caseGo = parseCaseGo();
    while (caseGo) {
        switchGo->caseGoInstructions.push_back(std::move(caseGo));
        caseGo = parseCaseGo();
    }
    
    switchGo->defaultInstruction = parseDefault();

    expectToken(R_BRACKET, "Parsing switch go: expected \"}\"");
    
    return std::move(switchGo);
}



std::unique_ptr<SwitchC> Parser::parseSwitchCEnd() {
    if(L_PARENT != currentToken.type)
        return std::unique_ptr<SwitchC>(nullptr);
    getNextToken();

    std::unique_ptr<SwitchC> switchC = std::make_unique<SwitchC>(SwitchC());
    
    switchC->postExpression = parsePostExpression();
    if(!switchC->postExpression)
        generateError("Parsing switch c: expected expression");
    
    expectToken(R_PARENT, "Parsing switch c: expected \")\"");
    expectToken(L_BRACKET, "Parsing switch c: expected \"{\"");
    
    std::unique_ptr<CaseC> caseC = parseCaseC();
    while (caseC) {
        switchC->caseCInstructions.push_back(std::move(caseC));
        caseC = parseCaseC();
    }
    
    switchC->defaultInstruction = parseDefault();

    expectToken(R_BRACKET, "Parsing switch c: expected \"}\"");

    return std::move(switchC);
}



std::unique_ptr<Program> Parser::parseProgram() {
    setUpPeekedToken();
    getNextToken();

    std::unique_ptr<Program> program = std::make_unique<Program>(Program());
    while(EOT != currentToken.type) {
        std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>, 
            std::monostate> variant = parseDeclarationOrFunction();

        // declaration
        if(std::unique_ptr<Declaration>* declaration = 
            std::get_if<std::unique_ptr<Declaration>>(&variant)) {
            if(!*declaration)
                generateError("Parsing program: expected a declaration");
            program->declarationFunctionVector.push_back
                (std::move(*declaration));
            expectToken(SEMICOLON, 
                "Parsing global declaration: expected a \";\"");
            continue;
        }

        // function
        if(std::unique_ptr<Function>* function = 
            std::get_if<std::unique_ptr<Function>>(&variant)) {
        
            if(!*function)
                generateError("Parsing program: expected a function");
            program->declarationFunctionVector.push_back(std::move(*function));
            continue;
        }

        generateError("Parsing declaration or function: could not parse neither"
            " declaration nor function");
    }

    return std::move(program);
}


