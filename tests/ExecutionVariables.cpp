#include <gtest/gtest.h>

#include "../headers/ExecutionObjects/Execution.h"
#include "../headers/LanguageObjects/LiteralExpression.h"

TEST(ExecutionVariables, simpleVariableCreation) {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(INT));
    
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(simpleType.get());
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(variable.get());
    
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionVariables, vectorVariableCreation) {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(FLOAT));
    std::unique_ptr<LiteralExpression> expression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<VectorType> vectorType = 
    std::make_unique<VectorType>(VectorType(std::move(simpleType), 
        std::move(expression)));
    
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(vectorType.get());
    VectorVariable* vectorVariable = 
        dynamic_cast<VectorVariable*>(variable.get());
    
    ASSERT_TRUE(vectorVariable);
    GTEST_ASSERT_EQ(vectorVariable->type, VECTOR);
    GTEST_ASSERT_EQ(vectorVariable->length, 2);
    
    for(unsigned int i = 0; i < vectorVariable->length; ++i) {
        SimpleVariable* innerSimpleVariable = 
            dynamic_cast<SimpleVariable*>(vectorVariable->values[i].get());
        
        ASSERT_TRUE(innerSimpleVariable);
        GTEST_ASSERT_EQ(innerSimpleVariable->type, FLOAT);
        GTEST_ASSERT_EQ(std::get<float>(innerSimpleVariable->value), 0.0f);
    }

}

TEST(ExecutionVariables, matrixVariableCreation) {
    std::unique_ptr<SimpleType> simpleType = 
        std::make_unique<SimpleType>(SimpleType(STRING));
    std::unique_ptr<LiteralExpression> firstExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<LiteralExpression> secondExpression = 
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2)));
    std::unique_ptr<MatrixType> matrixType = 
    std::make_unique<MatrixType>(MatrixType(std::move(simpleType), 
        std::move(firstExpression), std::move(secondExpression)));
    
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(matrixType.get());
    MatrixVariable* matrixVariable = 
        dynamic_cast<MatrixVariable*>(variable.get());
    
    ASSERT_TRUE(matrixVariable);
    GTEST_ASSERT_EQ(matrixVariable->type, MATRIX);
    GTEST_ASSERT_EQ(matrixVariable->firstLength, 2);
    GTEST_ASSERT_EQ(matrixVariable->secondLength, 2);
    
    for(unsigned int i = 0; i < matrixVariable->firstLength; ++i) {
        for(unsigned int j = 0; j < matrixVariable->secondLength; ++j) {
            SimpleVariable* innerSimpleVariable = dynamic_cast<SimpleVariable*>
                (matrixVariable->values[i][j].get());
            
            ASSERT_TRUE(innerSimpleVariable);
            GTEST_ASSERT_EQ(innerSimpleVariable->type, STRING);
            GTEST_ASSERT_EQ(std::get<std::string>(innerSimpleVariable->value), 
                "");
        }
    }

}

TEST(ExecutionVariables, nestedVariableCreation) {
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

    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(outerVectorType.get());
    VectorVariable* outerVectorVariable = 
        dynamic_cast<VectorVariable*>(variable.get());
    
    ASSERT_TRUE(outerVectorVariable);
    GTEST_ASSERT_EQ(outerVectorVariable->type, VECTOR);
    GTEST_ASSERT_EQ(outerVectorVariable->length, 2);
    
    for(unsigned int i = 0; i < outerVectorVariable->length; ++i) {
        VectorVariable* innerVectorVariable = 
            dynamic_cast<VectorVariable*>(outerVectorVariable->values[i].get());
        
        ASSERT_TRUE(innerVectorVariable);
        GTEST_ASSERT_EQ(innerVectorVariable->type, VECTOR);
        GTEST_ASSERT_EQ(innerVectorVariable->length, 2);

        for(unsigned int j = 0; j < innerVectorVariable->length; ++j) {
            SimpleVariable* innerSimpleVariable = dynamic_cast<SimpleVariable*>
                (innerVectorVariable->values[j].get());
            
            ASSERT_TRUE(innerSimpleVariable);
            GTEST_ASSERT_EQ(innerSimpleVariable->type, FLOAT);
            GTEST_ASSERT_EQ(std::get<float>(innerSimpleVariable->value), 0.0f);
        }
    }

}