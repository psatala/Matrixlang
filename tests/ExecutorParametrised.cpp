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
        "Runtime error: Unknown identifier \"a\"\n", ""),
    ExecutorInputOutput(TestPrograms::divideByZero, "", 
        "Runtime error: Cannot divide by zero\n", ""),
    ExecutorInputOutput(TestPrograms::strongTyping, "", 
        "Runtime error: Cannot perform assignment: "
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
            })", "", "", ""),
    ExecutorInputOutput(R"(
    int f() {
        for(int i = 0; i < 10; ++i) {
            if(i == 4)
                return i;
        }
    }

    int main() {
        print(intToString(f()));
        return 0;
    }
)", "", "", "4")
};

INSTANTIATE_TEST_SUITE_P(ExecutorSimplePrograms, ExecutorParametrised, 
    testing::ValuesIn(simplePrograms));



const ExecutorInputOutput errorPrograms[] = {

    // unknown identifier
    ExecutorInputOutput(R"(int main() {
                a = 3;
                return 0;
            })", "", "Runtime error: Unknown identifier \"a\"\n", ""),
    
    // unknown function
    ExecutorInputOutput(R"(int main() {
                f();
                return 0;
            })", "", "Runtime error: Function with "
            "name \"f\" is undefined\n", ""),

    // double declaration
    ExecutorInputOutput(R"(int main() {
                int a;
                int a;
            })", 
            "", "Runtime error: Local variable with name \"a\" already "
                "exists\n", ""),

    // type mismatch
    ExecutorInputOutput(R"(int main() {
                1 < 12.3;
                return 0;
            })", 
            "", "Runtime error: Cannot perform comparison (less than): "
                "variables are not of the same type\n", ""),


    // type mismatch in declaration
    ExecutorInputOutput(R"(int main() {
                int a = 123.45;
                return 0;
            })", 
            "", "Runtime error: Cannot perform assignment: "
                "variables are not of the same type\n", ""),

    // operator not supported
    ExecutorInputOutput(R"(int main() {
                Vector<int>[2] v1;
                Vector<int>[2] v2;
                v1 >= v2;
                return 0;
            })", 
            "", "Runtime error: Comparison operator (more equal) not "
                "supported for those types\n", ""),

    // vector of length 0
    ExecutorInputOutput(R"(int main() {
                Vector<int>[0] v1;
                return 0;
            })", 
            "", "Runtime error: Vector length must be positive\n", ""),

    // index out of range
    ExecutorInputOutput(R"(int main() {
                Vector<int>[2] v1;
                v1[2];
                return 0;
            })", 
            "", "Runtime error: Index out of range\n", ""),

    // index of incorrect type
    ExecutorInputOutput(R"(int main() {
                Vector<int>[2] v1;
                v1["abc"];
                return 0;
            })", 
            "", "Runtime error: Cannot get unsigned int value for "
                "float or string\n", ""),

    // string increment
    ExecutorInputOutput(R"(int main() {
                string s = "abc";
                ++s;
                return 0;
            })", 
            "", "Runtime error: Unary incremental expression can only be "
                "applied to variables of type int or float\n", ""),

    // modulo by zero
    ExecutorInputOutput(R"(int main() {
                1 % 0;
                return 0;
            })", 
            "", "Runtime error: Cannot divide (modulo) by zero\n", ""),

    // vector of length 0
    ExecutorInputOutput(R"(int main() {
        int a = 0;
                Vector<int>[a] v1;
                return 0;
            })", 
            "", "Runtime error: Vector length must be positive\n", ""),
    
    // modulo by zero
    ExecutorInputOutput(R"(int main() {
        int a = 0;
                1 % a;
                return 0;
            })", 
            "", "Runtime error: Cannot divide (modulo) by zero\n", ""),
    
};

INSTANTIATE_TEST_SUITE_P(ExecutorErrorPrograms, ExecutorParametrised, 
    testing::ValuesIn(errorPrograms));