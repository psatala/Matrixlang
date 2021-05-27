#include "AuxiliaryFunctionsExecutor.h"

TEST(ExecutionVariables, simpleVariableCreation) {
    std::unique_ptr<Variable> variable = createIntVariable();
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(variable.get());
    
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionVariables, vectorVariableCreation) {
    std::unique_ptr<Variable> variable = createVectorFloatVariable();
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
    std::unique_ptr<Variable> variable = createMatrixStringVariable();
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
    std::unique_ptr<Variable> variable = createVectorVectorFloatVariable();
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



TEST(ExecutionVariables, simpleVariableCopy) {
    std::unique_ptr<Variable> originalVariable = createIntVariable();
    std::unique_ptr<Variable> copiedVariable = VariableManagement::copyVariable
        (originalVariable.get());
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(copiedVariable.get());
    
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionVariables, vectorVariableCopy) {
    std::unique_ptr<Variable> originalVariable = createVectorFloatVariable();
    std::unique_ptr<Variable> copiedVariable = VariableManagement::copyVariable
        (originalVariable.get());
    VectorVariable* vectorVariable = 
        dynamic_cast<VectorVariable*>(copiedVariable.get());
    
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

TEST(ExecutionVariables, matrixVariableCopy) {
    std::unique_ptr<Variable> originalVariable = createMatrixStringVariable();
    std::unique_ptr<Variable> copiedVariable = VariableManagement::copyVariable
        (originalVariable.get());
    MatrixVariable* matrixVariable = 
        dynamic_cast<MatrixVariable*>(copiedVariable.get());
    
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

TEST(ExecutionVariables, nestedVariableCopy) {
    std::unique_ptr<Variable> originalVariable = createVectorVectorFloatVariable();
    std::unique_ptr<Variable> copiedVariable = VariableManagement::copyVariable
        (originalVariable.get());
    VectorVariable* outerVectorVariable = 
        dynamic_cast<VectorVariable*>(copiedVariable.get());
    
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



TEST(ExecutionVariables, simpleVariableIntLiteral) {
    std::unique_ptr<Variable> variable = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(variable.get());
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 3);
}

TEST(ExecutionVariables, simpleVariableFloatLiteral) {
    std::unique_ptr<Variable> variable = std::make_unique<SimpleVariable>
        (SimpleVariable(3.14f));
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(variable.get());
    GTEST_ASSERT_EQ(simpleVariable->type, FLOAT);
    GTEST_ASSERT_EQ(std::get<float>(simpleVariable->value), 3.14f);
}

TEST(ExecutionVariables, simpleVariableStringLiteral) {
    std::unique_ptr<Variable> variable = std::make_unique<SimpleVariable>
        (SimpleVariable("abc"));
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(variable.get());
    GTEST_ASSERT_EQ(simpleVariable->type, STRING);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleVariable->value), "abc");
}