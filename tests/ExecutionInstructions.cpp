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

TEST(ExecutionInstructions, forExecution) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(12)));

    Declaration declaration = Declaration(
        std::make_unique<SimpleType>(SimpleType(INT)), "i",
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0)))
    );
    
    BinaryExpression conditionalExpression = BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("i")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 10))),
        std::make_unique<Operator>(Operator(LESS_THAN))
        );

    UnaryIncrementalExpression incrementalExpression = 
        UnaryIncrementalExpression(
            std::make_unique<Operator>(Operator(INCREMENT)),
            std::make_unique<VariableExpression>(VariableExpression("i"))
        );

    For forInstruction = For(
        std::make_unique<Declaration>(std::move(declaration)),
        std::make_unique<BinaryExpression>(std::move(conditionalExpression)),
        std::make_unique<UnaryIncrementalExpression>
            (std::move(incrementalExpression)),
        std::move(createStatementWithAssignment("a", 2, PLUS_ASSIGN))
    );

    std::unique_ptr<Variable> returnedVariable = 
        forInstruction.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 32);
}

TEST(ExecutionInstructions, switchGoExecution) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(5)));

    CaseGo caseGo1 = CaseGo(
        std::make_unique<BinaryExpression>(BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 10))),
        std::make_unique<Operator>(Operator(LESS_THAN)))),
        std::move(createInstructionList("a", 3, ASSIGN))
    );

    CaseGo caseGo2 = CaseGo(
        std::make_unique<BinaryExpression>(BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 20))),
        std::make_unique<Operator>(Operator(MORE_THAN)))),
        std::move(createInstructionList("a", 111, ASSIGN))
    );
    
    Default defaultInstruction = Default(
        std::move(createInstructionList("a", 15, ASSIGN))
    );
    
    SwitchGo switchGo = SwitchGo();
    switchGo.caseGoInstructions.push_back(std::make_unique<CaseGo>(
        std::move(caseGo1)));
    switchGo.caseGoInstructions.push_back(std::make_unique<CaseGo>(
        std::move(caseGo2)));
    switchGo.defaultInstruction = std::make_unique<Default>(
        std::move(defaultInstruction));

    std::unique_ptr<Variable> returnedVariable = 
        switchGo.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 3);




    // change value in scope manager and run again
    scopeManager.setVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(23)));

    returnedVariable = switchGo.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 111);
    

    

    // change value in scope manager and run again
    scopeManager.setVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(17)));

    returnedVariable = switchGo.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 15);
    
}
