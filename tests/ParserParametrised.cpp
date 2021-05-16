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
    ParserInputOutput(R"(
                int main()
                    1 + 2 + 3;
                )", 
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
            Left: Binary expression
              Left: Literal expression: int number: 1
              Right: Literal expression: int number: 2
              Operator: +
            Right: Literal expression: int number: 3
            Operator: +
)"),

    ParserInputOutput(R"(
                int main()
                    a = b = c;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
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

    ParserInputOutput(R"(
                int main()
                    1 + 2 * 3 + 4;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
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

    ParserInputOutput(R"(
                int main()
                    1.0 * 2.0 + 3.0 * 4.0;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
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

    ParserInputOutput(R"(
                int main()
                    1 && 2 + 3 * 4 < 5;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
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

    ParserInputOutput(R"(
                int main()
                    +-!1;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Unary expression
            Operator: +
            Expression: Unary expression
              Operator: -
              Expression: Unary expression
                Operator: !
                Expression: Literal expression: int number: 1
)"),

    ParserInputOutput(R"(
                int main()
                    a + ++ b;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
            Left: Funcall expression
              Identifier: a
            Right: Unary expression
              Operator: ++
              Expression: Funcall expression
                Identifier: b
            Operator: +
)"),

    ParserInputOutput(R"(
                int main()
                    1 * (2 + 3);
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Binary expression
            Left: Literal expression: int number: 1
            Right: Binary expression
              Left: Literal expression: int number: 2
              Right: Literal expression: int number: 3
              Operator: +
            Operator: *
)"),

  ParserInputOutput(R"(
                int main()
                    "abc" 1 + 2 "def";
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: String Expression: 
            Raw String: abc
            Expression within string: Binary expression
              Left: Literal expression: int number: 1
              Right: Literal expression: int number: 2
              Operator: +
            Raw String: def
)"),

  ParserInputOutput(R"(
                int main()
                    abc(1, 2 + 3);
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Funcall expression
            Identifier: abc
            Expression no. 0: Literal expression: int number: 1
            Expression no. 1: Binary expression
              Left: Literal expression: int number: 2
              Right: Literal expression: int number: 3
              Operator: +
)"),

  ParserInputOutput(R"(
                int main()
                    a[1][2, 3];
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Matrix index expression
            Inner expression: Vector index expression
              Inner expression: Funcall expression
                Identifier: a
              Index expression: Literal expression: int number: 1
            First index expression: Literal expression: int number: 2
            Second index expression: Literal expression: int number: 3
)"),

  ParserInputOutput(R"(
                int main()
                    a++--;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Post expression
            Expression: Post expression
              Expression: Funcall expression
                Identifier: a
              Operator: ++
            Operator: --
)"),

  ParserInputOutput(R"(
                int main()
                    ++--!a;
                )",
R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Unary expression
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


const ParserInputOutput otherLanguageObjects[] = {
  ParserInputOutput(R"(Vector<float>[1] a;)", 
    R"(Program
  Declaration
    Type: Vector type
      Contained type: Simple type: float
      Expression: Literal expression: int number: 1
    Identifier: a
)"),

  ParserInputOutput(R"(Matrix< Vector<int>[1] >[2, 3] a;)", 
    R"(Program
  Declaration
    Type: Matrix type
      Contained type: Vector type
        Contained type: Simple type: int
        Expression: Literal expression: int number: 1
      First expression: Literal expression: int number: 2
      Second expressionLiteral expression: int number: 3
    Identifier: a
)"),

  ParserInputOutput(R"(int a = 0;)",
    R"(Program
  Declaration
    Type: Simple type: int
    Identifier: a
    Expression: Literal expression: int number: 0
)"),

  ParserInputOutput(R"(int foo(float bar, string variable);)",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: foo
    Argument list: Argument list
      Type no. 0: Simple type: float
      Identifier no. 0: bar
      Type no. 1: Simple type: string
      Identifier no. 1: variable
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: 
)"),

  ParserInputOutput(R"(int main() return 0;)",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Return: Return
            Expression: Literal expression: int number: 0
)"),

  ParserInputOutput(R"(int main() if(1);)",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          If: If
            Conditional expression: Literal expression: int number: 1
            True statement: Statement
              Instruction List: Instruction list
                Instruction: Instruction
                  Expression: 
            False statement: 
)"),

  ParserInputOutput(R"(int main() if(1); else;)",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          If: If
            Conditional expression: Literal expression: int number: 1
            True statement: Statement
              Instruction List: Instruction list
                Instruction: Instruction
                  Expression: 
            False statement: Statement
              Instruction List: Instruction list
                Instruction: Instruction
                  Expression: 
)"),

  ParserInputOutput(R"(int main() for(int i = 0; i < n; ++i);)",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          For: For
            Declaration: Declaration
              Type: Simple type: int
              Identifier: i
              Expression: Literal expression: int number: 0
            Conditional expression: Binary expression
              Left: Funcall expression
                Identifier: i
              Right: Funcall expression
                Identifier: n
              Operator: <
            Incremental expression: Unary expression
              Operator: ++
              Expression: Funcall expression
                Identifier: i
            Statement: Statement
              Instruction List: Instruction list
                Instruction: Instruction
                  Expression: 
)"),

  ParserInputOutput(R"(int main() {
                if(1)
                    a = 0;
                int b = 1;
                return c;
            })",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          If: If
            Conditional expression: Literal expression: int number: 1
            True statement: Statement
              Instruction List: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: a
                    Right: Literal expression: int number: 0
                    Operator: =
            False statement: 
        Instruction: Instruction
          Declaration: Declaration
            Type: Simple type: int
            Identifier: b
            Expression: Literal expression: int number: 1
        Instruction: Instruction
          Return: Return
            Expression: Funcall expression
              Identifier: c
)"),

  ParserInputOutput(R"(int main() {
                    switch {
                    case a < 1:
                        b = 2;
                    case a > 3:
                        b = 4;
                    default:
                        b = 5;
                    }
                }
            )",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Switch: Switch Go
            Case Go no. 0: Case Go
              Expression: Binary expression
                Left: Funcall expression
                  Identifier: a
                Right: Literal expression: int number: 1
                Operator: <
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: b
                    Right: Literal expression: int number: 2
                    Operator: =
            Case Go no. 1: Case Go
              Expression: Binary expression
                Left: Funcall expression
                  Identifier: a
                Right: Literal expression: int number: 3
                Operator: >
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: b
                    Right: Literal expression: int number: 4
                    Operator: =
            Default: Default
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: b
                    Right: Literal expression: int number: 5
                    Operator: =
)"),

  ParserInputOutput(R"(
                int main() {
                    switch(a) {
                    case 1:
                        b = 2;
                    case 3:
                        b = 4;
                    default:
                        b = 5;
                    }
                }
            )",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Switch: Switch C
            Expression: Funcall expression
              Identifier: a
            Case C no. 0: Case C
              Token: int number: 1
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: b
                    Right: Literal expression: int number: 2
                    Operator: =
            Case C no. 1: Case C
              Token: int number: 3
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: b
                    Right: Literal expression: int number: 4
                    Operator: =
            Default: Default
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Funcall expression
                      Identifier: b
                    Right: Literal expression: int number: 5
                    Operator: =
)"),

  ParserInputOutput(R"(
    int main() {
        print("Hello world");
        return 0;
    }
)",
    R"(Program
  Function
    Type: Simple type: int
    Identifier: main
    Argument list: 
    Statement: Statement
      Instruction List: Instruction list
        Instruction: Instruction
          Expression: Funcall expression
            Identifier: print
            Expression no. 0: String Expression: 
              Raw String: Hello world
        Instruction: Instruction
          Return: Return
            Expression: Literal expression: int number: 0
)")


};


INSTANTIATE_TEST_SUITE_P(ParserParametrisedOtherLanguageObjects, 
  ParserParametrised, testing::ValuesIn(otherLanguageObjects));
