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
        std::make_unique<std::stringstream>(TestPrograms::average
    //         R"(
    // float average(Vector<float>[n] vector) {
    // 	float sum = vector[0];
    //     sum + 0.0;
    //     #return sum / intToFloat(n);
    // }

    // int main() {
    // 	Vector<float>[2] vector;
    // 	vector[0] = 2;
    // 	vector[1] = 3;
    //     float sum = vector[0];
    // 	# print(floatToString(average(vector))); #prints 2.5
    //     average(vector);
    // 	return 0;
    // })"
    );

    fileStream->open("../examples/HelloWorld.ml", std::ifstream::in);
    if(!*fileStream)
        return -1;

    Interpreter interpreter = Interpreter(std::move(inStream), std::cin, 
        std::cerr, std::cout);
    interpreter.start();
    return 0;
}