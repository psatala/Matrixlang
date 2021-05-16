#include <iostream>

#include "../headers/Interpreter.h"
#include <fstream>


int main()
{
    
    std::unique_ptr<std::stringstream> inStream = 
        std::make_unique<std::stringstream>(
            // R"(a = b + c * 2 < d)"
            // R"(++--!a)"
            // R"(a + ++ b)"
            // R"(1)"
            // R"("abc" 1 + 2 "def")"
            // R"(abc(1, 2 + 3))"
            // R"(a[1][2, 3])"
            // R"(a++--)"
            // R"(Vector<float>[1])"
            // R"(Matrix< Vector<int>[1] >[2, 3])"
            // R"(a = b = c)"
            // R"(int a = 0;)"

            // R"(int global = 0;
            //     int main())"
            
            // R"(int a, Vector<float>[2] b)"
            // R"(int foo(float bar, string variable))"
            // R"(return 0;)"
            // R"(if(1))"
            // R"(for(int i = 0; i < n; ++i))"

            // R"(for(int i = 0; i < n; ++i))"

            R"({
                if(1)
                    a = 0;
                int b = 1;
                return c;
            })"

//             R"(
// int main() {
//     print("Hello world");
//     return 0;
// })"

            // R"(a = 3;)"
            );

    Interpreter interpreter = Interpreter(std::move(inStream), std::cerr, 
        std::cout);

    try {
        interpreter.parser.getNextToken();

        // std::unique_ptr<Instruction> instruction = 
        //     interpreter.parser.parseInstruction();
        // std::cout << instruction->print(1);

        // std::unique_ptr<InstructionList> instructionList = 
        //     interpreter.parser.parseBlock();
        // std::cout << instructionList->print(1);

        std::unique_ptr<Statement> statement = 
            interpreter.parser.parseStatement();
        std::cout << statement->print(1);


        // std::unique_ptr<For> forInstruction = interpreter.parser.parseFor();
        // std::cout << forInstruction->print(1);


        // std::unique_ptr<If> ifInstruction = interpreter.parser.parseIf();
        // std::cout << ifInstruction->print(1);

        // std::unique_ptr<Return> returnInstruction = 
        //     interpreter.parser.parseReturn();
        // std::cout << returnInstruction->print(1);

        // std::unique_ptr<ArgumentList> argumentList = 
        //     interpreter.parser.parseArgumentList();
        // std::cout << argumentList->print(1);
        
        // std::unique_ptr<Declaration> declaration = 
        //     interpreter.parser.parseDeclarationInstruction();
        // std::cout << declaration->print(1);

        // std::variant<std::unique_ptr<Declaration>, std::unique_ptr<Function>> 
        //     variant = interpreter.parser.parseDeclarationOrFunction();
        // std::unique_ptr<Function> function = std::move
        //     (std::get<std::unique_ptr<Function>>(variant));
        // std::cout << function->print(1);
        // std::unique_ptr<Declaration> declaration = std::move
        //     (std::get<std::unique_ptr<Declaration>>(variant));
        // std::cout << declaration->print(1);

        // interpreter.parser.getNextToken();
        // std::unique_ptr<Type> type = interpreter.parser.parseType();
        // std::cout << type->print(1);
        
        // std::unique_ptr<Program> program = interpreter.parser.parseProgram();
        // std::cout << program->print();


    } catch(std::string exception) {
        std::cout << exception << std::endl;
    }
    return 0;
}