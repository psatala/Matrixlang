#include "AuxiliaryFunctionsExecutor.h"
#include "../headers/ExecutionObjects/ScopeManager.h"

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