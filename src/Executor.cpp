#include "../headers/Executor.h"

Executor::Executor(std::istream& userInputStream, std::ostream& errStream, 
    std::ostream& outputStream, std::unique_ptr<Program> program) : 
    userInputStream(userInputStream), errStream(errStream), 
    outputStream(outputStream), program(std::move(program)) {
    
    // initial pass getting all functions and global variables
    for(int i = 0; i < this->program->declarationFunctionVector.size(); ++i) {

        // declaration
        if(std::unique_ptr<Declaration>* declaration = 
            std::get_if<std::unique_ptr<Declaration>>
            (&this->program->declarationFunctionVector[i])) {

            (*declaration)->execute(&scopeManager, false);
            continue;
        }

        // function
        scopeManager.addFunction(std::move(std::get<std::unique_ptr<Function>>(
            this->program->declarationFunctionVector[i])));
    }

    // check main
    Function* mainFunction = scopeManager.getFunction("main");
    if(!mainFunction)
        throw std::string("Missing \"main\" function");
    
    if(!mainFunction->argumentList.get()->typeVector.empty() ||
        !mainFunction->argumentList.get()->identifierVector.empty())
        throw std::string("\"main\" function should not have any parametrs");

    Type* mainReturnType = mainFunction->type.get();
    SimpleType* simpleMainReturnType = 
        dynamic_cast<SimpleType*>(mainReturnType);
    if(!simpleMainReturnType)
        throw std::string("\"main\" function must have int as return type");
    if(INT != simpleMainReturnType->type)
        throw std::string("\"main\" function must have int as return type");

    if(!mainFunction->statement)
        throw std::string("\"main\" function must have a body");

    
    // set up streams for embedded functions
    EmbeddedFunction::userInputStream = &userInputStream;
    EmbeddedFunction::outputStream = &outputStream;

    
    // execute main
    // function is called with empty expression list
    std::unique_ptr<Variable> returnedVariable;
    try {
        returnedVariable = mainFunction->execute(&scopeManager, 
            std::make_unique<ExpressionList>(ExpressionList()).get());
    }
    catch(std::string errorMessage) {
        // exception thrown during execution
        errStream << "Execution time error: " << errorMessage << '\n';
    }
    catch(const std::exception& e) {
        // for all other common exceptions
        // this code should never be executed
        errStream << e.what() << '\n';
    }
    


    // check return value
    SimpleVariable* simpleVariable = 
        dynamic_cast<SimpleVariable*>(returnedVariable.get());
    if(!simpleVariable)
        throw std::string("\"main\" function must have a not empty return "
            "statement");
    int returnedValue = std::get<int>(simpleVariable->value);
    if(returnedValue != 0)
        throw std::string("Program returned ") + std::to_string(returnedValue);
}