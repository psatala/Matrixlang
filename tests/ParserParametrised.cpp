#include "AuxiliaryFunctionsParser.h"

//basic fixture for parametrised tests
class ParserParametrised : public testing::TestWithParam<ParserInputOutput> {};

//parametrised test checking only parsed tree
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
    ParserInputOutput(R"(1 + 2 + 3)", 
R"(Program
  Binary expression
    Left: Binary expression
      Left: Literal expression: int number: 1
      Right: Literal expression: int number: 2
      Operator: +
    Right: Literal expression: int number: 3
    Operator: +
)"),

    ParserInputOutput(R"(a = b = c)",
R"(Program
  Binary expression
    Left: Funcall expression
      Identifier: a
    Right: Binary expression
      Left: Funcall expression
        Identifier: b
      Right: Funcall expression
        Identifier: c
      Operator: =
    Operator: =
)"),

    ParserInputOutput(R"(1 + 2 * 3 + 4)", 
R"(Program
  Binary expression
    Left: Binary expression
      Left: Literal expression: int number: 1
      Right: Binary expression
        Left: Literal expression: int number: 2
        Right: Literal expression: int number: 3
        Operator: *
      Operator: +
    Right: Literal expression: int number: 4
    Operator: +
)"),

    ParserInputOutput(R"(1.0 * 2.0 + 3.0 * 4.0)",
R"(Program
  Binary expression
    Left: Binary expression
      Left: Literal expression: float number: 1.000000
      Right: Literal expression: float number: 2.000000
      Operator: *
    Right: Binary expression
      Left: Literal expression: float number: 3.000000
      Right: Literal expression: float number: 4.000000
      Operator: *
    Operator: +
)"), 

    ParserInputOutput(R"(1 && 2 + 3 * 4 < 5)",
R"(Program
  Binary expression
    Left: Literal expression: int number: 1
    Right: Binary expression
      Left: Binary expression
        Left: Literal expression: int number: 2
        Right: Binary expression
          Left: Literal expression: int number: 3
          Right: Literal expression: int number: 4
          Operator: *
        Operator: +
      Right: Literal expression: int number: 5
      Operator: <
    Operator: &&
)"),

    ParserInputOutput(R"(+-!1)",
R"(Program
  Unary expression
    Operator: +
    Expression: Unary expression
      Operator: -
      Expression: Unary expression
        Operator: !
        Expression: Literal expression: int number: 1
)"),

    ParserInputOutput(R"(a + ++ b)",
R"(Program
  Binary expression
    Left: Funcall expression
      Identifier: a
    Right: Unary expression
      Operator: ++
      Expression: Funcall expression
        Identifier: b
    Operator: +
)"),

    ParserInputOutput(R"(1 * (2 + 3))",
R"(Program
  Binary expression
    Left: Literal expression: int number: 1
    Right: Binary expression
      Left: Literal expression: int number: 2
      Right: Literal expression: int number: 3
      Operator: +
    Operator: *
)"),

  ParserInputOutput(R"("abc" 1 + 2 "def")",
R"(Program
  String Expression: 
    Raw String: abc
    Expression within string: Binary expression
      Left: Literal expression: int number: 1
      Right: Literal expression: int number: 2
      Operator: +
    Raw String: def
)"),

  ParserInputOutput(R"(abc(1, 2 + 3))",
R"(Program
  Funcall expression
    Identifier: abc
    Expression no. 0: Literal expression: int number: 1
    Expression no. 1: Binary expression
      Left: Literal expression: int number: 2
      Right: Literal expression: int number: 3
      Operator: +
)"),

  ParserInputOutput(R"(a[1][2, 3])",
R"(Program
  Matrix index expression
    Inner expression: Vector index expression
      Inner expression: Funcall expression
        Identifier: a
      Index expression: Literal expression: int number: 1
    First index expression: Literal expression: int number: 2
    Second index expression: Literal expression: int number: 3
)"),

  ParserInputOutput(R"(a++--)",
R"(Program
  Post expression
    Expression: Post expression
      Expression: Funcall expression
        Identifier: a
      Operator: ++
    Operator: --
)"),

  ParserInputOutput(R"(++--!a)",
R"(Program
  Unary expression
    Operator: ++
    Expression: Unary expression
      Operator: --
      Expression: Unary expression
        Operator: !
        Expression: Funcall expression
          Identifier: a
)")

};

INSTANTIATE_TEST_SUITE_P(ParserParametrisedExpressions, ParserParametrised, 
    testing::ValuesIn(basicExpressions));
