#include "AuxiliaryFunctionsParser.h"

//basic fixture for parametrised tests
class ParserExpectError : public testing::TestWithParam<ParserInputOutput> {};

//parametrised test checking if any error occured while parsing test program
TEST_P(ParserExpectError, checkError)
{
    ParserInputOutput parserInputOutput = GetParam();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(parserInputOutput.input);
    std::stringstream userInputStream("");
    std::stringstream errStream("");
    std::stringstream outStream("");
    Interpreter interpreter = Interpreter(std::move(inStream), userInputStream, 
        errStream, outStream);
    
    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();
    } catch(std::string exception) {
        GTEST_ASSERT_EQ(exception, parserInputOutput.expectedOutput);
    }
    
}

const ParserInputOutput testPrograms[] = {
    // no error
    ParserInputOutput(R"(
                int main()
                    1 + 2 + 3;
                )",
    R"()"),

    // no semicolon
    ParserInputOutput(R"(
                int main()
                    1 + 2
                )",
    R"(Parsing stopped, error: Line: 4 Column: 17 -> Parsing instruction: )"
    R"(expected ";"
)"),

    // no declaration or function
    ParserInputOutput(R"(
                1 + 2;
                )",
    R"(Parsing stopped, error: Line: 2 Column: 17 -> Parsing declaration or )"
    R"(function: could not parse neither declaration nor function
)"),

    // trying to assign to rvalue
    ParserInputOutput(R"(
                int main()
                    a + b = c;
                )",
    R"(Parsing stopped, error: Line: 3 Column: 29 -> Parsing assignment )"
    R"(expression: expected lvalue operand before assignment operator
)"),

    // missing closing bracket
    ParserInputOutput(R"(
                int main() {
                    return 0;
                )",
    R"(Parsing stopped, error: Line: 4 Column: 17 -> Parsing block: expected "}"
)"),

    // missing closing parenthesis
    ParserInputOutput(R"(
                int main( {
                    return 0;
                }
                )",
    "Parsing stopped, error: Line: 2 Column: 27 -> Parsing function: "
    "expected \")\"\n"),

    // missing expression in declaration
    ParserInputOutput(R"(
                int a = ;
                )",
    R"(Parsing stopped, error: Line: 2 Column: 25 -> Parsing declaration: )"
    R"(parsed "=", but an expression did not follow
)"),

    // unknown type
    ParserInputOutput(R"(
                double a = 0;
                )",
    R"(Parsing stopped, error: Line: 2 Column: 17 -> Parsing declaration or )"
    R"(function: could not parse neither declaration nor function
)"),

    // vector without type
    ParserInputOutput(R"(
                Vector <>[3] v;
                )",
    R"(Parsing stopped, error: Line: 2 Column: 25 -> Parsing Vector, expected )"
    R"(Type
)"),

    // mixing switch c with switch go
    ParserInputOutput(R"(
                int main()
                    switch(c) {
                        case 1 < 2:
                            ;
                    }
                )",
    R"(Parsing stopped, error: Line: 4 Column: 32 -> Parsing case c: )"
    R"(expected ":"
)")

};

INSTANTIATE_TEST_SUITE_P(ParserCheckWhatFails, ParserExpectError, 
    testing::ValuesIn(testPrograms));