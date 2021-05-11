#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>
int main()
{
    // std::unique_ptr<std::ifstream> fileStream = 
    //     std::make_unique<std::ifstream>();

    // fileStream->open("../examples/HelloWorld.ml", std::ifstream::in);
    // if(!*fileStream)
    //     return -1;
    
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            // R"(Matrix <Vector<float>[ ]> [ , ])"
            R"(Vector<float>[ ])"
            // R"(float)"
            );

    Interpreter interpreter = Interpreter(std::move(inStream), std::cerr, 
        std::cout);

    // while(!interpreter.parser.lexer.getIsProcessed()) {
    //     const std::optional<Token> token = interpreter.parser.lexer.getToken();
    //     std::cout << token->type << std::endl;
    // }
    try {
        // MatrixType matrixType = 
        // interpreter.parser.parseMatrixType().value();
        // VectorType vectorType = interpreter.parser.parseVectorType().value();
        Type type = interpreter.parser.parseType().value();
        VectorType vectorType = std::get<VectorType>(type.containedType);
        int a = 0;
        std::variant<SimpleType, VectorType, MatrixType> typeVariant = 
            vectorType.type.containedType;
        int b = 1;
        // SimpleType simpleType = std::get<SimpleType>(vectorType.type.containedType);
        SimpleType simpleType = std::get<SimpleType>(typeVariant);
        int c = 2;
        // SimpleType simpleType = 
            // std::get<SimpleType>(vectorType.type.containedType);
        if(simpleType.type == FLOAT)
            std::cout << "Success" << std::endl;

        // Type type = vectorType.type;
        // std::get<SimpleType>(type.containedType);
        // SimpleType simpleType = 
        //     std::get<SimpleType>(vectorType.type.containedType);
        // TokenType tokenType = simpleType.type;
        // if(tokenType == FLOAT)
        //     std::cout << "Correct";

    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}