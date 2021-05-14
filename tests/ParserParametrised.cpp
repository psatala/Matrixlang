#include "AuxiliaryFunctionsParser.h"

//basic fixture for parametrised tests
class ParserParametrised : public testing::TestWithParam<ParserInputOutput> {};

//parametrised test checking only type of first token
TEST_P(ParserParametrised, checkParsedTree)
{
    ParserInputOutput parserInputOutput = GetParam();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(parserInputOutput.input);
    std::stringstream errStream("");
    std::stringstream outStream("");
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    
    std::unique_ptr<Program> program = interpreter.parser.parseProgram();
    GTEST_ASSERT_EQ(program->print(), parserInputOutput.expectedOutput);
}



const ParserInputOutput basicExpressions[] = {
    ParserInputOutput(R"(a + b + c)", 
R"(Program
  Binary expression
    Left: Binary expression
      Left: Primary expression: identifier: a
      Right: Primary expression: identifier: b
      Operator: code 43
    Right: Primary expression: identifier: c
    Operator: code 43
)"),

    ParserInputOutput(R"(a = b = c)",
R"(Program
  Binary expression
    Left: Primary expression: identifier: a
    Right: Binary expression
      Left: Primary expression: identifier: b
      Right: Primary expression: identifier: c
      Operator: code 61
    Operator: code 61
)"),

    ParserInputOutput(R"(1 + 2 * 3 + 4)", 
R"(Program
  Binary expression
    Left: Binary expression
      Left: Primary expression: int number: 1
      Right: Binary expression
        Left: Primary expression: int number: 2
        Right: Primary expression: int number: 3
        Operator: code 42
      Operator: code 43
    Right: Primary expression: int number: 4
    Operator: code 43
)"),

    ParserInputOutput(R"(1.0 * 2.0 + 3.0 * 4.0)",
R"(Program
  Binary expression
    Left: Binary expression
      Left: Primary expression: float number: 1.000000
      Right: Primary expression: float number: 2.000000
      Operator: code 42
    Right: Binary expression
      Left: Primary expression: float number: 3.000000
      Right: Primary expression: float number: 4.000000
      Operator: code 42
    Operator: code 43
)"), 

    ParserInputOutput(R"(a = b + c * 2 < d)",
R"(Program
  Binary expression
    Left: Primary expression: identifier: a
    Right: Binary expression
      Left: Binary expression
        Left: Primary expression: identifier: b
        Right: Binary expression
          Left: Primary expression: identifier: c
          Right: Primary expression: int number: 2
          Operator: code 42
        Operator: code 43
      Right: Primary expression: identifier: d
      Operator: code 60
    Operator: code 61
)"),

    ParserInputOutput(R"(++--!a)",
R"(Program
  Unary expression
    Operator: code 151
    Expression: Unary expression
      Operator: code 152
      Expression: Unary expression
        Operator: code 33
        Expression: Primary expression: identifier: a
)"),

    ParserInputOutput(R"(a + ++ b)",
R"(Program
  Binary expression
    Left: Primary expression: identifier: a
    Right: Unary expression
      Operator: code 151
      Expression: Primary expression: identifier: b
    Operator: code 43
)")

};

INSTANTIATE_TEST_SUITE_P(ParserParametrisedExpressions, ParserParametrised, 
    testing::ValuesIn(basicExpressions));
