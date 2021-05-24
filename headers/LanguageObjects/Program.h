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

    std::string print() {
        std::string toPrintString = std::string("Program") + "\n";
        
        for(int i = 0; i < declarationFunctionVector.size(); ++i) {
            
            // declaration
            if(std::unique_ptr<Declaration>* declaration = 
                std::get_if<std::unique_ptr<Declaration>>
                (&declarationFunctionVector[i])) {

                toPrintString += ident(1) + (*declaration)->print(2);
                continue;
            }

            // function
            toPrintString += ident(1) + std::get<std::unique_ptr<Function>>
                (declarationFunctionVector[i])->print(2);

        }

        return toPrintString;
    }
};
