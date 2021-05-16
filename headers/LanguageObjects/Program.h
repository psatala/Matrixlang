#pragma once

#include <memory>
#include <variant>

#include "Declaration.h"
#include "Function.h"
#include "../LanguageObjects.h"

class Program {
public:
    std::vector<std::variant<std::unique_ptr<Declaration>, 
        std::unique_ptr<Function>>> declarationFunctionVector;

    Program() {}


    // std::unique_ptr<Expression> expression;
    // Program(std::unique_ptr<Expression> expression) : 
        // expression(std::move(expression)) {}

    std::string print() {
        std::string toPrintString = std::string("Program") + "\n";
            // + ident(1) + expression->print(2);
        for(int i = 0; i < declarationFunctionVector.size(); ++i) {
            
            if(0 == declarationFunctionVector[i].index()) {
                // declaration
                std::unique_ptr<Declaration> declaration = std::move(std::get
                    <std::unique_ptr<Declaration>>
                    (declarationFunctionVector[i]));
                toPrintString += ident(1) + declaration->print(2);

                // move back ownership to vector
                declarationFunctionVector[i] = std::move(declaration);

                continue;
            }

            // function
            std::unique_ptr<Function> function = std::move(std::get
                    <std::unique_ptr<Function>>
                    (declarationFunctionVector[i]));
                toPrintString += ident(1) + function->print(2);

                // move back ownership to vector
                declarationFunctionVector[i] = std::move(function);
        }

        return toPrintString;
    }
};
