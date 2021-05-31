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



    inline float intToFloat(int value) {
        return static_cast<float>(value);
    }

    inline int floatToInt(float value) {
        return static_cast<int>(value);
    }

    inline std::string intToString(int value) {
        return std::to_string(value);
    }

    inline int stringToInt(std::string value) {
        try {
            return std::stoi(value);
        }
        catch(std::invalid_argument) {
            throw std::string("Cannot convert string to int: argument invalid");
        }
        catch(std::out_of_range) {
            throw std::string("Cannot convert string to int: argument out of "
                "range");
        }
    }

    inline std::string floatToString(float value) {
        return std::to_string(value);
    }

    inline float stringToFloat(std::string value) {
        try {
            return std::stof(value);
        }
        catch(std::invalid_argument) {
            throw std::string("Cannot convert string to float: argument "
                "invalid");
        }
        catch(std::out_of_range) {
            throw std::string("Cannot convert string to float: argument out of "
                "range");
        }
    }
}