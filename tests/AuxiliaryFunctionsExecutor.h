#pragma once

#include <gtest/gtest.h>

#include "../headers/ExecutionObjects/Execution.h"
#include "../headers/LanguageObjects/Expressions/LiteralExpression.h"
#include "../headers/LanguageObjects/Expressions/BinaryExpression.h"
#include "../headers/LanguageObjects/Expressions/VariableExpression.h"
#include "../headers/LanguageObjects/Statement.h"
#include "../headers/Interpreter.h"
#include "TestPrograms.h"


//class for passing data to parametrised tests
class ExecutorInputOutput {
public:
    std::string codeInput;
    std::string userInput;
    std::string errorOutput;
    std::string standardOutput;
    ExecutorInputOutput(std::string codeInput, std::string userInput, 
        std::string errorOutput, std::string standardOutput) :
        codeInput(codeInput), userInput(userInput), errorOutput(errorOutput), 
        standardOutput(standardOutput) {}
};


inline std::unique_ptr<Variable> createIntVariable() {
     std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(INT));
    
    return VariableManagement::createVariable(simpleType.get(), nullptr);
}

inline std::unique_ptr<Variable> createFloatVariable() {
     std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(FLOAT));
    
    return VariableManagement::createVariable(simpleType.get(), nullptr);
}

inline std::unique_ptr<Variable> createVectorFloatVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(FLOAT));
    std::unique_ptr<LiteralExpression> expression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> vectorType = 
    std::make_unique<VectorType>(VectorType(std::move(simpleType), 
        std::move(expression)));
    
    return VariableManagement::createVariable(vectorType.get(), nullptr);
}

inline std::unique_ptr<Variable> createVectorIntVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(INT));
    std::unique_ptr<LiteralExpression> expression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> vectorType = 
    std::make_unique<VectorType>(VectorType(std::move(simpleType), 
        std::move(expression)));
    
    return VariableManagement::createVariable(vectorType.get(), nullptr);
}

inline std::unique_ptr<Variable> createMatrixStringVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(STRING));
    std::unique_ptr<LiteralExpression> firstExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<LiteralExpression> secondExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<MatrixType> matrixType = 
    std::make_unique<MatrixType>(MatrixType(std::move(simpleType), 
        std::move(firstExpression), std::move(secondExpression)));
    
    return VariableManagement::createVariable(matrixType.get(), nullptr);
}

inline std::unique_ptr<Variable> createMatrixIntVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(INT));
    std::unique_ptr<LiteralExpression> firstExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<LiteralExpression> secondExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<MatrixType> matrixType = 
    std::make_unique<MatrixType>(MatrixType(std::move(simpleType), 
        std::move(firstExpression), std::move(secondExpression)));
    
    return VariableManagement::createVariable(matrixType.get(), nullptr);
}

inline std::unique_ptr<Variable> createVectorVectorFloatVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(FLOAT));
    std::unique_ptr<LiteralExpression> innerExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> innerVectorType = 
    std::make_unique<VectorType>(VectorType(std::move(simpleType), 
        std::move(innerExpression)));
    std::unique_ptr<LiteralExpression> outerExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> outerVectorType = 
    std::make_unique<VectorType>(VectorType(std::move(innerVectorType), 
        std::move(outerExpression)));

    return VariableManagement::createVariable(outerVectorType.get(), nullptr);
}

inline std::unique_ptr<Statement> createStatementWithAssignment(
    std::string identifier, int valueToAssign, TokenType tokenType = ASSIGN) {

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression(identifier)),
        std::make_unique<LiteralExpression>(LiteralExpression(
            Token(INT, valueToAssign))),
        std::make_unique<Operator>(Operator(tokenType))
    );
    Statement statement = Statement(std::make_unique<Instruction>(
        Instruction(
            std::make_unique<BinaryExpression>(std::move(binaryExpression))
        )
    ));

    return std::make_unique<Statement>(std::move(statement));
}

inline std::unique_ptr<InstructionList> createInstructionList(
    std::string identifier, int value, TokenType tokenType) {

    InstructionList instructionList = InstructionList();
    instructionList.instructions.push_back(std::make_unique<Instruction>(
        Instruction(std::make_unique<BinaryExpression>(BinaryExpression(
            std::make_unique<VariableExpression>(VariableExpression(
                identifier)),
            std::make_unique<LiteralExpression>(LiteralExpression(
                Token(INT, value))),
            std::make_unique<Operator>(Operator(tokenType)))    
        ))));
    return std::make_unique<InstructionList>(std::move(instructionList));
}