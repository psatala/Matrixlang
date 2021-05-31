#pragma once

#include <istream>
#include <ostream>
#include <string>

namespace EmbeddedFunctionsDefinitions {
    inline void print(std::ostream& outputStream, std::string textToPrint) {
        outputStream << textToPrint;
    }
    
    inline std::string input(std::istream& userInputStream) {
        std::string inputString;
        std::getline(userInputStream, inputString);
        return inputString;
    }
}