#pragma once

#include "Parser.h"
#include "Executor.h"

class Interpreter {
    std::istream& userInputStream;
    std::ostream& errStream;
    std::ostream& outStream;
    

public:
    Parser parser;

    Interpreter(std::unique_ptr<std::istream> inStream, 
        std::istream& userInputStream, std::ostream& errStream, 
        std::ostream& outStream) : 
        userInputStream(userInputStream), errStream(errStream), 
        outStream(outStream), parser(std::move(inStream), errStream) {}

    void start() {
        try {
            std::unique_ptr<Program> program = parser.parseProgram();
            Executor(userInputStream, errStream, outStream, std::move(program));
        }
        catch(std::string errorMessage) {
            // catches excpetions thrown during parsing or during executor setup
            errStream << errorMessage << '\n';
        }
        catch(const std::exception& e) {
            // catches all other common exceptions
            // this code should never be executed
            errStream << e.what() << '\n';
        }
        
    }
};