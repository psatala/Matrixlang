#pragma once

#include <memory>
#include <vector>

#include "Type.h"
#include "../LanguageObjects.h"

class ArgumentList {
public:
    std::vector<std::unique_ptr<Type>> typeVector;
    std::vector<std::string> identifierVector;
    ArgumentList() {}

    std::string print(int identLevel) {
        std::string toPrintString = std::string("Argument list") + "\n";
        for(int i = 0; i < std::min(typeVector.size(), identifierVector.size());
            ++i) {
            
            toPrintString += ident(identLevel) + "Type no. " + 
                std::to_string(i) + ": " + typeVector[i]->print(identLevel + 1) 
                + ident(identLevel) + "Identifier no. " + std::to_string(i) + 
                ": " + identifierVector[i] + "\n";
        }
        return toPrintString;
    }
};