#include "AuxiliaryFunctionsExecutor.h"
#include "../headers/ExecutionObjects/ScopeManager.h"
#include "../headers/Interpreter.h"

TEST(ExecutionScope, basicScopeInt) {
    Scope scope;
    scope.setVariable("a", std::make_unique<SimpleVariable>(SimpleVariable(6)));
    Variable* variable = scope.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 6);

    variable = scope.getVariable("b");
    GTEST_ASSERT_EQ(variable, nullptr);
}

TEST(ExecutionScope, basicScopeVector) {
    Scope scope;
    scope.setVariable("v", std::move(createVectorFloatVariable()));
    Variable* variable = scope.getVariable("v");
    VectorVariable* vectorVariable = 
        dynamic_cast<VectorVariable*>(variable);
    
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



TEST(ExecutionScope, scopeManagerGlobal) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(8)));
    
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 8);

    try {
        variable = scopeManager.getVariable("b");
        ASSERT_TRUE(false); // above line should throw, so this line should not
                            // be executed
    }
    catch(std::string errorMessage) {
        GTEST_ASSERT_EQ(errorMessage, "Unknown identifier \"b\"");
    }
}

TEST(ExecutionScope, scopeManagerSimpleLocal) {
    ScopeManager scopeManager;
    scopeManager.addFuncall();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(9)));
    
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 9);

    try {
        variable = scopeManager.getVariable("b");
        ASSERT_TRUE(false); // above line should throw, so this line should not
                            // be executed
    }
    catch(std::string errorMessage) {
        GTEST_ASSERT_EQ(errorMessage, "Unknown identifier \"b\"");
    }
}

TEST(ExecutionScope, scopeManagerDifferentFuncallsCannotSeeEachOther) {
    ScopeManager scopeManager;
    scopeManager.addFuncall();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(52)));
    scopeManager.addFuncall();

    try {
        // cannot see variable from another funcall
        Variable* variable = scopeManager.getVariable("a");
        ASSERT_TRUE(false); // above line should throw, so this line should not
                            // be executed
    }
    catch(std::string errorMessage) {
        GTEST_ASSERT_EQ(errorMessage, "Unknown identifier \"a\"");
    }

    scopeManager.endFuncall();
    // now current funcall has variable "a"
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 52);

}

TEST(ExecutionScope, scopeManagerInnerBlockPreferred) {
    ScopeManager scopeManager;
    scopeManager.addFuncall();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(1)));
    scopeManager.addBlock();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(2)));
    
    // inner block is preferred
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 2);

    scopeManager.endBlock();
    
    // only one block left
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionScope, scopeManagerInnerBlockSetting) {
    ScopeManager scopeManager;
    scopeManager.addFuncall();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(1)));
    scopeManager.addBlock();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(2)));
    
    // when setting variable, inner block is also preferred
    scopeManager.setVariable("a", std::make_unique<SimpleVariable>
        (SimpleVariable(3)));

    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 3);

    scopeManager.endBlock();
    
    // only one block left
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 1);
}

TEST(ExecutionScope, scopeManagerLocalOverGlobal) {
    ScopeManager scopeManager;
    scopeManager.addFuncall();
    scopeManager.addLocalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable("local")));
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable("global")));
    
    // local is preferred
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, STRING);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleVariable->value), "local");

    scopeManager.endFuncall();
    
    // only global scope left
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, STRING);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleVariable->value), "global");
}



TEST(ExecutionScope, simpleVariableChange) {
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

TEST(ExecutionScope, vectorVariableChange) {
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

TEST(ExecutionScope, variableExpressionInt) {
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

TEST(ExecutionScope, variableExpressionVectorInt) {
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

TEST(ExecutionScope, vectorIndexExpressionVectorInt) {
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

TEST(ExecutionScope, matrixIndexExpressionMatrixString) {
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

TEST(ExecutionScope, literalExpressionInt) {
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

TEST(ExecutionScope, literalExpressionFloat) {
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

TEST(ExecutionScope, postExpressionInt) {
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

TEST(ExecutionScope, unaryExpressionInt) {
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

TEST(ExecutionScope, unaryMinusExpression) {
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

TEST(ExecutionScope, unaryNotExpression) {
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

TEST(ExecutionScope, binaryExpressionAssignInt) {
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


TEST(ExecutionScope, binaryExpressionAssignVector) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("v", createVectorIntVariable());
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VectorIndexExpression>(VectorIndexExpression(
        std::make_unique<VariableExpression>(VariableExpression("v")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 1))))
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
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);

    // second element
    simpleVariable = dynamic_cast<SimpleVariable*>
        (vectorVariable->values[1].get());
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 37);
}



TEST(ExecutionScope, binaryExpressionPlusAssignInt) {
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

TEST(ExecutionScope, binaryExpressionMinusAssignInt) {
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

TEST(ExecutionScope, binaryExpressionMultiplyAssignInt) {
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

TEST(ExecutionScope, binaryExpressionDivideAssignInt) {
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

TEST(ExecutionScope, binaryExpressionModuloAssignInt) {
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




TEST(ExecutionScope, binaryExpressionPlusInt) {
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

TEST(ExecutionScope, binaryExpressionMinusInt) {
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

TEST(ExecutionScope, binaryExpressionMultiplyInt) {
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

TEST(ExecutionScope, binaryExpressionDivideInt) {
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

TEST(ExecutionScope, binaryExpressionModuloInt) {
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



TEST(ExecutionScope, binaryExpressionLessThanInt) {
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

TEST(ExecutionScope, binaryExpressionLessEqualInt) {
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

TEST(ExecutionScope, binaryExpressionMoreThanInt) {
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

TEST(ExecutionScope, binaryExpressionMoreEqualInt) {
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

TEST(ExecutionScope, binaryExpressionEqualInt) {
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

TEST(ExecutionScope, binaryExpressionNotEqualInt) {
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




TEST(ExecutionScope, binaryExpressionAndInt) {
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

TEST(ExecutionScope, binaryExpressionOrInt) {
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
