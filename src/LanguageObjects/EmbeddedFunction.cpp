#include "../../headers/LanguageObjects/EmbeddedFunction.h"

// default values of static parameters
std::istream* EmbeddedFunction::userInputStream = &std::cin;
std::ostream* EmbeddedFunction::outputStream = &std::cout;


EmbeddedFunction::EmbeddedFunction(std::unique_ptr<Type> type, 
    std::string identifier, 
    std::unique_ptr<ArgumentList> argumentList, 
    std::unique_ptr<Statement> statement) : 
        Function(std::move(type), identifier, std::move(argumentList), 
            std::move(statement)) {}


std::unique_ptr<Variable> EmbeddedFunction::executeInnerStatement(
    ScopeManager* scopeManager) {
    
    if("print" == identifier) {
        SimpleVariable* simpleVariable = dynamic_cast<SimpleVariable*>
            (scopeManager->getVariable("textToPrint"));
        EmbeddedFunctionsDefinitions::print(*outputStream, 
            std::get<std::string>(simpleVariable->value));
        return std::make_unique<VoidVariable>(VoidVariable());
    }

    return std::unique_ptr<Variable>(nullptr);
}