#pragma once

#include <gtest/gtest.h>

#include "../headers/ExecutionObjects/Execution.h"
#include "../headers/LanguageObjects/LiteralExpression.h"

inline std::unique_ptr<Variable> createIntVariable() {
     std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(INT));
    
    return VariableManagement::createVariable(simpleType.get());
}

inline std::unique_ptr<Variable> createFloatVariable() {
     std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(FLOAT));
    
    return VariableManagement::createVariable(simpleType.get());
}

inline std::unique_ptr<Variable> createVectorFloatVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(FLOAT));
    std::unique_ptr<LiteralExpression> expression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> vectorType = 
    std::make_unique<VectorType>(VectorType(std::move(simpleType), 
        std::move(expression)));
    
    return VariableManagement::createVariable(vectorType.get());
}

inline std::unique_ptr<Variable> createVectorIntVariable() {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(INT));
    std::unique_ptr<LiteralExpression> expression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> vectorType = 
    std::make_unique<VectorType>(VectorType(std::move(simpleType), 
        std::move(expression)));
    
    return VariableManagement::createVariable(vectorType.get());
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
    
    return VariableManagement::createVariable(matrixType.get());
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

    return VariableManagement::createVariable(outerVectorType.get());
}