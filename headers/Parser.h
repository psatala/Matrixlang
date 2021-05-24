#pragma once

#include <functional>

#include "Lexer.h"

#include "LanguageObjects.h"
#include "LanguageObjects/BinaryExpression.h"
#include "LanguageObjects/Expression.h"
#include "LanguageObjects/Operator.h"
#include "LanguageObjects/LiteralExpression.h"
#include "LanguageObjects/Program.h"
#include "LanguageObjects/UnaryExpression.h"
#include "LanguageObjects/FuncallExpression.h"
#include "LanguageObjects/VectorIndexExpression.h"
#include "LanguageObjects/MatrixIndexExpression.h"
#include "LanguageObjects/PostExpression.h"
#include "LanguageObjects/MatrixType.h"
#include "LanguageObjects/SimpleType.h"
#include "LanguageObjects/StringExpression.h"
#include "LanguageObjects/Type.h"
#include "LanguageObjects/VectorType.h"
#include "LanguageObjects/Declaration.h"
#include "LanguageObjects/ArgumentList.h"
#include "LanguageObjects/Function.h"
#include "LanguageObjects/Statement.h"
#include "LanguageObjects/Return.h"
#include "LanguageObjects/If.h"
#include "LanguageObjects/For.h"
#include "LanguageObjects/Instruction.h"
#include "LanguageObjects/InstructionList.h"
#include "LanguageObjects/Default.h"
#include "LanguageObjects/CaseGo.h"
#include "LanguageObjects/CaseC.h"
#include "LanguageObjects/Switch.h"
#include "LanguageObjects/SwitchGo.h"
#include "LanguageObjects/SwitchC.h"


class Parser {
    std::ostream& errStream;

    Token currentToken;
    bool isEOTProcessed = false;

    void getNextToken();
    void generateError(std::string message);
    void expectToken(TokenType type, std::string errorMessage);


    std::unique_ptr<Expression> constructLeftTreeFromExpressionVector(
        std::vector<std::unique_ptr<Expression>> expressionVector,
        std::vector<std::unique_ptr<Operator>> operatorVector);
    std::unique_ptr<Expression> constructRightTreeFromExpressionVector(
        std::vector<std::unique_ptr<Expression>> expressionVector,
        std::vector<std::unique_ptr<Operator>> operatorVector);    
    



    std::unique_ptr<SimpleType> parseSimpleType();
    std::unique_ptr<VectorType> parseVectorType();
    std::unique_ptr<MatrixType> parseMatrixType();
    std::unique_ptr<Type> parseType();



    std::unique_ptr<Operator> parseOperator(std::vector<TokenType> 
        acceptedOperators);
    
    std::unique_ptr<Operator> parsePostOperator();
    std::unique_ptr<Operator> parseUnaryRValueOperator();
    std::unique_ptr<Operator> parseUnaryLValueOperator();
    std::unique_ptr<Operator> parseMultiplicationOperator();
    std::unique_ptr<Operator> parseAdditionOperator();
    std::unique_ptr<Operator> parseRelationOperator();
    std::unique_ptr<Operator> parseAndOperator();
    std::unique_ptr<Operator> parseOrOperator();
    std::unique_ptr<Operator> parseAssignmentOperator();
    


    std::unique_ptr<Expression> parseStringExpression();
    std::unique_ptr<Expression> parseLiteralExpression();
    std::unique_ptr<Expression> parsePrimaryExpression();

    std::unique_ptr<Expression> parseFuncallExpression();
    std::unique_ptr<Expression> parseLValueExpression();
    std::unique_ptr<Expression> parsePostExpression();

    std::unique_ptr<Expression> parseUnaryExpression(
        std::function<std::unique_ptr<Expression>()> parseLowerExpression,
        std::function<std::unique_ptr<Operator>()> parseThisOperator);
    std::unique_ptr<Expression> parseAllUnaryExpressions();

    std::unique_ptr<Expression> parseBinaryExpression(
        std::function<std::unique_ptr<Expression>()> parseLowerExpression,
        std::function<std::unique_ptr<Operator>()> parseThisOperator,
        std::string errorMessage, bool isRightAssociative = false);
    
    std::unique_ptr<Expression> parseMultiplicationExpression();
    std::unique_ptr<Expression> parseAdditionExpression();
    std::unique_ptr<Expression> parseRelationExpression();
    std::unique_ptr<Expression> parseAndExpression();
    std::unique_ptr<Expression> parseOrExpression();
    std::unique_ptr<Expression> parseRValueExpression();

    std::unique_ptr<Expression> parseAssignmentExpression();
    
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<ExpressionList> parseExpressionList();
    
    std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>> 
        parseDeclarationOrFunction();
    std::unique_ptr<Declaration> parseDeclarationEnd(std::unique_ptr<Type> type,
        std::string identifier);
    std::unique_ptr<Function> parseFunctionEnd(std::unique_ptr<Type> type, 
        std::string identifier);
    std::unique_ptr<Declaration> parseDeclarationInstruction();
    std::unique_ptr<Function> parseFunction();

    std::unique_ptr<ArgumentList> parseArgumentList();
    std::unique_ptr<Return> parseReturn();

    std::unique_ptr<Instruction> parseInstruction();
    std::unique_ptr<InstructionList> parseInstructionList();
    std::unique_ptr<InstructionList> parseBlock();
    std::unique_ptr<Statement> parseStatement();

    std::unique_ptr<If> parseIf();
    std::unique_ptr<For> parseFor();

    std::unique_ptr<CaseGo> parseCaseGo();
    std::unique_ptr<CaseC> parseCaseC();
    std::unique_ptr<Default> parseDefault();

    std::unique_ptr<Switch> parseSwitch();
    std::unique_ptr<SwitchGo> parseSwitchGoEnd();
    std::unique_ptr<SwitchC> parseSwitchCEnd();


public:
    Lexer lexer;


    std::unique_ptr<Program> parseProgram();

    Parser(std::unique_ptr<std::istream> inStream, std::ostream& errStream) : 
        errStream(errStream),
        lexer(std::move(inStream), errStream) {}
};