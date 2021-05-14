#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>


int main()
{
    
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            // R"(a + b + c)"
            R"(a = b = c)"
            );

    Interpreter interpreter = Interpreter(std::move(inStream), std::cerr, 
        std::cout);

    try {
        std::unique_ptr<Program> program = interpreter.parser.parseProgram();
        std::cout << program->print();

        // a = b = c
        // BinaryExpression* binaryExpression = dynamic_cast<BinaryExpression*>
        //     (program->expression.get());
        // BinaryExpression* binaryExpressionRight = 
        //     dynamic_cast<BinaryExpression*>(binaryExpression->rhs.get());
        // PrimaryExpression* primaryExpressionA = dynamic_cast<PrimaryExpression*>
        //     (binaryExpression->lhs.get());
        // PrimaryExpression* primaryExpressionB = dynamic_cast<PrimaryExpression*>
        //     (binaryExpressionRight->lhs.get());
        // PrimaryExpression* primaryExpressionC = dynamic_cast<PrimaryExpression*>
        //     (binaryExpressionRight->rhs.get());
        

        // a + b + c
        // BinaryExpression* binaryExpression = dynamic_cast<BinaryExpression*>
        //     (program->expression.get());
        // BinaryExpression* binaryExpressionLeft = dynamic_cast<BinaryExpression*>
        //     (binaryExpression->lhs.get());
        // PrimaryExpression* primaryExpressionA = dynamic_cast<PrimaryExpression*>
        //     (binaryExpressionLeft->lhs.get());
        // PrimaryExpression* primaryExpressionB = dynamic_cast<PrimaryExpression*>
        //     (binaryExpressionLeft->rhs.get());
        // PrimaryExpression* primaryExpressionC = dynamic_cast<PrimaryExpression*>
        //     (binaryExpression->rhs.get());
        
    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}