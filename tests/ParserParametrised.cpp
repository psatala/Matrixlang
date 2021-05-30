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
    // simple additive expression
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

    // simple assignment expression
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
            Left: Variable expression
              Identifier: a
            Right: Binary expression
              Left: Variable expression
                Identifier: b
              Right: Variable expression
                Identifier: c
              Operator: =
            Operator: =
)"),

    // combining mulitplication with addition
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

    // another compilation of multiplication and addition
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

    // multiple operators of different precedence levels
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

    // unary rvalue operators
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

    // mix of unary and binary
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
            Left: Variable expression
              Identifier: a
            Right: Unary incremental expression
              Operator: ++
              Expression: Variable expression
                Identifier: b
            Operator: +
)"),

    // parenthesis
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

    // string expression
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

  // funcall
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

  // vector and matrix index access
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
              Inner expression: Variable expression
                Identifier: a
              Index expression: Literal expression: int number: 1
            First index expression: Literal expression: int number: 2
            Second index expression: Literal expression: int number: 3
)"),

  // post expression
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
              Expression: Variable expression
                Identifier: a
              Operator: ++
            Operator: --
)"),

  // unary lvalue expression
  ParserInputOutput(R"(
                int main()
                    !++--a;
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
            Operator: !
            Expression: Unary incremental expression
              Operator: ++
              Expression: Unary incremental expression
                Operator: --
                Expression: Variable expression
                  Identifier: a
)")

};

INSTANTIATE_TEST_SUITE_P(ParserParametrisedExpressions, ParserParametrised, 
    testing::ValuesIn(basicExpressions));


const ParserInputOutput otherLanguageObjects[] = {
  // declaration
  ParserInputOutput(R"(Vector<float>[1] a;)", 
    R"(Program
  Declaration
    Type: Vector type
      Contained type: Simple type: float
      Expression: Literal expression: int number: 1
    Identifier: a
)"),

  // nested declaration
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

  // simple declaration
  ParserInputOutput(R"(int a = 0;)",
    R"(Program
  Declaration
    Type: Simple type: int
    Identifier: a
    Expression: Literal expression: int number: 0
)"),

  // function
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

  // return
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

  // if
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

  // if else
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

  // for
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
              Left: Variable expression
                Identifier: i
              Right: Variable expression
                Identifier: n
              Operator: <
            Incremental expression: Unary incremental expression
              Operator: ++
              Expression: Variable expression
                Identifier: i
            Statement: Statement
              Instruction List: Instruction list
                Instruction: Instruction
                  Expression: 
)"),

  // instruction list
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
                    Left: Variable expression
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
            Expression: Variable expression
              Identifier: c
)"),

  // switch go
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
                Left: Variable expression
                  Identifier: a
                Right: Literal expression: int number: 1
                Operator: <
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Variable expression
                      Identifier: b
                    Right: Literal expression: int number: 2
                    Operator: =
            Case Go no. 1: Case Go
              Expression: Binary expression
                Left: Variable expression
                  Identifier: a
                Right: Literal expression: int number: 3
                Operator: >
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Variable expression
                      Identifier: b
                    Right: Literal expression: int number: 4
                    Operator: =
            Default: Default
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Variable expression
                      Identifier: b
                    Right: Literal expression: int number: 5
                    Operator: =
)"),

  // switch c
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
            Expression: Variable expression
              Identifier: a
            Case C no. 0: Case C
              Token: int number: 1
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Variable expression
                      Identifier: b
                    Right: Literal expression: int number: 2
                    Operator: =
            Case C no. 1: Case C
              Token: int number: 3
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Variable expression
                      Identifier: b
                    Right: Literal expression: int number: 4
                    Operator: =
            Default: Default
              Instruction list: Instruction list
                Instruction: Instruction
                  Expression: Binary expression
                    Left: Variable expression
                      Identifier: b
                    Right: Literal expression: int number: 5
                    Operator: =
)"),

  // hello world
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
