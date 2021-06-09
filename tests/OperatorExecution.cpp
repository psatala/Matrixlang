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



TEST(OperatorExecution, andInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(1));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(1));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::logicalAnd(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, andFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(0.0f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(0.1f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::logicalAnd(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, orString) {
    std::unique_ptr<Variable> stringVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(""));
    std::unique_ptr<Variable> stringVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(""));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::logicalOr(stringVariable1.get(), 
        stringVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, orFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(0.0f));
    std::unique_ptr<Variable> intVariable2 = std::make_unique<SimpleVariable>
        (SimpleVariable(0.1f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::logicalOr(intVariable1.get(), intVariable2.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}

TEST(OperatorExecution, notInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::logicalNot(intVariable1.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);
}

TEST(OperatorExecution, notFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(0.0f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::logicalNot(intVariable1.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 1);
}


TEST(OperatorExecution, unaryPlusInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::unaryPlus(intVariable1.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 3);
}

TEST(OperatorExecution, unaryPlusFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3.14f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::unaryPlus(intVariable1.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<float>(simpleResultVariable->value), 3.14f);
}

TEST(OperatorExecution, unaryMinusInt) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(3));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::unaryMinus(intVariable1.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), -3);
}

TEST(OperatorExecution, unaryMinusFloat) {
    std::unique_ptr<Variable> intVariable1 = std::make_unique<SimpleVariable>
        (SimpleVariable(-3.14f));
    std::unique_ptr<Variable> resultVariable = 
        VariableOperators::unaryMinus(intVariable1.get());
    
    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(resultVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<float>(simpleResultVariable->value), 3.14f);
}



TEST(OperatorExecution, vectorIndexAccess) {
    std::unique_ptr<Variable> vectorVariable = createVectorIntVariable();
    std::unique_ptr<Variable> intVariable = 
        VariableOperators::vectorIndexAccess(vectorVariable.get(), 1);

    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(intVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<int>(simpleResultVariable->value), 0);   
}

TEST(OperatorExecution, matrixIndexAccess) {
    std::unique_ptr<Variable> matrixVariable = createMatrixStringVariable();
    std::unique_ptr<Variable> stringVariable = 
        VariableOperators::matrixIndexAccess(matrixVariable.get(), 1, 0);

    SimpleVariable* simpleResultVariable = 
        dynamic_cast<SimpleVariable*>(stringVariable.get());
    ASSERT_TRUE(simpleResultVariable);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleResultVariable->value), "");   
}