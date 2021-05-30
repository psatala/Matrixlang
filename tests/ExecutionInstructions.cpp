#include "AuxiliaryFunctionsExecutor.h"
#include "../headers/Interpreter.h"

TEST(ExecutionInstructions, expressionExecution) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(11)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 33))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    Instruction instruction = Instruction(
        std::make_unique<BinaryExpression>(std::move(binaryExpression))
    );

    std::unique_ptr<Variable> returnedVariable = 
        instruction.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 33);
}

TEST(ExecutionInstructions, expressionListExecution) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(11)));
    
    InstructionList instructionList = InstructionList();
    
    // instruction with assignment expression
    Instruction instruction1 = Instruction(
        std::make_unique<BinaryExpression>(
            BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 33))),
        std::make_unique<Operator>(Operator(ASSIGN))
        )
    ));
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction1)));

    // another instruction with assignment expression
    Instruction instruction2 = Instruction(
        std::make_unique<BinaryExpression>(
            BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 99))),
        std::make_unique<Operator>(Operator(ASSIGN))
        )
    ));
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction2)));

    std::unique_ptr<Variable> returnedVariable = 
        instructionList.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 99);
}

TEST(ExecutionInstructions, blockExecution) {
    ScopeManager scopeManager;
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(12)));
    
    InstructionList instructionList = InstructionList();
    
    // instruction with assignment expression
    Instruction instruction1 = Instruction(
        std::make_unique<BinaryExpression>(
            BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 24))),
        std::make_unique<Operator>(Operator(ASSIGN))
        )
    ));
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction1)));

    // another instruction with assignment expression
    Instruction instruction2 = Instruction(
        std::make_unique<BinaryExpression>(
            BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 36))),
        std::make_unique<Operator>(Operator(ASSIGN))
        )
    ));
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction2)));

    // block containing all above instructions
    Block block = 
        Block(std::make_unique<InstructionList>(std::move(instructionList)));

    std::unique_ptr<Variable> returnedVariable = 
        block.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 36);
}

TEST(ExecutionInstructions, statementInstructionExecution) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(10)));
    
    BinaryExpression binaryExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 18))),
        std::make_unique<Operator>(Operator(ASSIGN))
    );
    Statement statement = Statement(std::make_unique<Instruction>(
        Instruction(
            std::make_unique<BinaryExpression>(std::move(binaryExpression))
        )
    ));
    

    std::unique_ptr<Variable> returnedVariable = 
        statement.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 18);
}

TEST(ExecutionInstructions, statmentBlockExecution) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(12)));
    
    InstructionList instructionList = InstructionList();
    
    // instruction with assignment expression
    Instruction instruction1 = Instruction(
        std::make_unique<BinaryExpression>(
            BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 37))),
        std::make_unique<Operator>(Operator(ASSIGN))
        )
    ));
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction1)));

    // another instruction with assignment expression
    Instruction instruction2 = Instruction(
        std::make_unique<BinaryExpression>(
            BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 111))),
        std::make_unique<Operator>(Operator(ASSIGN))
        )
    ));
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction2)));

    // statement containing block containing all above instructions
    Statement statement = Statement(std::make_unique<Block>(Block(
        std::make_unique<InstructionList>(std::move(instructionList))
    )));

    std::unique_ptr<Variable> returnedVariable = 
        statement.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 111);
}

TEST(ExecutionInstructions, ifExecutionTrue) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(12)));
    
    If ifInstruction = If(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 1))), 
        std::move(createStatementWithAssignment("a", 24)), 
        std::move(createStatementWithAssignment("a", 456)));

    std::unique_ptr<Variable> returnedVariable = 
        ifInstruction.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 24);
}

TEST(ExecutionInstructions, ifExecutionFalse) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(12)));
    
    If ifInstruction = If(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0))), 
        std::move(createStatementWithAssignment("a", 24)), 
        std::move(createStatementWithAssignment("a", 456)));

    std::unique_ptr<Variable> returnedVariable = 
        ifInstruction.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 456);
}

TEST(ExecutionInstructions, localDeclarationEmptyExecution) {
    ScopeManager scopeManager;
    scopeManager.addFuncall();

    Declaration declaration = Declaration(
        std::make_unique<SimpleType>(SimpleType(INT)), "a",
        std::unique_ptr<Expression>(nullptr)
    );
    

    std::unique_ptr<Variable> returnedVariable = 
        declaration.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionInstructions, globalDeclarationExpressionExecution) {
    ScopeManager scopeManager;

    Declaration declaration = Declaration(
        std::make_unique<SimpleType>(SimpleType(INT)), "a",
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 23)))
    );
    

    std::unique_ptr<Variable> returnedVariable = 
        declaration.execute(&scopeManager, false);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 23);
}