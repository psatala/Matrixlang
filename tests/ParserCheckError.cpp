#include "AuxiliaryFunctionsParser.h"
#include "TestPrograms.h"

//basic fixture for parametrised tests
class ParserCheckError : public testing::TestWithParam<std::string> {};

//parametrised test checking if any error occured while parsing test program
TEST_P(ParserCheckError, checkError)
{
    std::string inputProgram = GetParam();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(inputProgram);
    std::stringstream errStream("");
    std::stringstream outStream("");
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    
    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();

        // parsing program should not generate errors
        ASSERT_TRUE(errStream.str().empty());

    } catch(std::string exception) {
        std::cout << exception << std::endl;
        //if exception thrown by parser occurs, fail the test
        ASSERT_TRUE(false);
    }
    
}

const std::string testPrograms[] = {
    TestPrograms::fibonacciRec,
    TestPrograms::fibonacciIter,
    TestPrograms::findMax,
    TestPrograms::concatStringMatrix,
    TestPrograms::average,
    TestPrograms::printAgeDescription,
    TestPrograms::includeFile,
    TestPrograms::copyByValue,
    TestPrograms::copying,
    TestPrograms::scope,
    TestPrograms::divideByZero,
    TestPrograms::strongTyping
};

INSTANTIATE_TEST_SUITE_P(ParserCheckIfFails, ParserCheckError, 
    testing::ValuesIn(testPrograms));