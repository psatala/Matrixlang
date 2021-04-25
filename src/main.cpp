#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>
int main()
{
    //std::stringstream inStream("");
    //std::stringstream errStream("");
    //std::stringstream outStream("");
    //inStream << "int a = 10;";
    //Interpreter interpreter = Interpreter(inStream, errStream, outStream);
    std::ifstream f;
    std::stringstream s("");
    f.open("../examples/yearInfo.ml", std::ifstream::in);
    if(f) {
        s << f.rdbuf();
        f.close();
    }
    std::string res;
    while(s >> res)
        std::cout << res << std::endl;

    return 0;
}