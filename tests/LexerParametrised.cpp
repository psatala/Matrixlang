#include "AuxiliaryFunctionsLexer.h"

//basic fixture for parametrised tests
class LexerParametrised : public testing::TestWithParam<SimpleTestData> {};

//parametrised test checking only type of first token
TEST_P(LexerParametrised, checkFirstTokenType)
{
    SimpleTestData simpleTestData = GetParam();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(simpleTestData.input);
    std::stringstream errStream("");
    std::stringstream outStream("");
    Interpreter interpreter = Interpreter(std::move(inStream), 
        errStream, outStream);
    
    assertTokenType(interpreter.parser.lexer, simpleTestData.firstToken);
}



const SimpleTestData basicTestParams[] = {
    SimpleTestData("HelloWorld", IDENTIFIER),
    SimpleTestData("123", INT_NUMBER),
    SimpleTestData("3.14", FLOAT_NUMBER),
    SimpleTestData("\"hello\"", STRING_CONSTANT),
    SimpleTestData("#comment", COMMENT),
    SimpleTestData("```comment```", COMMENT),
    SimpleTestData("", EOT),
    SimpleTestData("~", UNKNOWN),
    SimpleTestData("```incorrect unterminated comment", INCORRECT),
    SimpleTestData("@include \"otherFile.ml\"", LEXER_COMMAND)
};

INSTANTIATE_TEST_SUITE_P(LexerParametrisedBasic, LexerParametrised, 
    testing::ValuesIn(basicTestParams));




const SimpleTestData keywordTestParams[] = {
    SimpleTestData("if", IF),
    SimpleTestData("else", ELSE),
    SimpleTestData("switch", SWITCH),
    SimpleTestData("case", CASE),
    SimpleTestData("default", DEFAULT),
    SimpleTestData("for", FOR),
    SimpleTestData("return", RETURN),
    SimpleTestData("int", INT),
    SimpleTestData("float", FLOAT),
    SimpleTestData("string", STRING),
    SimpleTestData("Vector", VECTOR),
    SimpleTestData("Matrix", MATRIX),
    SimpleTestData("void", VOID)
};

INSTANTIATE_TEST_SUITE_P(LexerParametrisedKeywords, LexerParametrised, 
    testing::ValuesIn(keywordTestParams));




const SimpleTestData operatorTestParams[] = {
    SimpleTestData("+", PLUS),
    SimpleTestData("+=", PLUS_ASSIGN),
    SimpleTestData("++", INCREMENT),
    SimpleTestData("-", MINUS),
    SimpleTestData("-=", MINUS_ASSIGN),
    SimpleTestData("--", DECREMENT),
    SimpleTestData("*", MULTIPLY),
    SimpleTestData("*=", MULTIPLY_ASSIGN),
    SimpleTestData("/", DIVIDE),
    SimpleTestData("/=", DIVIDE_ASSIGN),
    SimpleTestData("%", MODULO),
    SimpleTestData("%=", MODULO_ASSIGN),
    SimpleTestData("<", LESS_THAN),
    SimpleTestData("<=", LESS_EQUAL),
    SimpleTestData(">", MORE_THAN),
    SimpleTestData(">=", MORE_EQUAL),
    SimpleTestData("!", NOT),
    SimpleTestData("!=", NOT_EQUAL),
    SimpleTestData("=", ASSIGN),
    SimpleTestData("==", EQUAL),
    SimpleTestData("&&", AND),
    SimpleTestData("||", OR),
    SimpleTestData(":", COLON),
    SimpleTestData(";", SEMICOLON),
    SimpleTestData(",", COMMA),
    SimpleTestData(".", DOT),
    SimpleTestData("{", L_BRACKET),
    SimpleTestData("}", R_BRACKET),
    SimpleTestData("[", L_SQUARE_BRACKET),
    SimpleTestData("]", R_SQUARE_BRACKET),
    SimpleTestData("(", L_PARENT),
    SimpleTestData(")", R_PARENT),
};

INSTANTIATE_TEST_SUITE_P(LexerParametrisedOperators, LexerParametrised, 
    testing::ValuesIn(operatorTestParams));
