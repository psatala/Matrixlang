#include "AuxiliaryFunctionsExecutor.h"
#include "../headers/ExecutionObjects/ScopeManager.h"
#include "../headers/Interpreter.h"

TEST(ExecutionExpressions, simpleVariableChange) {
    Scope scope;
    scope.setVariable("a", std::make_unique<SimpleVariable>(SimpleVariable(6)));
    Variable* changedVariable = scope.getVariable("a");
    std::unique_ptr<Variable> targetVariable = 
        std::make_unique<SimpleVariable>(SimpleVariable(13));
    VariableManagement::copyVariableContent(changedVariable, 
        targetVariable.get());
    
    Variable* variableAfterChange = scope.getVariable("a");
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(variableAfterChange);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 13);
}

TEST(ExecutionExpressions, vectorVariableChange) {
    Scope scope;
    scope.setVariable("v", std::move(createVectorIntVariable()));
    Variable* changedVariable = scope.getVariable("v");

    VectorVariable* vectorVariable = 
        dynamic_cast<VectorVariable*>(changedVariable);
    
    std::unique_ptr<Variable> targetVariable = 
        std::make_unique<SimpleVariable>(SimpleVariable(13));
    VariableManagement::copyVariableContent(vectorVariable->values[1].get(), 
        targetVariable.get());

    
    Variable* variableAfterChange = scope.getVariable("v");
    VectorVariable* vectorVariableAfterChange = 
        dynamic_cast<VectorVariable*>(variableAfterChange);
    ASSERT_TRUE(vectorVariableAfterChange);
    GTEST_ASSERT_EQ(vectorVariableAfterChange->type, VECTOR);
    GTEST_ASSERT_EQ(vectorVariableAfterChange->length, 2);
    
    // first element
    SimpleVariable* innerSimpleVariable = dynamic_cast<SimpleVariable*>
        (vectorVariableAfterChange->values[0].get());
        
    ASSERT_TRUE(innerSimpleVariable);
    GTEST_ASSERT_EQ(innerSimpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(innerSimpleVariable->value), 0);

    // second element
    innerSimpleVariable = dynamic_cast<SimpleVariable*>
        (vectorVariableAfterChange->values[1].get());
        
    ASSERT_TRUE(innerSimpleVariable);
    GTEST_ASSERT_EQ(innerSimpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(innerSimpleVariable->value), 13);
    
}

TEST(ExecutionExpressions, variableExpressionInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(12)));
    
    VariableExpression variableExpression = VariableExpression("a");
    std::unique_ptr<Variable> returnedVariable = 
        variableExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 12);
}

TEST(ExecutionExpressions, variableExpressionVectorInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("v", 
        createVectorIntVariable());
    
    VariableExpression variableExpression = VariableExpression("v");
    std::unique_ptr<Variable> returnedVariable = 
        variableExpression.value(&scopeManager);

    VectorVariable* vectorVariable = 
        dynamic_cast<VectorVariable*>(returnedVariable.get());
    
    ASSERT_TRUE(vectorVariable);
    GTEST_ASSERT_EQ(vectorVariable->type, VECTOR);
    GTEST_ASSERT_EQ(vectorVariable->length, 2);
    
    for(unsigned int i = 0; i < vectorVariable->length; ++i) {
        SimpleVariable* innerSimpleVariable = 
            dynamic_cast<SimpleVariable*>(vectorVariable->values[i].get());
        
        ASSERT_TRUE(innerSimpleVariable);
        GTEST_ASSERT_EQ(innerSimpleVariable->type, INT);
        GTEST_ASSERT_EQ(std::get<int>(innerSimpleVariable->value), 0);
    }
}

TEST(ExecutionExpressions, vectorIndexExpressionVectorInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("v", createVectorIntVariable());
    
    VariableExpression variableExpression = VariableExpression("v");
    LiteralExpression literalExpression = LiteralExpression(Token(INT, 1));
    VectorIndexExpression vectorIndexExpression = VectorIndexExpression(
        std::make_unique<VariableExpression>(variableExpression),
        std::make_unique<LiteralExpression>(literalExpression)
    );
    std::unique_ptr<Variable> returnedVariable = 
        vectorIndexExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionExpressions, matrixIndexExpressionMatrixString) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("m", createMatrixStringVariable());
    
    VariableExpression variableExpression = VariableExpression("m");
    LiteralExpression literalExpression1 = LiteralExpression(Token(INT, 1));
    LiteralExpression literalExpression2 = LiteralExpression(Token(INT, 1));
    MatrixIndexExpression matrixIndexExpression = MatrixIndexExpression(
        std::make_unique<VariableExpression>(variableExpression),
        std::make_unique<LiteralExpression>(literalExpression1),
        std::make_unique<LiteralExpression>(literalExpression2)
    );
    std::unique_ptr<Variable> returnedVariable = 
        matrixIndexExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, STRING);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleVariable->value), "");
}

TEST(ExecutionExpressions, literalExpressionInt) {
    ScopeManager scopeManager;
    
    LiteralExpression literalExpression = LiteralExpression(Token(INT, 14));
    
    std::unique_ptr<Variable> returnedVariable = 
        literalExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 14);
}

TEST(ExecutionExpressions, literalExpressionFloat) {
    ScopeManager scopeManager;
    
    LiteralExpression literalExpression = 
        LiteralExpression(Token(FLOAT, 2.71f));
    
    std::unique_ptr<Variable> returnedVariable = 
        literalExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, FLOAT);
    GTEST_ASSERT_EQ(std::get<float>(simpleVariable->value), 2.71f);
}

TEST(ExecutionExpressions, postExpressionInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(16)));
    
    PostExpression postExpression = PostExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<Operator>(Operator(INCREMENT))
    );
    std::unique_ptr<Variable> returnedVariable = 
        postExpression.value(&scopeManager);

    // same value returned
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 16);


    // incremented value in scope manager
    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 17);

}

TEST(ExecutionExpressions, unaryExpressionInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(18)));
    
    UnaryIncrementalExpression unaryIncrementalExpression = 
        UnaryIncrementalExpression(
        std::make_unique<Operator>(Operator(INCREMENT)),
        std::make_unique<VariableExpression>(VariableExpression("a"))
    );
    std::unique_ptr<Variable> returnedVariable = 
        unaryIncrementalExpression.value(&scopeManager);

    // incremented value returned
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 19);


    // incremented value in scope manager
    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 19);

}

TEST(ExecutionExpressions, unaryMinusExpression) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(18)));
    
    UnaryExpression unaryExpression = UnaryExpression(
        std::make_unique<Operator>(Operator(MINUS)),
        std::make_unique<VariableExpression>(VariableExpression("a"))
    );
    std::unique_ptr<Variable> returnedVariable = 
        unaryExpression.value(&scopeManager);

    // incremented value returned
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), -18);


    // incremented value in scope manager
    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 18);

}

TEST(ExecutionExpressions, unaryNotExpression) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(18)));
    
    UnaryExpression unaryExpression = UnaryExpression(
        std::make_unique<Operator>(Operator(NOT)),
        std::make_unique<VariableExpression>(VariableExpression("a"))
    );
    std::unique_ptr<Variable> returnedVariable = 
        unaryExpression.value(&scopeManager);

    // incremented value returned
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);


    // incremented value in scope manager
    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 18);

}

TEST(ExecutionExpressions, binaryExpressionAssignInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(4)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 33))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 33);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 33);
}


TEST(ExecutionExpressions, binaryExpressionAssignVector) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("v", createVectorIntVariable());
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VectorIndexExpression>(VectorIndexExpression(
        std::make_unique<VariableExpression>(VariableExpression("v")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0))))
        ),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 37))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 37);


    Variable* variable = scopeManager.getVariable("v");
    VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>(variable);

    ASSERT_TRUE(vectorVariable);
    GTEST_ASSERT_EQ(vectorVariable->type, VECTOR);

    // first element
    simpleVariable = dynamic_cast<SimpleVariable*>
        (vectorVariable->values[0].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 37);

    // second element
    simpleVariable = dynamic_cast<SimpleVariable*>
        (vectorVariable->values[1].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}


TEST(ExecutionExpressions, binaryExpressionAssignMatrix) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("v", createMatrixIntVariable());
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<MatrixIndexExpression>(MatrixIndexExpression(
        std::make_unique<VariableExpression>(VariableExpression("v")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 1))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0))))
        ),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 37))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 37);


    Variable* variable = scopeManager.getVariable("v");
    MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>(variable);

    ASSERT_TRUE(matrixVariable);
    GTEST_ASSERT_EQ(matrixVariable->type, MATRIX);

    // elements

    simpleVariable = dynamic_cast<SimpleVariable*>
        (matrixVariable->values[0][0].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);

    simpleVariable = dynamic_cast<SimpleVariable*>
        (matrixVariable->values[0][1].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);

    simpleVariable = dynamic_cast<SimpleVariable*>
        (matrixVariable->values[1][0].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 37);

    simpleVariable = dynamic_cast<SimpleVariable*>
        (matrixVariable->values[1][1].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}





TEST(ExecutionExpressions, binaryExpressionPlusAssignInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(44)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 33))),
        std::make_unique<Operator>(Operator(PLUS_ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 77);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 77);
}

TEST(ExecutionExpressions, binaryExpressionMinusAssignInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(44)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 33))),
        std::make_unique<Operator>(Operator(MINUS_ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 11);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 11);
}

TEST(ExecutionExpressions, binaryExpressionMultiplyAssignInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(44)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 3))),
        std::make_unique<Operator>(Operator(MULTIPLY_ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 132);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 132);
}

TEST(ExecutionExpressions, binaryExpressionDivideAssignInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(47)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 6))),
        std::make_unique<Operator>(Operator(DIVIDE_ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 7);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 7);
}

TEST(ExecutionExpressions, binaryExpressionModuloAssignInt) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(47)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 6))),
        std::make_unique<Operator>(Operator(MODULO_ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 5);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 5);
}




TEST(ExecutionExpressions, binaryExpressionPlusInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 7))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 6))),
        std::make_unique<Operator>(Operator(PLUS))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 13);
}

TEST(ExecutionExpressions, binaryExpressionMinusInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 7))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 6))),
        std::make_unique<Operator>(Operator(MINUS))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionExpressions, binaryExpressionMultiplyInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 7))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 6))),
        std::make_unique<Operator>(Operator(MULTIPLY))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 42);
}

TEST(ExecutionExpressions, binaryExpressionDivideInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 7))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(DIVIDE))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionExpressions, binaryExpressionModuloInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 7))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(MODULO))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 2);
}



TEST(ExecutionExpressions, binaryExpressionLessThanInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(LESS_THAN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionExpressions, binaryExpressionLessEqualInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<Operator>(Operator(LESS_EQUAL))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionExpressions, binaryExpressionMoreThanInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(MORE_THAN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionExpressions, binaryExpressionMoreEqualInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(MORE_EQUAL))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionExpressions, binaryExpressionEqualInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<Operator>(Operator(EQUAL))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionExpressions, binaryExpressionNotEqualInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 4))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(NOT_EQUAL))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}




TEST(ExecutionExpressions, binaryExpressionAndInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(AND))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionExpressions, binaryExpressionOrInt) {
    ScopeManager scopeManager;

    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0))),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 5))),
        std::make_unique<Operator>(Operator(OR))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionExpressions, logicalValueTrue) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(4)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 33))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.logicalValue(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 33);
}

TEST(ExecutionExpressions, logicalValueFalse) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(4)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    std::unique_ptr<Variable> returnedVariable = 
        binaryExpression.logicalValue(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);

    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionExpressions, stringExpressionValue) {
    ScopeManager scopeManager;
    
    StringExpression stringExpression = StringExpression();
    stringExpression.stringLiteralsAndExpressions.push_back("abc ");
    stringExpression.stringLiteralsAndExpressions.push_back(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 123)))
    );
    stringExpression.stringLiteralsAndExpressions.push_back(" def");

    std::unique_ptr<Variable> returnedVariable = 
        stringExpression.value(&scopeManager);

    
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
        (returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, STRING);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleVariable->value), 
        "abc 123 def");
}



TEST(ExecutionExpression, vectorCreation) {
    VectorType vectorType = VectorType(
        std::make_unique<SimpleType>(SimpleType(INT)), 
        std::make_unique<LiteralExpression>
            (LiteralExpression(Token(INT, 123)))
        );
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(&vectorType, nullptr);
    
    VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>
        (variable.get());
        
    ASSERT_TRUE(vectorVariable);
    GTEST_ASSERT_EQ(vectorVariable->type, VECTOR);
    GTEST_ASSERT_EQ(vectorVariable->length, 123);
}

TEST(ExecutionExpression, matrixCreation) {
    MatrixType matrixType = MatrixType(
        std::make_unique<SimpleType>(SimpleType(INT)), 
        std::make_unique<LiteralExpression>
            (LiteralExpression(Token(INT, 100))),
        std::make_unique<LiteralExpression>
            (LiteralExpression(Token(INT, 200)))
        );
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(&matrixType, nullptr);
    
    MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>
        (variable.get());
        
    ASSERT_TRUE(matrixVariable);
    GTEST_ASSERT_EQ(matrixVariable->type, MATRIX);
    GTEST_ASSERT_EQ(matrixVariable->firstLength, 100);
    GTEST_ASSERT_EQ(matrixVariable->secondLength, 200);
}

TEST(ExecutionExpression, vectorContextualCreation) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", std::make_unique<SimpleVariable>
        (SimpleVariable(333)));
    VectorType vectorType = VectorType(
        std::make_unique<SimpleType>(SimpleType(INT)), 
        std::make_unique<VariableExpression>(VariableExpression("a"))
        );
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(&vectorType, &scopeManager);
    
    VectorVariable* vectorVariable = dynamic_cast<VectorVariable*>
        (variable.get());
        
    ASSERT_TRUE(vectorVariable);
    GTEST_ASSERT_EQ(vectorVariable->type, VECTOR);
    GTEST_ASSERT_EQ(vectorVariable->length, 333);
}

TEST(ExecutionExpression, matrixContextualCreation) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", std::make_unique<SimpleVariable>
        (SimpleVariable(333)));
    scopeManager.addGlobalVariable("b", std::make_unique<SimpleVariable>
        (SimpleVariable(444)));
    MatrixType matrixType = MatrixType(
        std::make_unique<SimpleType>(SimpleType(INT)), 
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<VariableExpression>(VariableExpression("b"))
        );
    std::unique_ptr<Variable> variable = 
        VariableManagement::createVariable(&matrixType, &scopeManager);
    
    MatrixVariable* matrixVariable = dynamic_cast<MatrixVariable*>
        (variable.get());
        
    ASSERT_TRUE(matrixVariable);
    GTEST_ASSERT_EQ(matrixVariable->type, MATRIX);
    GTEST_ASSERT_EQ(matrixVariable->firstLength, 333);
    GTEST_ASSERT_EQ(matrixVariable->secondLength, 444);
}