#include "AuxiliaryFunctionsExecutor.h"
#include "../headers/ExecutionObjects/OperatorExecution.h"

TEST(OperatorExecution, additionInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::add(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 7);
}

TEST(OperatorExecution, additionFloat) {
    std::unique_ptr<Variable> floatVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(1.5f));
    std::unique_ptr<Variable> floatVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(1.25f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::add(floatVariable1.get(), floatVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<float>(simpleResultVariable->value), 2.75f);
}

TEST(OperatorExecution, additionString) {
    std::unique_ptr<Variable> stringVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable("abc"));
    std::unique_ptr<Variable> stringVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable("def"));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::add(stringVariable1.get(), stringVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleResultVariable->value), 
        "abcdef");
}

TEST(OperatorExecution, subtractionInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::subtract(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), -1);
}

TEST(OperatorExecution, multiplicationInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::multiply(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 12);
}

TEST(OperatorExecution, divisionInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(30));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::divide(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 7);
}

TEST(OperatorExecution, moduloInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(30));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::modulo(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 2);
}



TEST(OperatorExecution, lessThanInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::lessThan(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, lessThanFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3.4f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.3f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::lessThan(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, lessEqualInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::lessEqual(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, lessEqualFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(1.4f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.3f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::lessEqual(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}



TEST(OperatorExecution, moreThanInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(4));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::moreThan(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, moreThanFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3.4f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.3f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::moreThan(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, moreEqualInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::moreEqual(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, moreEqualFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(1.4f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.3f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::moreEqual(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}



TEST(OperatorExecution, equalInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(34));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(34));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::equal(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, equalFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.2f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.3f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::equal(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, notEqualInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(34));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(34));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::notEqual(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, notEqualFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.2f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(2.3f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::notEqual(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}