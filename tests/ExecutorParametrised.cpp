#include "AuxiliaryFunctionsExecutor.h"

//basic fixture for parametrised tests
class ExecutorParametrised : 
    public testing::TestWithParam<ExecutorInputOutput> {};

//parametrised test checking running entire program
TEST_P(ExecutorParametrised, runFullProgram)
{
    ExecutorInputOutput executorInputOutput = GetParam();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(executorInputOutput.codeInput);
    std::stringstream userInputStream(executorInputOutput.userInput);
    std::stringstream errStream("");
    std::stringstream outStream("");

    Interpreter interpreter = Interpreter(std::move(inStream), userInputStream, 
        errStream, outStream);

    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();
        Executor(userInputStream, errStream, outStream, std::move(program));
    }
    catch(std::string errorMessage) {
        // catches excpetions thrown during parsing or during executor setup
        // all execution time exceptions should be caught by executor and passed
        // to error stream
        ASSERT_TRUE(false);
    }
    catch(const std::exception& e) {
        // catches all other common exceptions
        // this code should never be executed
        std::cerr << e.what() << '\n';
    }
    
    // always check error stream and standard output
    GTEST_ASSERT_EQ(errStream.str(), executorInputOutput.errorOutput);
    GTEST_ASSERT_EQ(outStream.str(), executorInputOutput.standardOutput);
}

const ExecutorInputOutput programs[] = {
    ExecutorInputOutput(TestPrograms::fibonacciRec, "", "", "55"),
    ExecutorInputOutput(TestPrograms::fibonacciIter, "", "", "55"),
    ExecutorInputOutput(TestPrograms::findMax, "", "", "14"),
    ExecutorInputOutput(TestPrograms::concatStringMatrix, "", "", 
        "ala ma kota i psa"),
    ExecutorInputOutput(TestPrograms::average, "", "", "2.500000"),
    
    ExecutorInputOutput(TestPrograms::printAgeDescription, "-1", "", 
        "Your age is incorrect"),
    ExecutorInputOutput(TestPrograms::printAgeDescription, "11", "", 
        "You are a kid."),
    ExecutorInputOutput(TestPrograms::printAgeDescription, "31", "", 
        "You are an adult."),
    ExecutorInputOutput(TestPrograms::printAgeDescription, "71", "", 
        "You are a pensioner."),

    ExecutorInputOutput(TestPrograms::includeFile, "", "", 
        "Hello from year 2021"),
    ExecutorInputOutput(TestPrograms::copyByValue, "", "", "34"),
    ExecutorInputOutput(TestPrograms::copying, "", "", 
        "0: 0, 1: 0\n0: 3, 1: 5\n"),
    ExecutorInputOutput(TestPrograms::scope, "", 
        "Execution time error: Unknown identifier \"a\"\n", ""),
    ExecutorInputOutput(TestPrograms::divideByZero, "", 
        "Execution time error: Cannot divide by zero\n", ""),
    ExecutorInputOutput(TestPrograms::strongTyping, "", 
        "Execution time error: Cannot perform assignment: "
        "variables are not of the same type\n", "")
};


INSTANTIATE_TEST_SUITE_P(ExecutorFullPrograms, ExecutorParametrised, 
    testing::ValuesIn(programs));



const ExecutorInputOutput simplePrograms[] = {
    ExecutorInputOutput(R"(int main() {
                for(int i = 0; i < 5; ++i) {
                    int l = 3;
                }
                return 0;
            })", "", "", "")
};

INSTANTIATE_TEST_SUITE_P(ExecutorSimplePrograms, ExecutorParametrised, 
    testing::ValuesIn(simplePrograms));