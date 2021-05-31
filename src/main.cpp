#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/Interpreter.h"

#include "../tests/TestPrograms.h"

int main()
{
    std::unique_ptr<std::ifstream> fileStream = 
        std::make_unique<std::ifstream>();

    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            R"(
                int main() {
                    print("Hello world\n");
                    return 0;
                }
            )");

    fileStream->open("../examples/HelloWorld.ml", std::ifstream::in);
    if(!*fileStream)
        return -1;

    Interpreter interpreter = Interpreter(std::move(inStream), std::cin, 
        std::cerr, std::cout);
    interpreter.start();
    return 0;
}