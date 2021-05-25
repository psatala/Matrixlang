#include "AuxiliaryFunctionsParser.h"

//basic fixture for parametrised tests
class ParserExpectError : public testing::TestWithParam<ParserInputOutput> {};

//parametrised test checking if any error occured while parsing test program
TEST_P(ParserExpectError, checkError)
{
    ParserInputOutput parserInputOutput = GetParam();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(parserInputOutput.input);
    std::stringstream errStream("");
    std::stringstream outStream("");
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    
    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();
    } catch(std::string exception) {
        GTEST_ASSERT_EQ(errStream.str(), parserInputOutput.expectedOutput);
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
    R"(Line: 4 Column: 17 -> Parsing instruction: expected ";"
)"),

    // no declaration or function
    ParserInputOutput(R"(
                1 + 2;
                )",
    R"(Line: 2 Column: 17 -> Parsing declaration or function: )"
    R"(could not parse neither declaration nor function
)"),

    // trying to assign to rvalue
    ParserInputOutput(R"(
                int main()
                    a + b = c;
                )",
    R"(Line: 3 Column: 29 -> Parsing assignment expression: )"
    R"(expected lvalue operand before assignment operator
)"),

    // missing closing bracket
    ParserInputOutput(R"(
                int main() {
                    return 0;
                )",
    R"(Line: 4 Column: 17 -> Parsing block: expected "}"
)"),

    // missing closing parenthesis
    ParserInputOutput(R"(
                int main( {
                    return 0;
                }
                )",
    "Line: 2 Column: 27 -> Parsing function: expected \")\"\n"),

    // missing expression in declaration
    ParserInputOutput(R"(
                int a = ;
                )",
    R"(Line: 2 Column: 25 -> Parsing declaration: parsed "=", )"
    R"(but an expression did not follow
)"),

    // unknown type
    ParserInputOutput(R"(
                double a = 0;
                )",
    R"(Line: 2 Column: 17 -> Parsing declaration or function: )"
    R"(could not parse neither declaration nor function
)"),

    // vector without type
    ParserInputOutput(R"(
                Vector <>[3] v;
                )",
    R"(Line: 2 Column: 25 -> Parsing Vector, expected Type
)"),

    // mixing switch c with switch go
    ParserInputOutput(R"(
                int main()
                    switch(c) {
                        case 1 < 2:
                            ;
                    }
                )",
    R"(Line: 4 Column: 32 -> Parsing case c: expected ":"
)")

};

INSTANTIATE_TEST_SUITE_P(ParserCheckWhatFails, ParserExpectError, 
    testing::ValuesIn(testPrograms));