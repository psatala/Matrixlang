#include <sstream>

#include "AuxiliaryFunctionsExecutor.h"
#include "../headers/Interpreter.h"
#include "../headers/LanguageObjects/EmbeddedFunction.h"

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

TEST(ExecutionInstructions, switchCExecution) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(10)));

    CaseC caseC1 = CaseC(
        Token(INT_NUMBER, 10), std::move(createInstructionList("a", 11, ASSIGN))
    );

    CaseC caseC2 = CaseC(
        Token(INT_NUMBER, 20), std::move(createInstructionList("a", 21, ASSIGN))
    );
    
    Default defaultInstruction = Default(
        std::move(createInstructionList("a", 31, ASSIGN))
    );
    
    SwitchC switchC = SwitchC();
    switchC.lValExpression = std::make_unique<VariableExpression>(
        VariableExpression("a")
    );
    switchC.caseCInstructions.push_back(std::make_unique<CaseC>(
        std::move(caseC1)));
    switchC.caseCInstructions.push_back(std::make_unique<CaseC>(
        std::move(caseC2)));
    switchC.defaultInstruction = std::make_unique<Default>(
        std::move(defaultInstruction));

    std::unique_ptr<Variable> returnedVariable = 
        switchC.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    Variable* variable = scopeManager.getVariable("a");
    SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 11);




    // change value in scope manager and run again
    scopeManager.setVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(20)));

    returnedVariable = switchC.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 21);
    

    

    // change value in scope manager and run again
    scopeManager.setVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(15)));

    returnedVariable = switchC.execute(&scopeManager);

    // nullptr returned for expressions
    ASSERT_FALSE(returnedVariable);
    
    // variable changed in scope manager
    variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 31);
    
}

TEST(ExecutionInstructions, returnExecution) {
    ScopeManager scopeManager;
    scopeManager.init();

    Return returnInstruction = Return(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 0)))
    );

    std::unique_ptr<Variable> returnedVariable = 
        returnInstruction.execute(&scopeManager);

    // returned variable
    ASSERT_TRUE(returnedVariable);
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 0);
}

TEST(ExecutionInstructions, emptyReturnExecution) {
    ScopeManager scopeManager;
    scopeManager.init();

    Return returnInstruction = Return(std::unique_ptr<Expression>(nullptr));

    std::unique_ptr<Variable> returnedVariable = 
        returnInstruction.execute(&scopeManager);

    // returned variable
    ASSERT_TRUE(returnedVariable);
    VoidVariable* voidVariable = 
        dynamic_cast<VoidVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(voidVariable);
    GTEST_ASSERT_EQ(voidVariable->type, VOID);
}

TEST(ExecutionInstructions, returnStoppingExecution) {
    ScopeManager scopeManager;
    scopeManager.init();
    scopeManager.addGlobalVariable("a", 
        std::make_unique<SimpleVariable>(SimpleVariable(10)));

    Instruction instruction1 = Instruction(
        std::make_unique<Return>(Return(std::make_unique<LiteralExpression>
            (LiteralExpression(Token(INT, -1)))))
    );

    Instruction instruction2 = Instruction(
        std::make_unique<BinaryExpression>(BinaryExpression(
        std::make_unique<VariableExpression>(VariableExpression("a")),
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 20))),
        std::make_unique<Operator>(Operator(ASSIGN))
        ))
    );

    InstructionList instructionList = InstructionList();
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction1))
    );
    instructionList.instructions.push_back(
        std::make_unique<Instruction>(std::move(instruction2))
    );


    std::unique_ptr<Variable> returnedVariable = 
        instructionList.execute(&scopeManager);

    // returned variable
    ASSERT_TRUE(returnedVariable);
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), -1);

    // variable not changed in scope manager due to previous return
    Variable* variable = scopeManager.getVariable("a");
    simpleVariable = dynamic_cast<SimpleVariable*>(variable);
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 10);
}




TEST(ExecutionInstructions, emptyFunction) {
    ScopeManager scopeManager;
    scopeManager.addFunction(
        std::make_unique<Function>(Function(
            std::make_unique<SimpleType>(SimpleType(VOID)), "f", 
            std::unique_ptr<ArgumentList>(nullptr),
            std::make_unique<Statement>(Statement(
                std::make_unique<Instruction>(Instruction(
                    std::make_unique<Return>(Return(
                        std::unique_ptr<Expression>(nullptr)
                    ))
                ))
            ))
        ))
    );
    FuncallExpression funcallExpression = FuncallExpression("f");
    std::unique_ptr<Variable> returnedVariable = 
        funcallExpression.value(&scopeManager);

    // returned variable
    ASSERT_TRUE(returnedVariable);
    VoidVariable* voidVariable = 
        dynamic_cast<VoidVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(voidVariable);
    GTEST_ASSERT_EQ(voidVariable->type, VOID);
}

TEST(ExecutionInstructions, addFunction) {
    ScopeManager scopeManager;

    // function definition
    ArgumentList argumentList;
    argumentList.typeVector.push_back(
        std::make_unique<SimpleType>(SimpleType(INT)));
    argumentList.identifierVector.push_back("a");
    argumentList.typeVector.push_back(
        std::make_unique<SimpleType>(SimpleType(INT)));
    argumentList.identifierVector.push_back("b");

    scopeManager.addFunction(
        std::make_unique<Function>(Function(
            std::make_unique<SimpleType>(SimpleType(INT)), "add", 
            std::make_unique<ArgumentList>(ArgumentList(
                std::move(argumentList))),
            std::make_unique<Statement>(Statement(
                std::make_unique<Instruction>(Instruction(
                    std::make_unique<Return>(Return(
                        std::make_unique<BinaryExpression>(BinaryExpression(
                            std::make_unique<VariableExpression>(
                                VariableExpression("a")),
                            std::make_unique<VariableExpression>(
                                VariableExpression("b")),
                            std::make_unique<Operator>(Operator(PLUS))
                        ))
                    ))
                ))
            ))
        ))
    );

    // function call
    ExpressionList expressionList;
    expressionList.push_back(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 3))));
    expressionList.push_back(
        std::make_unique<LiteralExpression>(LiteralExpression(Token(INT, 2))));
    FuncallExpression funcallExpression = FuncallExpression("add", 
        std::make_unique<ExpressionList>(std::move(expressionList)));
    
    std::unique_ptr<Variable> returnedVariable = 
        funcallExpression.value(&scopeManager);
    
    // returned variable
    ASSERT_TRUE(returnedVariable);
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, INT);
    GTEST_ASSERT_EQ(std::get<int>(simpleVariable->value), 5);
}




TEST(ExecutionInstructions, printEmbeddedFunction) {
    ScopeManager scopeManager;
    std::stringstream outStream = std::stringstream("");
    EmbeddedFunction::outputStream = &outStream;

    // function call
    StringExpression stringExpression = StringExpression();
    stringExpression.stringLiteralsAndExpressions.push_back("Hello world");
    ExpressionList expressionList;
    expressionList.push_back(std::make_unique<StringExpression>(
        std::move(stringExpression)));

    FuncallExpression funcallExpression = FuncallExpression("print", 
        std::make_unique<ExpressionList>(std::move(expressionList)));
    
    std::unique_ptr<Variable> returnedVariable = 
        funcallExpression.value(&scopeManager);

    // returned variable
    ASSERT_TRUE(returnedVariable);
    VoidVariable* voidVariable = 
        dynamic_cast<VoidVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(voidVariable);
    GTEST_ASSERT_EQ(voidVariable->type, VOID);

    // output stream content
    GTEST_ASSERT_EQ(outStream.str(), "Hello world");
}

TEST(ExecutionInstructions, inputEmbeddedFunction) {
    ScopeManager scopeManager;
    std::stringstream inStream = std::stringstream("Hello\nWorld");
    EmbeddedFunction::userInputStream = &inStream;

    // function call
    FuncallExpression funcallExpression = FuncallExpression("input");
    
    std::unique_ptr<Variable> returnedVariable = 
        funcallExpression.value(&scopeManager);

    // returned variable
    ASSERT_TRUE(returnedVariable);
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(returnedVariable.get());
        
    ASSERT_TRUE(simpleVariable);
    GTEST_ASSERT_EQ(simpleVariable->type, STRING);
    GTEST_ASSERT_EQ(std::get<std::string>(simpleVariable->value), "Hello");
    
}
